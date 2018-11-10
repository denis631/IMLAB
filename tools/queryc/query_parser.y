// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
%skeleton "lalr1.cc"
%require "3.0.4"
// ---------------------------------------------------------------------------------------------------
// Write a parser header file
%defines
// Define the parser class name
%define parser_class_name {QueryParser}
// Create the parser in our namespace
%define api.namespace { imlab }
// Use C++ variant to store the values and get better type warnings (compared to "union")
%define api.value.type variant
// With variant-based values, symbols are handled as a whole in the scanner
%define api.token.constructor
// Prefix all tokens
%define api.token.prefix {SCHEMA_}
// Check if variants are constructed and destroyed properly
%define parse.assert
// Trace the parser
%define parse.trace
// Use verbose parser errors
%define parse.error verbose
// Enable location tracking.
%locations
// Pass the compiler as parameter to yylex/yyparse.
%param { imlab::QueryParseContext &qc }
// ---------------------------------------------------------------------------------------------------
// Added to the header file and parser implementation before bison definitions.
// We include string for string tokens and forward declare the SchemaParseContext.
%code requires {
#include <string>
#include <tuple>
#include "imlab/query/query_parse_context.h"
}
// ---------------------------------------------------------------------------------------------------
// Import the compiler header in the implementation file
%code {
imlab::QueryParser::symbol_type yylex(imlab::QueryParseContext& qc);
}
// ---------------------------------------------------------------------------------------------------
// Token definitions
%token <int>            INTEGER_VALUE    "integer_value"
%token <std::string>    IDENTIFIER       "identifier"
%token SQ               "single_quote"
%token COMMA            "comma"
%token SELECT           "select"
%token FROM             "from"
%token AND              "and"
%token WHERE            "where"
%token EQ               "equals"
%token SEMICOLON        "semicolon"
%token INTEGER          "integer"
%token EOF 0            "eof"
// ---------------------------------------------------------------------------------------------------
%type <std::string> value;
%type <std::pair<std::string, std::string>> predicate;
%type <std::vector<std::pair<std::string, std::string>>> predicate_list;
%type <std::vector<std::string>> identifier_list;
// ---------------------------------------------------------------------------------------------------
// Tracing code that is called whenever a symbol is reported
%printer { for(int i = 0; i < $$.size(); ++i) { yyoutput << ((i > 0) ? ", " : "") << $$[i]; }} <std::vector<std::string>>;
%printer { yyoutput << $$.Name(); } <imlab::Type>;
// ---------------------------------------------------------------------------------------------------
%%

%start statement;

statement:
    SELECT identifier_list FROM identifier_list WHERE predicate_list SEMICOLON  { qc.buildAlgebraTree($2, $4, $6); }
;

identifier_list:
    identifier_list COMMA IDENTIFIER      { $1.push_back($3); std::swap($$, $1); }
  | IDENTIFIER                            { $$ = std::vector<std::string>{$1};   }
;

predicate_list:
    predicate_list AND predicate          { $1.push_back($3); std::swap($$, $1); }
  | predicate                             { $$ = std::vector<std::pair<std::string, std::string>>{$1}; }
  | %empty                                { $$ = std::vector<std::pair<std::string, std::string>>();   }
;

predicate:
    IDENTIFIER EQ value                   { $$ = std::pair<std::string, std::string>{$1, $3}; }
;

value:
    IDENTIFIER                            { $$ = $1; }
  | SQ IDENTIFIER SQ                      {
                                            std::ostringstream stringStream;
                                            stringStream << "\"" << $2 << "\"";
                                            $$ = stringStream.str();
                                          }
;

%%
// ---------------------------------------------------------------------------------------------------
// Define error function
void imlab::QueryParser::error(const location_type& l, const std::string& m) {
    qc.Error(l.begin.line, l.begin.column, m);
}
// ---------------------------------------------------------------------------------------------------

