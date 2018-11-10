// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_SCHEMA_SCHEMA_PARSE_CONTEXT_H_
#define INCLUDE_IMLAB_SCHEMA_SCHEMA_PARSE_CONTEXT_H_
// ---------------------------------------------------------------------------------------------------
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include "imlab/schema/schema.h"
// ---------------------------------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------------------------------
struct SchemaParser;
struct SchemaCompiler;
// ---------------------------------------------------------------------------------------------------
// Schema compiler
class SchemaParseContext {
    friend SchemaParser;

 public:
    // Constructor
    explicit SchemaParseContext(bool trace_scanning = false, bool trace_parsing = false);
    // Destructor
    virtual ~SchemaParseContext();

    // Parse an istream
    Schema Parse(std::istream &in);

    // Throw an error
    void Error(uint32_t line, uint32_t column, const std::string &err);
    // Throw an error
    void Error(const std::string &m);

 private:
    // Begin a scan
    void beginScan(std::istream &in);
    // End a scan
    void endScan();

    // Define a table
    void defineTable(const std::string &id, std::vector<std::pair<std::string, std::string>> options);
    // Define a column definition of the current table
    void defineTableColumn(const std::string &id, Type type);
    // Define the primary key of the current table
    void defineTablePrimaryKey(std::vector<std::string> &&columns);
    // Define an index
    void defineIndex(
        const std::string &id,
        const std::string &table,
        std::vector<std::string> &&columns,
        std::vector<std::pair<std::string, std::string>> options);

    // Finalize the parsing
    Schema finalize();

    // Trace the scanning
    bool trace_scanning_;
    // Trace the parsing
    bool trace_parsing_;

    // The defined tables
    std::vector<Table> tables_;
    // Table id map
    std::unordered_map<std::string, size_t> table_ids_;

    // The defined indexes
    std::vector<Index> indexes_;

    // Temporary columns
    std::vector<Column> tmp_columns_;
    // Temporary primary key index
    std::unique_ptr<std::vector<Column>> tmp_primary_key_;
    // Temporary column id map
    std::unordered_map<std::string, size_t> tmp_column_ids_;
};
// ---------------------------------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_SCHEMA_SCHEMA_PARSE_CONTEXT_H_
// ---------------------------------------------------------------------------------------------------
