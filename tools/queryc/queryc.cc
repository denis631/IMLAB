#include <iostream>
#include <fstream>
#include <imlab/algebra/print.h>
#include <imlab/algebra/inner_join.h>
#include <imlab/algebra/table_scan.h>
#include <imlab/algebra/selection.h>
#include <imlab/database.h>
#include <imlab/query/queryc.h>
#include <queue>

namespace imlab {
    void QueryCompiler::Compile(std::unique_ptr<imlab::Print> algebraTreeRoot, std::string &path) {
        std::ofstream outputStream(path);

        outputStream << "#include <iostream>\n\n"
                     << "#include \"../../include/imlab/database.h\"\n"
                     << "#include \"../../include/imlab/infra/hash_table.h\"\n\n"
                     << "using namespace imlab;\n\n"
                     << "extern \"C\" void " << COMPILED_QUERY_FUNCTION_NAME << "(imlab::Database &db) {\n"
                     << std::endl;

        algebraTreeRoot->Execute(outputStream);

        outputStream << "}" << std::endl;

        std::stringstream stream;
        stream << "clang++ -std=c++14 -O3 -fPIC -rdynamic -shared -undefined dynamic_lookup -o " << COMPILED_QUERY_LIB
               << " " << path;
        std::system(stream.str().c_str()); // Compile generated query

        stream.clear();
    }

    std::unique_ptr<Print> QueryCompiler::ConstructAlgebraTree(SelectStatement &selectStatement) {
        std::vector<std::unique_ptr<TableScan>> tableScanLayer;
        std::vector<std::unique_ptr<Operator>> selectionLayer;

        // create tablescans from table strings
        for (const auto &table : selectStatement.tables) {
            tableScanLayer.push_back(std::make_unique<TableScan>(table.c_str()));
        }

        // apply selection predicates on tablescans if possible
        for (auto &tableScan :tableScanLayer) {
            auto endIterator = std::remove_if(selectStatement.selectPredicates.begin(),
                                              selectStatement.selectPredicates.end(),
                                              [&tableScan](std::pair<const IU*, std::string> &predicate) {
                                                  return strcmp(predicate.first->table, tableScan->TableName()) == 0;
                                              });

            // get predicates only for that table
            std::vector<std::pair<const IU*, std::string>> tablePredicates;
            std::copy(endIterator, selectStatement.selectPredicates.end(), std::back_inserter(tablePredicates));

            // remove unneeded select predicates
            selectStatement.selectPredicates.erase(endIterator, selectStatement.selectPredicates.end());

            if (!tablePredicates.empty()) {
                selectionLayer.push_back(std::make_unique<Selection>(std::move(tableScan), tablePredicates));
            } else {
                selectionLayer.push_back(std::move(tableScan));
            }
        }

        std::unique_ptr<Operator> finalJoin = std::move(selectionLayer[0]);

        // reduce all joins
        for (int i = 1; i < selectionLayer.size(); ++i) {
            auto rightOperand = std::move(selectionLayer[i]);

            std::vector<std::pair<const IU*, const IU*>> joinPredicates;

            // get predicates only for that join
            for (auto &predicate : selectStatement.joinPredicates) {
                auto leftCollect = finalJoin->CollectIUs();
                auto rightCollect = rightOperand->CollectIUs();
                auto predicateExistsInLeftChild  = std::find(leftCollect.begin(), leftCollect.end(), predicate.first) != leftCollect.end()    || std::find(leftCollect.begin(), leftCollect.end(), predicate.second) != leftCollect.end() ;
                auto predicateExistsInRightChild = std::find(rightCollect.begin(), rightCollect.end(), predicate.first) != rightCollect.end() || std::find(rightCollect.begin(), rightCollect.end(), predicate.second) != rightCollect.end();

                if (predicateExistsInLeftChild && predicateExistsInRightChild) {
                    // check if we should swap predicate order x.a = y.b -> y.b = x.a
                    auto shouldSwapPredicates = std::find(leftCollect.begin(), leftCollect.end(), predicate.first) == leftCollect.end();

                    if (shouldSwapPredicates) {
                        auto tmp = predicate.first;
                        predicate.first = predicate.second;
                        predicate.second = tmp;
                    }

                    joinPredicates.push_back(predicate);
                }
            }

            finalJoin = std::make_unique<InnerJoin>(std::move(finalJoin), std::move(rightOperand), joinPredicates);
        }

        return std::make_unique<Print>(std::move(finalJoin), selectStatement.projectedAttributes );
    }
}