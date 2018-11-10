
// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------

#include "imlab/datastore.h"

using SchemaCompiler = imlab::SchemaCompiler;
using Type = imlab::Type;

namespace imlab {

// IUs

const std::unordered_multimap<std::string, IU> Datastore::IUs {
    { "warehouse", IU("warehouse", "w_id", Type::Integer()) },
    { "warehouse", IU("warehouse", "w_name", Type::Varchar(10)) },
    { "warehouse", IU("warehouse", "w_street_1", Type::Varchar(20)) },
    { "warehouse", IU("warehouse", "w_street_2", Type::Varchar(20)) },
    { "warehouse", IU("warehouse", "w_city", Type::Varchar(20)) },
    { "warehouse", IU("warehouse", "w_state", Type::Char(2)) },
    { "warehouse", IU("warehouse", "w_zip", Type::Char(9)) },
    { "warehouse", IU("warehouse", "w_tax", Type::Numeric(4, 4)) },
    { "warehouse", IU("warehouse", "w_ytd", Type::Numeric(12, 2)) },
    { "district", IU("district", "d_id", Type::Integer()) },
    { "district", IU("district", "d_w_id", Type::Integer()) },
    { "district", IU("district", "d_name", Type::Varchar(10)) },
    { "district", IU("district", "d_street_1", Type::Varchar(20)) },
    { "district", IU("district", "d_street_2", Type::Varchar(20)) },
    { "district", IU("district", "d_city", Type::Varchar(20)) },
    { "district", IU("district", "d_state", Type::Char(2)) },
    { "district", IU("district", "d_zip", Type::Char(9)) },
    { "district", IU("district", "d_tax", Type::Numeric(4, 4)) },
    { "district", IU("district", "d_ytd", Type::Numeric(12, 2)) },
    { "district", IU("district", "d_next_o_id", Type::Integer()) },
    { "customer", IU("customer", "c_id", Type::Integer()) },
    { "customer", IU("customer", "c_d_id", Type::Integer()) },
    { "customer", IU("customer", "c_w_id", Type::Integer()) },
    { "customer", IU("customer", "c_first", Type::Varchar(16)) },
    { "customer", IU("customer", "c_middle", Type::Char(2)) },
    { "customer", IU("customer", "c_last", Type::Varchar(16)) },
    { "customer", IU("customer", "c_street_1", Type::Varchar(20)) },
    { "customer", IU("customer", "c_street_2", Type::Varchar(20)) },
    { "customer", IU("customer", "c_city", Type::Varchar(20)) },
    { "customer", IU("customer", "c_state", Type::Char(2)) },
    { "customer", IU("customer", "c_zip", Type::Char(9)) },
    { "customer", IU("customer", "c_phone", Type::Char(16)) },
    { "customer", IU("customer", "c_since", Type::Timestamp()) },
    { "customer", IU("customer", "c_credit", Type::Char(2)) },
    { "customer", IU("customer", "c_credit_lim", Type::Numeric(12, 2)) },
    { "customer", IU("customer", "c_discount", Type::Numeric(4, 4)) },
    { "customer", IU("customer", "c_balance", Type::Numeric(12, 2)) },
    { "customer", IU("customer", "c_ytd_paymenr", Type::Numeric(12, 2)) },
    { "customer", IU("customer", "c_payment_cnt", Type::Numeric(4, 0)) },
    { "customer", IU("customer", "c_delivery_cnt", Type::Numeric(4, 0)) },
    { "customer", IU("customer", "c_data", Type::Varchar(500)) },
    { "history", IU("history", "h_c_id", Type::Integer()) },
    { "history", IU("history", "h_c_d_id", Type::Integer()) },
    { "history", IU("history", "h_c_w_id", Type::Integer()) },
    { "history", IU("history", "h_d_id", Type::Integer()) },
    { "history", IU("history", "h_w_id", Type::Integer()) },
    { "history", IU("history", "h_date", Type::Timestamp()) },
    { "history", IU("history", "h_amount", Type::Numeric(6, 2)) },
    { "history", IU("history", "h_data", Type::Varchar(24)) },
    { "neworder", IU("neworder", "no_o_id", Type::Integer()) },
    { "neworder", IU("neworder", "no_d_id", Type::Integer()) },
    { "neworder", IU("neworder", "no_w_id", Type::Integer()) },
    { "order", IU("order", "o_id", Type::Integer()) },
    { "order", IU("order", "o_d_id", Type::Integer()) },
    { "order", IU("order", "o_w_id", Type::Integer()) },
    { "order", IU("order", "o_c_id", Type::Integer()) },
    { "order", IU("order", "o_entry_d", Type::Timestamp()) },
    { "order", IU("order", "o_carrier_id", Type::Integer()) },
    { "order", IU("order", "o_ol_cnt", Type::Numeric(2, 0)) },
    { "order", IU("order", "o_all_local", Type::Numeric(1, 0)) },
    { "orderline", IU("orderline", "ol_o_id", Type::Integer()) },
    { "orderline", IU("orderline", "ol_d_id", Type::Integer()) },
    { "orderline", IU("orderline", "ol_w_id", Type::Integer()) },
    { "orderline", IU("orderline", "ol_number", Type::Integer()) },
    { "orderline", IU("orderline", "ol_i_id", Type::Integer()) },
    { "orderline", IU("orderline", "ol_supply_w_id", Type::Integer()) },
    { "orderline", IU("orderline", "ol_delivery_d", Type::Timestamp()) },
    { "orderline", IU("orderline", "ol_quantity", Type::Numeric(2, 0)) },
    { "orderline", IU("orderline", "ol_amount", Type::Numeric(6, 2)) },
    { "orderline", IU("orderline", "ol_dist_info", Type::Char(24)) },
    { "item", IU("item", "i_id", Type::Integer()) },
    { "item", IU("item", "i_im_id", Type::Integer()) },
    { "item", IU("item", "i_name", Type::Varchar(24)) },
    { "item", IU("item", "i_price", Type::Numeric(5, 2)) },
    { "item", IU("item", "i_data", Type::Varchar(50)) },
    { "stock", IU("stock", "s_i_id", Type::Integer()) },
    { "stock", IU("stock", "s_w_id", Type::Integer()) },
    { "stock", IU("stock", "s_quantity", Type::Numeric(4, 0)) },
    { "stock", IU("stock", "s_dist_01", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_02", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_03", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_04", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_05", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_06", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_07", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_08", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_09", Type::Char(24)) },
    { "stock", IU("stock", "s_dist_10", Type::Char(24)) },
    { "stock", IU("stock", "s_ytd", Type::Numeric(8, 0)) },
    { "stock", IU("stock", "s_order_cnt", Type::Numeric(4, 0)) },
    { "stock", IU("stock", "s_remote_cnt", Type::Numeric(4, 0)) },
    { "stock", IU("stock", "s_data", Type::Varchar(50)) },
};

// Primary Keys

template <>
Key<Integer> Datastore::PrimaryKey<Datastore::warehouse_row>(Datastore::warehouse_row &t) {
    return Key<Integer>( t.w_id);
}
template <>
Key<Integer, Integer> Datastore::PrimaryKey<Datastore::district_row>(Datastore::district_row &t) {
    return Key<Integer, Integer>( t.d_w_id, t.d_id);
}
template <>
Key<Integer, Integer, Integer> Datastore::PrimaryKey<Datastore::customer_row>(Datastore::customer_row &t) {
    return Key<Integer, Integer, Integer>( t.c_w_id, t.c_d_id, t.c_id);
}
template <>
Key<> Datastore::PrimaryKey<Datastore::history_row>(Datastore::history_row &t) {
    return Key<>();
}
template <>
Key<Integer, Integer, Integer> Datastore::PrimaryKey<Datastore::neworder_row>(Datastore::neworder_row &t) {
    return Key<Integer, Integer, Integer>( t.no_w_id, t.no_d_id, t.no_o_id);
}
template <>
Key<Integer, Integer, Integer> Datastore::PrimaryKey<Datastore::order_row>(Datastore::order_row &t) {
    return Key<Integer, Integer, Integer>( t.o_w_id, t.o_d_id, t.o_id);
}
template <>
Key<Integer, Integer, Integer, Integer> Datastore::PrimaryKey<Datastore::orderline_row>(Datastore::orderline_row &t) {
    return Key<Integer, Integer, Integer, Integer>( t.ol_w_id, t.ol_d_id, t.ol_o_id, t.ol_number);
}
template <>
Key<Integer> Datastore::PrimaryKey<Datastore::item_row>(Datastore::item_row &t) {
    return Key<Integer>( t.i_id);
}
template <>
Key<Integer, Integer> Datastore::PrimaryKey<Datastore::stock_row>(Datastore::stock_row &t) {
    return Key<Integer, Integer>( t.s_w_id, t.s_i_id);
}

// Size

template <>
size_t Datastore::Size<Datastore::warehouse_row>() {
    auto &data = warehouse_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::district_row>() {
    auto &data = district_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::customer_row>() {
    auto &data = customer_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::history_row>() {
    auto &data = history_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::neworder_row>() {
    auto &data = neworder_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::order_row>() {
    auto &data = order_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::orderline_row>() {
    auto &data = orderline_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::item_row>() {
    auto &data = item_data;
    return data.size();
}
template <>
size_t Datastore::Size<Datastore::stock_row>() {
    auto &data = stock_data;
    return data.size();
}

// Get

template <>
Datastore::warehouse_row &Datastore::Get<Datastore::warehouse_row>(tid_t tid) {
    return warehouse_data[tid];
}
template <>
Datastore::district_row &Datastore::Get<Datastore::district_row>(tid_t tid) {
    return district_data[tid];
}
template <>
Datastore::customer_row &Datastore::Get<Datastore::customer_row>(tid_t tid) {
    return customer_data[tid];
}
template <>
Datastore::history_row &Datastore::Get<Datastore::history_row>(tid_t tid) {
    return history_data[tid];
}
template <>
Datastore::neworder_row &Datastore::Get<Datastore::neworder_row>(tid_t tid) {
    return neworder_data[tid];
}
template <>
Datastore::order_row &Datastore::Get<Datastore::order_row>(tid_t tid) {
    return order_data[tid];
}
template <>
Datastore::orderline_row &Datastore::Get<Datastore::orderline_row>(tid_t tid) {
    return orderline_data[tid];
}
template <>
Datastore::item_row &Datastore::Get<Datastore::item_row>(tid_t tid) {
    return item_data[tid];
}
template <>
Datastore::stock_row &Datastore::Get<Datastore::stock_row>(tid_t tid) {
    return stock_data[tid];
}

// Find

template <>
bool Datastore::Find<Datastore::warehouse_row>(Key<Integer> key, tid_t &tid) {
    auto &data = warehouse_data;
    auto &pk = warehouse_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::district_row>(Key<Integer, Integer> key, tid_t &tid) {
    auto &data = district_data;
    auto &pk = district_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::customer_row>(Key<Integer, Integer, Integer> key, tid_t &tid) {
    auto &data = customer_data;
    auto &pk = customer_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::neworder_row>(Key<Integer, Integer, Integer> key, tid_t &tid) {
    auto &data = neworder_data;
    auto &pk = neworder_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::order_row>(Key<Integer, Integer, Integer> key, tid_t &tid) {
    auto &data = order_data;
    auto &pk = order_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::orderline_row>(Key<Integer, Integer, Integer, Integer> key, tid_t &tid) {
    auto &data = orderline_data;
    auto &pk = orderline_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::item_row>(Key<Integer> key, tid_t &tid) {
    auto &data = item_data;
    auto &pk = item_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}
template <>
bool Datastore::Find<Datastore::stock_row>(Key<Integer, Integer> key, tid_t &tid) {
    auto &data = stock_data;
    auto &pk = stock_pk;
    auto iter = pk.find(key);
    if (iter == pk.end()) {
        return false;
    } else {
        tid = iter->second;
        return true;
    }
}

// Delete

template <>
void Datastore::Delete<Datastore::warehouse_row>(tid_t tid) {
using KeyType = Key<Integer>;
    auto &data = warehouse_data;
    auto &pk = warehouse_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<warehouse_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::warehouse_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::district_row>(tid_t tid) {
using KeyType = Key<Integer, Integer>;
    auto &data = district_data;
    auto &pk = district_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<district_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::district_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::customer_row>(tid_t tid) {
using KeyType = Key<Integer, Integer, Integer>;
    auto &data = customer_data;
    auto &pk = customer_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<customer_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::customer_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::history_row>(tid_t tid) {
    auto &data = history_data;
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        std::swap(data[tid], data[other_tid]);
    }
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::neworder_row>(tid_t tid) {
using KeyType = Key<Integer, Integer, Integer>;
    auto &data = neworder_data;
    auto &pk = neworder_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<neworder_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::neworder_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::order_row>(tid_t tid) {
using KeyType = Key<Integer, Integer, Integer>;
    auto &data = order_data;
    auto &pk = order_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<order_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::order_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::orderline_row>(tid_t tid) {
using KeyType = Key<Integer, Integer, Integer, Integer>;
    auto &data = orderline_data;
    auto &pk = orderline_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<orderline_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::orderline_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::item_row>(tid_t tid) {
using KeyType = Key<Integer>;
    auto &data = item_data;
    auto &pk = item_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<item_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::item_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Delete<Datastore::stock_row>(tid_t tid) {
using KeyType = Key<Integer, Integer>;
    auto &data = stock_data;
    auto &pk = stock_pk;
    auto &tuple = data[tid];
    KeyType key = PrimaryKey<stock_row, KeyType>(tuple);
    if (tid + 1 < data.size()) {
        auto other_tid = data.size() - 1;
        KeyType other_key = PrimaryKey<Datastore::stock_row, KeyType>(data[other_tid]);
        std::swap(data[tid], data[other_tid]);
        pk[other_key] = tid;
    }
    pk.erase(pk.find(key));
    data.pop_back();
}
template <>
void Datastore::Insert<Datastore::warehouse_row>(Datastore::warehouse_row tuple) {
    using KeyType = Key<Integer>;
    auto &data = warehouse_data;
    KeyType key = PrimaryKey<Datastore::warehouse_row, KeyType>(tuple);
    auto &pk = warehouse_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::district_row>(Datastore::district_row tuple) {
    using KeyType = Key<Integer, Integer>;
    auto &data = district_data;
    KeyType key = PrimaryKey<Datastore::district_row, KeyType>(tuple);
    auto &pk = district_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::customer_row>(Datastore::customer_row tuple) {
    using KeyType = Key<Integer, Integer, Integer>;
    auto &data = customer_data;
    KeyType key = PrimaryKey<Datastore::customer_row, KeyType>(tuple);
    auto &pk = customer_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::history_row>(Datastore::history_row tuple) {
    using KeyType = Key<>;
    auto &data = history_data;

    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::neworder_row>(Datastore::neworder_row tuple) {
    using KeyType = Key<Integer, Integer, Integer>;
    auto &data = neworder_data;
    KeyType key = PrimaryKey<Datastore::neworder_row, KeyType>(tuple);
    auto &pk = neworder_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::order_row>(Datastore::order_row tuple) {
    using KeyType = Key<Integer, Integer, Integer>;
    auto &data = order_data;
    KeyType key = PrimaryKey<Datastore::order_row, KeyType>(tuple);
    auto &pk = order_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::orderline_row>(Datastore::orderline_row tuple) {
    using KeyType = Key<Integer, Integer, Integer, Integer>;
    auto &data = orderline_data;
    KeyType key = PrimaryKey<Datastore::orderline_row, KeyType>(tuple);
    auto &pk = orderline_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::item_row>(Datastore::item_row tuple) {
    using KeyType = Key<Integer>;
    auto &data = item_data;
    KeyType key = PrimaryKey<Datastore::item_row, KeyType>(tuple);
    auto &pk = item_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}
template <>
void Datastore::Insert<Datastore::stock_row>(Datastore::stock_row tuple) {
    using KeyType = Key<Integer, Integer>;
    auto &data = stock_data;
    KeyType key = PrimaryKey<Datastore::stock_row, KeyType>(tuple);
    auto &pk = stock_pk;

    auto iter = pk.find(key);
    if (iter != pk.end()) throw std::runtime_error("Duplicate key");
    pk.insert({ key, data.size() });
    data.push_back(std::move(tuple));
}

}  // namespace imlab
