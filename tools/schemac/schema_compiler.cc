// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
#include <ostream>
#include <sstream>
#include "imlab/algebra/iu.h"
#include "imlab/schema/schema.h"
#include "imlab/schema/schema_compiler.h"
#include "imlab/schema/schema_parse_context.h"
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------------------------------
namespace {
// ---------------------------------------------------------------------------------------------------
const char *kTab  = "    ";
const char *kTab2 = "        ";
// ---------------------------------------------------------------------------------------------------
const char *indexType(imlab::IndexType type) {
    switch (type) {
        case imlab::IndexType::kSTLUnorderedMap: return "std::unordered_map";
        case imlab::IndexType::kSTLMap: return "std::map";
        case imlab::IndexType::kSTXMap: return "stx::btree_map";
        default: throw imlab::SchemaCompilationError("Unknown index type");
    }
}
// ---------------------------------------------------------------------------------------------------
}  // namespace
// ---------------------------------------------------------------------------------------------------
// Compile a schema
void imlab::SchemaCompiler::Compile(Schema &schema) {
    // Write the header
    header_ <<
R"RAWTEXT(
#ifndef INCLUDE_IMLAB_DATASTORE_H_
#define INCLUDE_IMLAB_DATASTORE_H_
// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include "imlab/algebra/iu.h"
#include "imlab/infra/types.h"
#include "imlab/infra/hash.h"
#include "imlab/schema/schema_parse_context.h"
#include "imlab/schema/schema_compiler.h"
#include "stx/btree_map.h"

typedef size_t tid_t;

namespace imlab {

class Datastore {
 public:
)RAWTEXT";
    // Relation types
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        header_ << kTab << "struct " << table.id << "_row {" << std::endl;
        for (auto &column : table.columns) {
            header_ << kTab2 << column.type.Name() << " " << column.id << ";" << std::endl;
        }
        header_ << kTab << "};" << std::endl;
    }
    header_ << std::endl;

    // Relation vectors
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        header_ << kTab << "std::vector<" << table.id << "_row> " << table.id << "_data;" << std::endl;
    }
    header_ << std::endl;

    // Relation primary keys
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        if (table.primary_key.empty()) continue;
        header_ << kTab << indexType(table.index_type) << "<Key<";
        for (int j = 0; j < table.primary_key.size(); ++j) {
            header_ << (j > 0 ? ", " : "") << table.primary_key[j].type.Name();
        }
        header_ << ">, tid_t> " << table.id << "_pk;" << std::endl;
    }
    header_ << std::endl;

    // Relation IUs
    header_ << kTab << "static const std::unordered_multimap<std::string, IU> IUs;" << std::endl;
    header_ << std::endl;

    // Default constructor
    header_ << kTab << "Datastore()" << std::endl;
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        if (table.primary_key.empty()) continue;
        header_ << kTab2 << (i == 0 ? ": " : "") << table.id << "_data()," << std::endl;
        header_ << kTab2 << table.id << "_pk()";
        header_ << ((i == schema.tables.size() - 1) ? " {}" : ",") << std::endl;
    }

    // Declare CRUD methods
    header_ << R"RAWTEXT(
    template <typename T>
    size_t Size();

    template <typename T, typename K>
    K PrimaryKey(T &tuple);

    template <typename T>
    T &Get(tid_t tid);

    template <typename T, typename K>
    bool Find(K key, tid_t &tid);

    template <typename T>
    void Delete(tid_t tid);

    template <typename T>
    void Insert(T tuple);
};

}  // namespace imlab

#endif  // INCLUDE_IMLAB_DATASTORE_H_
)RAWTEXT";


    // Write the implementation
    impl_ << R"RAWTEXT(
// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------

#include "imlab/datastore.h"

using SchemaCompiler = imlab::SchemaCompiler;
using Type = imlab::Type;

