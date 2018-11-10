# ---------------------------------------------------------------------------
# IMLAB
# ---------------------------------------------------------------------------

# Register flex and bison output
set(QUERYC_SCANNER_OUT     "${CMAKE_SOURCE_DIR}/tools/queryc/gen/query_scanner.cc")
set(QUERYC_PARSER_OUT      "${CMAKE_SOURCE_DIR}/tools/queryc/gen/query_parser.cc")
set(QUERYC_COMPILER        "${CMAKE_SOURCE_DIR}/tools/queryc/query_compiler.cc")
set(QUERYC_PARSE_CONTEXT   "${CMAKE_SOURCE_DIR}/tools/queryc/query_parse_context.cc")
set(QUERYC_CC ${QUERYC_SCANNER_OUT} ${QUERYC_PARSER_OUT} ${QUERYC_COMPILER} ${QUERYC_PARSE_CONTEXT})


# Clear the output files
file(WRITE ${QUERYC_SCANNER_OUT} "")
file(WRITE ${QUERYC_PARSER_OUT} "")

## Generate parser & scanner
add_custom_target(queryc_parser
        COMMAND ${BISON_EXECUTABLE}
        --defines="${CMAKE_SOURCE_DIR}/tools/queryc/gen/query_parser.h"
        --output=${QUERYC_PARSER_OUT}
        --report=state
        --report-file="${CMAKE_BINARY_DIR}/queryc_bison.log"
        "${CMAKE_SOURCE_DIR}/tools/queryc/query_parser.y"
        COMMAND ${FLEX_EXECUTABLE}
        --outfile=${QUERYC_SCANNER_OUT}
        "${CMAKE_SOURCE_DIR}/tools/queryc/query_scanner.l"
        DEPENDS "${CMAKE_SOURCE_DIR}/tools/queryc/query_parser.y"
        "${CMAKE_SOURCE_DIR}/tools/queryc/query_scanner.l")

add_library(query ${QUERYC_CC})
add_dependencies(query queryc_parser)


# ---------------------------------------------------------------------------
# Compiler
# ---------------------------------------------------------------------------

add_executable(queryc "${CMAKE_SOURCE_DIR}/tools/queryc/queryc.cc" ${INCLUDE_H})
target_link_libraries(queryc query imlab gflags Threads::Threads)

# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_cpplint_target(lint_queryc "${CMAKE_SOURCE_DIR}/tools/queryc/queryc.cc")
list(APPEND lint_targets lint_queryc)
