// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
#include "imlab/schema/schema_parse_context.h"
#include "./gen/schema_parser.h"
#include <sstream>
#include <unordered_set>
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------------------------------
using SchemaCompilationError = imlab::SchemaCompilationError;
using SchemaParseContext = imlab::SchemaParseContext;
using Table = imlab::Table;
using Schema = imlab::Schema;
using Type = imlab::Type;
// ---------------------------------------------------------------------------------------------------
// Constructor
SchemaParseContext::SchemaParseContext(bool trace_scanning, bool trace_parsing)
    : trace_scanning_(trace_scanning), trace_parsing_(trace_parsing),
        tables_(), table_ids_(), indexes_(), tmp_columns_(), tmp_primary_key_(), tmp_column_ids_() {}
// ---------------------------------------------------------------------------------------------------
// Destructor
SchemaParseContext::~SchemaParseContext() {}
// ---------------------------------------------------------------------------------------------------
// Parse a string
Schema SchemaParseContext::Parse(std::istream &in) {
    beginScan(in);
    imlab::SchemaParser parser(*this);
    parser.set_debug_level(trace_parsing_);
    parser.parse();
    endScan();
    return finalize();
}
// ---------------------------------------------------------------------------------------------------
// Yield an error
void SchemaParseContext::Error(const std::string& m) {
    throw SchemaCompilationError(m);
}
// ---------------------------------------------------------------------------------------------------
// Yield an error
void SchemaParseContext::Error(uint32_t line, uint32_t column, const std::string &err) {
    std::stringstream ss;
    ss << "[ l=" << line << " c=" << column << " ] " << err << std::endl;
    throw SchemaCompilationError(ss.str());
}
// ---------------------------------------------------------------------------------------------------
// Define a table
void SchemaParseContext::defineTable(const std::string &id, std::vector<std::pair<std::string, std::string>> options) {
    // Check if there is already a table with this name
    if (table_ids_.find(id) != table_ids_.end()) {
        throw SchemaCompilationError(std::string("Duplicate table identifier: ") + id);
    }
    // Register table
    table_ids_.insert({ id, tables_.size() });

    // Resolve all columns of the primary key
    std::vector<Column> primary_key;
    if (!!tmp_primary_key_) {
        for (auto &pk_col : *tmp_primary_key_) {
            auto col_ofs = tmp_column_ids_.find(pk_col.id);
            if (col_ofs == tmp_column_ids_.end()) {
                std::stringstream ss;
                ss << "Table primary key '" << id << "' references unknown column: " << pk_col.id;
                throw SchemaCompilationError(ss.str());
            }
            auto &column = tmp_columns_[col_ofs->second];
            primary_key.emplace_back(column.id, column.type);
        }
    }

    // Check options
    IndexType index_type = IndexType::kSTLUnorderedMap;
    for (auto &option : options) {
        if (option.first == "key_index_type") {
            if (option.second == "unordered_map") {
                index_type = IndexType::kSTLUnorderedMap;
                continue;
            } else if (option.second == "map") {
                index_type = IndexType::kSTLMap;
                continue;
            } else if (option.second == "btree_map") {
                index_type = IndexType::kSTXMap;
                continue;
            }
        }
        std::stringstream ss;
        ss << "Table '" << id << "' has unknown option: " << option.first << "=" << option.second;
        throw SchemaCompilationError(ss.str());
    }

    // Store table
    tables_.emplace_back(id, std::move(tmp_columns_), std::move(primary_key), index_type);

    // Clear things
    tmp_columns_.clear();
    tmp_column_ids_.clear();
    tmp_primary_key_.reset();
}
// ---------------------------------------------------------------------------------------------------
// Define a column definition of the current table
void SchemaParseContext::defineTableColumn(const std::string &id, Type type) {
    // Check if there is already a column with this name
    if (tmp_column_ids_.find(id) != tmp_column_ids_.end()) {
        throw SchemaCompilationError(std::string("Duplicate column identifier: ") + id);
    }
    // Add the column
    tmp_columns_.emplace_back(id, type);
    // Add the column id
    tmp_column_ids_.insert({ id, tmp_columns_.size() - 1 });
}
// ---------------------------------------------------------------------------------------------------
// Define the primary key of the current table
void SchemaParseContext::defineTablePrimaryKey(std::vector<std::string> &&columns) {
    // Duplicate primary key definition?
    if (tmp_primary_key_ != nullptr) {
        throw SchemaCompilationError(std::string("Duplicate primary key definition"));
    }

    // Build the column array
    // Note that we (potentially) cannot resolve all column identifiers here
    // Resolve the types when we define the table (need to know all columns there)
    tmp_primary_key_ = std::make_unique<std::vector<Column>>();
    for (auto &column : columns) {
        tmp_primary_key_->emplace_back(column);
    }
}
// ---------------------------------------------------------------------------------------------------
// Define an index
void SchemaParseContext::defineIndex(
        const std::string &id,
        const std::string &table,
        std::vector<std::string> &&column_ids,
        std::vector<std::pair<std::string, std::string>> options) {
    // Build unresolved columns
    std::vector<Column> columns;
    for (auto &column_id : column_ids) {
        columns.emplace_back(column_id);
    }

    // Check options
    IndexType index_type = IndexType::kSTLUnorderedMap;
    for (auto &option : options) {
        if (option.first == "index_type") {
            if (option.second == "unordered_map") {
                index_type = IndexType::kSTLUnorderedMap;
                continue;
            } else if (option.second == "map") {
                index_type = IndexType::kSTLMap;
                continue;
            } else if (option.second == "btree_map") {
                index_type = IndexType::kSTXMap;
                continue;
            }
        }
        std::stringstream ss;
        ss << "Index '" << id << "' has unknown option: " << option.first << "=" << option.second;
        throw SchemaCompilationError(ss.str());
    }

    // Add index
    indexes_.emplace_back(id, table, std::move(columns), index_type);
}
// ---------------------------------------------------------------------------------------------------
Schema SchemaParseContext::finalize() {
    // ---------------------------
    // Resolve the index columns
    // ---------------------------
    for (auto &idx : indexes_) {
        // Check if the table exists
        auto table_iter = table_ids_.find(idx.table_id);
        if (table_iter == table_ids_.end()) {
            std::stringstream ss;
            ss << "Index '" << idx.id << "' refers to unknown table: " << idx.table_id;
            throw SchemaCompilationError(ss.str());
        }

        // Build set of unmatched columns
        std::unordered_set<std::string> unmatched_columns;
        for (auto &idx_column : idx.columns) unmatched_columns.insert(idx_column.id);

        // Resolve all columns
        std::vector<Column> resolved_columns;
        for (auto &column : tables_[table_iter->second].columns) {
            auto unmatched_iter = unmatched_columns.find(column.id);
            if (unmatched_iter != unmatched_columns.end()) {
                unmatched_columns.erase(unmatched_iter);
                resolved_columns.emplace_back(column.id, column.type);
            }
        }

        // Make sure all columns have been found
        if (!unmatched_columns.empty()) {
            std::stringstream ss;
            ss << "Index '" << idx.id << "' references unknown column(s): ";
            bool first = true;
            for (auto &unmatched_column : unmatched_columns) {
                ss << ((!first) ? ", " : "") << unmatched_column;
            }
            throw SchemaCompilationError(ss.str());
        }

        // Overwrite columns with resolved columns
        idx.columns = std::move(resolved_columns);
    }

    // Create schema
    Schema s(std::move(tables_), std::move(indexes_));

    // Clear things
    tables_.clear();
    table_ids_.clear();
    tmp_columns_.clear();
    tmp_column_ids_.clear();
    tmp_primary_key_.reset();

    return s;
}
// ---------------------------------------------------------------------------------------------------
