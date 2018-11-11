//
// Created by Denis Grebennicov on 25.11.17.
//

#ifndef PROJECT_QUERY_PARSE_CONTEXT_H
#define PROJECT_QUERY_PARSE_CONTEXT_H
#include "imlab/query/query.h"
#include "imlab/algebra/table_scan.h"
#include "imlab/algebra/inner_join.h"
#include "imlab/datastore.h"
#include "imlab/algebra/iu.h"
#include "imlab/infra/types.h"
#include "imlab/algebra/selection.h"
#include "imlab/algebra/print.h"
#include <istream>

namespace imlab {
    struct QueryParser;

class QueryParseContext {
   friend QueryParser;

public:
    explicit QueryParseContext(bool trace_scanning = false, bool trace_parsing = false);

    SelectStatement Parse(std::istream &in);
    void buildAlgebraTree(std::vector<std::string> projectedAttributes,
                          std::vector<std::string> tables,
                          std::vector<std::pair<std::string, std::string>> predicates);

    void Error(uint32_t line, uint32_t column, const std::string &err);
    void Error(const std::string &m);

    private:
    void beginScan(std::istream &in);
    void endScan();

    SelectStatement statement;
    // Trace the scanning
    bool trace_scanning_;
    // Trace the parsing
    bool trace_parsing_;
};

class QueryCompiler {
public:
    auto Compile(std::string &in, std::string &path) -> void;

    QueryParseContext parseContext;
private:
    auto ConstructAlgebraTree(SelectStatement &selectStatement) -> std::unique_ptr<Print>;
};
}

#endif //PROJECT_QUERY_PARSE_CONTEXT_H
