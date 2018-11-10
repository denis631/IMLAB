//
// Created by Denis Grebennicov on 27.11.17.
//

#ifndef PROJECT_QUERYPARSER_H
#define PROJECT_QUERYPARSER_H


#include "queryc.h"

namespace imlab {
    struct QueryParser {
        SelectStatement Parse(const std::string &);
    };
}


#endif //PROJECT_QUERYPARSER_H
