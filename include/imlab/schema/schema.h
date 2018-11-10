// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_SCHEMA_SCHEMA_H_
#define INCLUDE_IMLAB_SCHEMA_SCHEMA_H_
// ---------------------------------------------------------------------------
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include "imlab/infra/types.h"
// ---------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------
// A type
struct Type {
    // Type class
    enum Class: uint8_t {
        kInteger,
        kTimestamp,
        kNumeric,
        kChar,
        kVarchar,
    };
    // The type class
    Class tclass;
    // The type argument (if any)
    union {
        struct {
            uint32_t length;
            uint32_t precision;
        };
    };


    // Static methods to construct a column
    static inline Type Integer();
    static inline Type Timestamp();
    static inline Type Numeric(unsigned length, unsigned precision);
    static inline Type Char(unsigned length);
    static inline Type Varchar(unsigned length);

    // Get type name
    inline std::string Name() const {
        std::stringstream out;
        switch (tclass) {
            case imlab::Type::kInteger:    out << "Integer"; break;
            case imlab::Type::kTimestamp:  out << "Timestamp"; break;
            case imlab::Type::kNumeric:    out << "Numeric<" << length << ", " << precision << ">"; break;
            case imlab::Type::kChar:       out << "Char<" << length << ">"; break;
            case imlab::Type::kVarchar:    out << "Varchar<" << length << ">"; break;
            default: break;
        }
        return out.str();
    }
    // Get type class name
    inline std::string ClassName() const {
        std::stringstream out;
        switch (tclass) {
            case imlab::Type::kInteger:    out << "Type::kInteger"; break;
            case imlab::Type::kTimestamp:  out << "Type::kTimestamp"; break;
            case imlab::Type::kNumeric:    out << "Type::kNumeric"; break;
            case imlab::Type::kChar:       out << "Type::kChar"; break;
            case imlab::Type::kVarchar:    out << "Type::kVarchar"; break;
            default: break;
        }
        return out.str();
    }
    // Get type constructor
    inline std::string ConstructorName() const {
        std::stringstream out;
        switch (tclass) {
            case imlab::Type::kInteger:    out << "Type::Integer()"; break;
            case imlab::Type::kTimestamp:  out << "Type::Timestamp()"; break;
            case imlab::Type::kNumeric:    out << "Type::Numeric(" << length << ", " << precision << ")"; break;
            case imlab::Type::kChar:       out << "Type::Char(" << length << ")"; break;
            case imlab::Type::kVarchar:    out << "Type::Varchar(" << length << ")"; break;
            default: break;
        }
        return out.str();
    }

    bool IsString() const {
        switch (tclass) {
            case imlab::Type::kChar:
            case imlab::Type::kVarchar:
                return true;
            default:
                return false;
        }
    }
};
// ---------------------------------------------------------------------------------------------------
Type Type::Integer()    {
    Type t;
    t.tclass = kInteger;
    return t;
}
Type Type::Timestamp()  {
    Type t;
    t.tclass = kTimestamp;
    return t;
}
Type Type::Numeric(unsigned length, unsigned precision) {
    Type t;
    t.tclass = kNumeric;
    t.length = length;
    t.precision = precision;
    return t;
}
Type Type::Char(unsigned length) {
    Type t;
    t.tclass = kChar;
    t.length = length;
    return t;
}
Type Type::Varchar(unsigned length) {
    Type t;
    t.tclass = kVarchar;
    t.length = length;
    return t;
}
// ---------------------------------------------------------------------------
// An index type
enum IndexType: uint8_t {
    kSTLUnorderedMap,
    kSTLMap,
    kSTXMap
};
// ---------------------------------------------------------------------------
// A single column
struct Column {
    // Name of the column
    const std::string id;
    // Type of the column
    const Type type;

    // Constructor
    explicit Column(const std::string &id, Type type = Type::Integer())
        : id(id), type(type) {}
};
// ---------------------------------------------------------------------------
// A single table
struct Table {
    // Name of the table
    const std::string id;
    // Columns
    const std::vector<Column> columns;
    // Primary key
    const std::vector<Column> primary_key;
    // Index type
    const IndexType index_type;

    // Constructor
    Table(const std::string &id, std::vector<Column> &&columns, std::vector<Column> &&primary_key, IndexType index_type)
        : id(id), columns(std::move(columns)), primary_key(std::move(primary_key)), index_type(index_type) {}
};
// ---------------------------------------------------------------------------
// A single index
struct Index {
    // Name of the index
    const std::string id;
    // Name of the indexed table
    const std::string table_id;
    // Columns
    std::vector<Column> columns;
    // Index type
    const IndexType index_type;

    // Constructor
    Index(const std::string &id, const std::string &table_id, std::vector<Column> &&columns, IndexType index_type)
        : id(id), table_id(table_id), columns(columns), index_type(index_type) {}
};
// ---------------------------------------------------------------------------
// A complete schema
struct Schema {
    // Tables
    const std::vector<Table> tables;
    // Indexes
    const std::vector<Index> indexes;

    // Constructor
    Schema(std::vector<Table> &&tables, std::vector<Index> &&indexes)
        : tables(std::move(tables)), indexes(std::move(indexes)) {}
};
// ---------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_SCHEMA_SCHEMA_H_
// ---------------------------------------------------------------------------
