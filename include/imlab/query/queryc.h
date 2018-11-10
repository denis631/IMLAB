//
// Created by Denis Grebennicov on 25.11.17.
//

#ifndef PROJECT_QUERYC_H
#define PROJECT_QUERYC_H

#define COMPILED_QUERY_LIB "COMPILED_QUERY_LIB"
#define COMPILED_QUERY_FUNCTION_NAME "generated_query"

#include <fstream>

#include <imlab/algebra/operator.h>
#include <imlab/algebra/print.h>

namespace imlab {
    struct SelectStatement {
        std::vector<std::string> tables{};
        std::vector<const IU *> projectedAttributes{};
        std::vector<std::pair<const IU *, const IU *>> joinPredicates{};
        std::vector<std::pair<const IU *, std::string>> selectPredicates{};
    };

    struct QueryCompiler {
        auto Compile(std::unique_ptr<imlab::Print> algebraTreeRoot, std::string &path) -> void;
        auto ConstructAlgebraTree(imlab::SelectStatement &selectStatement) -> std::unique_ptr<imlab::Print>;
    };
}

#endif //PROJECT_QUERYC_H
