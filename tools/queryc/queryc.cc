#include <iostream>
#include <fstream>
#include <imlab/query/query_parse_context.h>

#include "imlab/schema/schema_parse_context.h"
#include "imlab/schema/schema_compiler.h"
#include "gflags/gflags.h"
#include "imlab/algebra/table_scan.h"
#include "imlab/algebra/inner_join.h"
#include "imlab/datastore.h"
#include "imlab/algebra/iu.h"
#include "imlab/infra/types.h"
#include "imlab/algebra/selection.h"
#include "imlab/algebra/print.h"

using SchemaCompiler = imlab::SchemaCompiler;
using SchemaParseContext = imlab::SchemaParseContext;
using TableScan = imlab::TableScan;
using InnerJoin = imlab::InnerJoin;
using IU = imlab::IU;
using Selection = imlab::Selection;
using Print = imlab::Print;
using QueryParseContext = imlab::QueryParseContext;

int main(int argc, char *argv[]) {
    std::cout << "SQL Statement: " << std::endl;

    std::string input;
    std::getline(std::cin, input);

    imlab::QueryCompiler compiler;
    std::string path = "../src/query/tmp_queryc.cc";
    compiler.Compile(input, path);

//    std::stringstream inputStream;
//    inputStream.str(input);
//    QueryParseContext qc;
//    qc.Parse(inputStream);
}
