
#include <iosfwd>
#include <imlab/infra/error.h>
#include "./gen/query_parser.h"
#include "imlab/query/query_parse_context.h"

using namespace imlab;

QueryParseContext::QueryParseContext(bool trace_scanning, bool trace_parsing)
    : trace_parsing_(trace_parsing), trace_scanning_(trace_scanning) {}

SelectStatement QueryParseContext::Parse(std::istream &in) {
    beginScan(in);
    imlab::QueryParser parser(*this);
    parser.set_debug_level(trace_parsing_);
    parser.parse();
    endScan();

    return statement;
}

void QueryParseContext::Error(const std::string &m) {
    throw QueryCompilationError(m);
}

void QueryParseContext::Error(uint32_t line, uint32_t column, const std::string &err) {
    std::stringstream ss;
    ss << "[ l=" << line << " c=" << column << " ] " << err << std::endl;
    throw QueryCompilationError(ss.str());
}

const imlab::IU* IUForTableNameAndAttributeName(const char *tableName, const char *attributeName) {
    auto match = imlab::Datastore::IUs.equal_range(tableName);
    for (auto iter = match.first; iter != match.second; ++iter) {
        if (strcmp(iter->second.column, attributeName) == 0)    return &(iter->second);
    }

    return nullptr; // shouldn't happen
}

void QueryParseContext::buildAlgebraTree(std::vector<std::string> projectedAttributes,
                                         std::vector<std::string> tables,
                                         std::vector<std::pair<std::string, std::string>> predicates) {

    SelectStatement result;
    result.tables = tables;

    std::vector<const IU*> projectedAttributesIU;

    for (const auto &attribute : projectedAttributes) {
        const IU *attributeIU = nullptr;

        for (const auto &table : tables) {
            attributeIU = IUForTableNameAndAttributeName(table.c_str(), attribute.c_str());

            if (attributeIU != nullptr) break;
        }

        projectedAttributesIU.push_back(attributeIU);
    }

    result.projectedAttributes = projectedAttributesIU;

    for (const auto &predicate : predicates) {
        auto leftPredicate = predicate.first;
        auto rightPredicate = predicate.second;

        // check if there doesn't exist a IU for the right side, meaning it's a selection predicate
        const IU* rightColumnIU = nullptr;
        for (const auto &table : tables) {
            rightColumnIU = IUForTableNameAndAttributeName(table.c_str(), rightPredicate.c_str());
            if (rightColumnIU != nullptr) break;
        }

        const IU* leftColumnIU = nullptr;
        for (const auto &table : tables) {
            leftColumnIU = IUForTableNameAndAttributeName(table.c_str(), leftPredicate.c_str());
            if (leftColumnIU != nullptr) break;
        }

        if (leftColumnIU == nullptr) {
            throw std::invalid_argument("attribute with name: " + leftPredicate + " was not found");
        }

        if (rightColumnIU == nullptr) {
            // it's a selection
            result.selectPredicates.emplace_back(leftColumnIU, rightPredicate);
        } else {
            // it's a join
            result.joinPredicates.emplace_back(leftColumnIU, rightColumnIU);
        }
    }

    this->statement = result;
}
