//
// Created by Denis Grebennicov on 27.11.17.
//

#include <regex>
#include <iostream>
#include <algorithm>
#include <imlab/datastore.h>
#include "imlab/query/queryParser.h"

// Split a string and return a vector of substrings
std::vector<std::string> Split(const std::string &s, const std::string &delim) {
    std::vector<std::string> elems;
    auto matchIndex = s.find(delim);
    size_t prevMatchIndex = 0;

    while (matchIndex != std::string::npos && matchIndex != prevMatchIndex) {
        elems.emplace_back(std::string(s.begin() + prevMatchIndex, s.begin() + matchIndex));
        matchIndex += delim.length();
        prevMatchIndex = matchIndex;
        matchIndex = s.find(delim, matchIndex);
    }

    elems.emplace_back(std::string(s.begin() + prevMatchIndex, s.end()));

    return elems;
}

std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

const imlab::IU* IUForTableNameAndAttributeName(const char *tableName, const char *attributeName) {
    auto match = imlab::Datastore::IUs.equal_range(tableName);

    for (auto iter = match.first; iter != match.second; ++iter) {
        if (strcmp(iter->second.column, attributeName) == 0) return &(iter->second);
    }

    return nullptr; // shouldn't happen
}

imlab::SelectStatement imlab::QueryParser::Parse(const std::string &input) {
    std::string query = std::string(input.begin(), input.end() - (input[input.length() - 1] == ';' ? 1 : 0));

    auto selectIndex = query.find("select");
    auto fromIndex = query.find("from");
    auto whereIndex = query.find("where");

    auto projectedAttributeString = std::string(query.begin() + selectIndex + std::string("select").length(), query.begin() + fromIndex);
    auto projectedAttributes = Split(projectedAttributeString, ",");
    std::transform(projectedAttributes.begin(), projectedAttributes.end(), projectedAttributes.begin(), ::trim);

    auto tablesString = std::string(query.begin() + fromIndex + std::string("from").length(), whereIndex == std::string::npos ? query.end() : (query.begin() + whereIndex));
    auto tables = Split(tablesString, ",");
    std::transform(tables.begin(), tables.end(), tables.begin(), ::trim);

    std::vector<const IU*> projectedAttributesIU;

    for (const auto &attribute : projectedAttributes) {
        const IU *attributeIU = nullptr;

        for (const auto &table : tables) {
            attributeIU = IUForTableNameAndAttributeName(table.c_str(), attribute.c_str());

            if (attributeIU != nullptr) break;
        }

        projectedAttributesIU.push_back(attributeIU);
    }

    std::transform(projectedAttributes.begin(), projectedAttributes.end(), projectedAttributesIU.begin(), [&tables](const std::string &attribute) {
        const IU *attributeIU = nullptr;

        for (const auto &table : tables) {
            attributeIU = IUForTableNameAndAttributeName(table.c_str(), attribute.c_str());
            if (attributeIU != nullptr) break;
        }

        return attributeIU;
    });

    SelectStatement result;
    result.tables = tables;
    result.projectedAttributes = projectedAttributesIU;

    if (whereIndex != std::string::npos) {
        auto predicatesString = std::string(query.begin() + whereIndex + std::string("where").length(), query.end());
        auto predicates = Split(predicatesString, "and");
        std::transform(predicates.begin(), predicates.end(), predicates.begin(), ::trim);

        for (const auto &predicate : predicates) {
            auto predicateOperands = Split(predicate, "=");
            auto leftPredicate = trim(predicateOperands[0]);
            auto rightPredicate = trim(predicateOperands[1]);
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

                auto firstCharIter = rightPredicate.begin();
                auto lastCharIter = rightPredicate.begin() + rightPredicate.length() - 1;

                // map single quotes to double quotes
                if ((*firstCharIter) == '\'' && *lastCharIter == '\'') {
                    *firstCharIter = '"';
                    *lastCharIter = '"';
                }

                result.selectPredicates.emplace_back(leftColumnIU, rightPredicate);
            } else {
                // it's a join
                result.joinPredicates.emplace_back(leftColumnIU, rightColumnIU);
            }
        }
    }

    return result;
}