namespace imlab {

// IUs

)RAWTEXT";
    // Generate ius
    impl_ << "const std::unordered_multimap<std::string, IU> Datastore::IUs {" << std::endl;
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        for (int j = 0; j < table.columns.size(); ++j) {
            auto &column = table.columns[j];
            impl_ << kTab << "{ \"" << table.id << "\", "
                << "IU(\"" << table.id << "\", \"" << column.id << "\", " << column.type.ConstructorName() << ")"
                << " }," << std::endl;
        }
    }
    impl_ << "};" << std::endl;

    impl_ << std::endl << "// Primary Keys" << std::endl << std::endl;

    // Generate primary key methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        std::stringstream key_type;
        key_type << "Key<";
        for (int j = 0; j < table.primary_key.size(); ++j) {
            key_type << (j > 0 ? ", ": "") << table.primary_key[j].type.Name();
        }
        key_type << ">";

        impl_ << "template <>" << std::endl;
        impl_ << key_type.str() << " Datastore::PrimaryKey<Datastore::" << table.id << "_row>(";
        impl_ << "Datastore::" << table.id << "_row &t) {" << std::endl;
        impl_ << kTab << "return " << key_type.str() << "(";
        for (int j = 0; j < table.primary_key.size(); ++j) {
            impl_ << (j > 0 ? ", t.": " t.") << table.primary_key[j].id;
        }
        impl_ << R"RAWTEXT();
}
)RAWTEXT";
    }

    impl_ << std::endl << "// Size" << std::endl << std::endl;

    // Generate size methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        impl_ << "template <>" << std::endl;
        impl_ << "size_t Datastore::Size<Datastore::" << table.id << "_row>() {" << std::endl;
        impl_ << kTab << "auto &data = " << table.id << "_data;";
        impl_ << R"RAWTEXT(
    return data.size();
}
)RAWTEXT";
    }

    impl_ << std::endl << "// Get" << std::endl << std::endl;

    // Generate get methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        impl_ << "template <>" << std::endl;
        impl_ << "Datastore::" << table.id << "_row &Datastore::Get<Datastore::" << table.id << "_row>(tid_t tid) {" << std::endl;
        impl_ << kTab << "return " << table.id << "_data[tid];";
        impl_ << R"RAWTEXT(
}
)RAWTEXT";
    }

    impl_ << std::endl << "// Find" << std::endl << std::endl;

    // Generate find methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        if (table.primary_key.empty()) continue;
        impl_ << "template <>" << std::endl;
        impl_ << "bool Datastore::Find<Datastore::" << table.id << "_row>(Key<";
        for (int j = 0; j < table.primary_key.size(); ++j) {
            auto &column = table.primary_key[j];
            impl_ << (j > 0 ? ", " : "") << column.type.Name();
        }
        impl_ << "> key, tid_t &tid) {" << std::endl;
        impl_ << kTab << "auto &data = " << table.id << "_data;" << std::endl;
        impl_ << kTab << "auto &pk = " << table.id << "_pk;";
        impl_ << R"RAWTEXT(
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
)RAWTEXT";
    }

    impl_ << std::endl << "// Delete" << std::endl << std::endl;

    // Generate delete methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        impl_ << "template <>" << std::endl;
        impl_ << "void Datastore::Delete<Datastore::" << table.id << "_row>(tid_t tid) {" << std::endl;

        if (!table.primary_key.empty()) {
            // Has primary key?
            impl_ << "using KeyType = Key<";
            for (int j = 0; j < table.primary_key.size(); ++j) {
                impl_ << (j > 0 ? ", ": "") << table.primary_key[j].type.Name();
            }
            impl_ << ">;" << std::endl;
            impl_ << kTab << "auto &data = " << table.id << "_data;" << std::endl;
            impl_ << kTab << "auto &pk = " << table.id << "_pk;" << std::endl;
            impl_ << kTab << "auto &tuple = data[tid];" << std::endl;
            impl_ << kTab << "KeyType key = PrimaryKey<" << table.id << "_row, KeyType>(tuple);";
            impl_ << R"RAWTEXT(
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::)RAWTEXT" << table.id << R"RAWTEXT(_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
)RAWTEXT";
        } else {
            // Has no primary key
            impl_ << kTab << "auto &data = " << table.id << "_data;";
            impl_ << R"RAWTEXT(
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        std::swap(data[tid], data[other_tid]);
    }
    data.pop_back();
}
)RAWTEXT";
        }
    }

    // Generate insert methods
    for (int i = 0; i < schema.tables.size(); ++i) {
        auto &table = schema.tables[i];
        impl_ << "template <>" << std::endl;
        impl_ << "void Datastore::Insert<Datastore::" << table.id << "_row>(Datastore::" << table.id << "_row tuple) {" << std::endl;
        impl_ << kTab << "using KeyType = Key<";
        for (int j = 0; j < table.primary_key.size(); ++j) {
            impl_ << (j > 0 ? ", ": "") << table.primary_key[j].type.Name();
        }
        impl_ << ">;" << std::endl;
        impl_ << kTab << "auto &data = " << table.id << "_data;" << std::endl;
        if (!table.primary_key.empty()) {
            impl_ << kTab << "KeyType key = PrimaryKey<Datastore::" << table.id << "_row, KeyType>(tuple);" << std::endl;
            impl_ << kTab << "auto &pk = " << table.id << "_pk;" << std::endl;
            impl_ << R"RAWTEXT(
    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });)RAWTEXT";
        }
        impl_ << R"RAWTEXT(
    data.push_back(std::move(tuple));
}
)RAWTEXT";
    }


        impl_ << R"RAWTEXT(
}  // namespace imlab
)RAWTEXT";
}
// ---------------------------------------------------------------------------------------------------
