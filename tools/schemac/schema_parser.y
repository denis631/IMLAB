// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
%skeleton "lalr1.cc"
%require "3.0.4"
// ---------------------------------------------------------------------------------------------------
// Write a parser header file
%defines
// Define the parser class name
%define parser_class_name {SchemaParser}
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
%param { imlab::SchemaParseContext &sc }
// ---------------------------------------------------------------------------------------------------
// Added to the header file and parser implementation before bison definitions.
// We include string for string tokens and forward declare the SchemaParseContext.
%code requires {
#include <string>
#include <tuple>
#include "imlab/schema/schema_parse_context.h"
}
// ---------------------------------------------------------------------------------------------------
// Import the compiler header in the implementation file
%code {
imlab::SchemaParser::symbol_type yylex(imlab::SchemaParseContext& sc);
}
// ---------------------------------------------------------------------------------------------------
// Token definitions
%token <int>            INTEGER_VALUE    "integer_value"
%token <std::string>    IDENTIFIER       "identifier"
%token LP               "left_paranthesis"
%token RP               "right_paranthesis"
%token DQ               "double_quotes"
%token COMMA            "comma"
%token EQ               "equals"
%token SEMICOLON        "semicolon"
%token CHAR             "char"
%token CREATE           "create"
%token INDEX            "index"
%token INDEX_TYPE       "index_type"
%token INTEGER          "integer"
%token NOT              "not"
%token NULL             "null"
%token NUMERIC          "numeric"
%token ON               "on"
%token PRIMARY          "primary"
%token KEY              "key"
%token TABLE            "table"
%token TIMESTAMP        "timestamp"
%token VARCHAR          "varchar"
%token WITH             "with"
%token EOF 0            "eof"
// ---------------------------------------------------------------------------------------------------
%type <imlab::Type> column_type;
%type <std::vector<std::pair<std::string, std::string>>> key_value_list;
%type <std::vector<std::pair<std::string, std::string>>> optional_key_value_list;
%type <std::vector<std::string>> identifier_list;
%type <std::string> identifier;
// ---------------------------------------------------------------------------------------------------
// Tracing code that is called whenever a symbol is reported
%printer { for(int i = 0; i < $$.size(); ++i) { yyoutput << ((i > 0) ? ", " : "") << $$[i]; }} <std::vector<std::string>>;
%printer { yyoutput << $$.Name(); } <imlab::Type>;
// ---------------------------------------------------------------------------------------------------
%%

%start optional_schema_statements;

optional_schema_statements:
    schema_statements
 |  %empty
    ;

schema_statements:
    schema_statements schema_statement
 |  schema_statement
    ;

schema_statement:
    CREATE TABLE identifier LP create_table_element_list RP optional_key_value_list SEMICOLON       { sc.defineTable($3, std::move($7)); }
 |  CREATE INDEX identifier ON identifier LP identifier_list RP optional_key_value_list SEMICOLON   { sc.defineIndex($3, $5, std::move($7), std::move($9)); }
    ;

optional_key_value_list:
    WITH LP key_value_list RP                           { std::swap($$, $3); }
 |  %empty                                              { $$ = std::vector<std::pair<std::string, std::string>>(); }
    ;

key_value_list:
    key_value_list COMMA IDENTIFIER EQ IDENTIFIER       { $1.push_back(std::make_pair($3, $5)); std::swap($$, $1); }
 |  IDENTIFIER EQ IDENTIFIER                            { $$ = std::vector<std::pair<std::string, std::string>> { std::make_pair($1, $3) }; }
 |  %empty                                              { $$ = std::vector<std::pair<std::string, std::string>>(); }
    ;

create_table_element_list:
    create_table_element_list COMMA create_table_element
 |  create_table_element
 |  %empty
    ;

create_table_element:
    identifier column_type NOT NULL                     { sc.defineTableColumn($1, $2); }
 |  PRIMARY KEY LP identifier_list RP                   { sc.defineTablePrimaryKey(std::move($4)); }
    ;

column_type:
    INTEGER                                             { $$ = Type::Integer(); }
 |  TIMESTAMP                                           { $$ = Type::Timestamp(); }
 |  NUMERIC LP INTEGER_VALUE COMMA INTEGER_VALUE RP     { $$ = Type::Numeric($3, $5); }
 |  CHAR    LP INTEGER_VALUE RP                         { $$ = Type::Char($3); }
 |  VARCHAR LP INTEGER_VALUE RP                         { $$ = Type::Varchar($3); }
    ;

identifier_list:
    identifier_list COMMA identifier                    { $1.push_back($3); std::swap($$, $1); }
 |  identifier                                          { $$ = std::vector<std::string>{ $1 }; }
    ;

identifier:
    IDENTIFIER                                          { $$ = $1; }
 |  DQ IDENTIFIER DQ                                    { $$ = $2; }
    ;

%%
// ---------------------------------------------------------------------------------------------------
// Define error function
void imlab::SchemaParser::error(const location_type& l, const std::string& m) {
    sc.Error(l.begin.line, l.begin.column, m);
}
// ---------------------------------------------------------------------------------------------------
