// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include "imlab/database.h"
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include "imlab/datastore.h"
#include "imlab/infra/hash_table.h"
#include "imlab/infra/error.h"

namespace {

// Split a string and write it with a writer
template<typename Writer>
void Split(const std::string &s, char delim, Writer writer) {
    std::stringstream sstr(s);
    std::string token;
    while (std::getline(sstr, token, delim))
        *(writer++) = token;
}

// Split a string and return a vector of substrings
std::vector<std::string> Split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Split(s, delim, std::back_inserter(elems));
    return elems;
}

}  // namespace

namespace imlab {

Database::Database(): datastore_(std::make_unique<Datastore>()) {}
Database::~Database() {}

void Database::LoadWarehouse(std::istream &in) {
    std::string line_buffer;
    Datastore::warehouse_row w;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 9) { continue; }
        w.w_id = Integer(std::stoi(tokens[0]));
        w.w_name = Varchar<10>::castString(tokens[1].c_str(), tokens[1].length());
        w.w_street_1 = Varchar<20>::castString(tokens[2].c_str(), tokens[2].length());
        w.w_street_2 = Varchar<20>::castString(tokens[3].c_str(), tokens[3].length());
        w.w_city = Varchar<20>::castString(tokens[4].c_str(), tokens[4].length());
        w.w_state = Char<2>::castString(tokens[5].c_str(), tokens[5].length());
        w.w_zip = Char<9>::castString(tokens[6].c_str(), tokens[6].length());
        w.w_tax = Numeric<4, 4>::castString(tokens[7].c_str(), tokens[7].length());
        w.w_ytd = Numeric<12, 2>::castString(tokens[8].c_str(), tokens[8].length());
        datastore_->Insert(std::move(w));
    }
}

void Database::LoadDistrict(std::istream &in) {
    std::string line_buffer;
    Datastore::district_row d;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 11) { continue; }
        d.d_id = Integer(std::stoi(tokens[0]));
        d.d_w_id = Integer(std::stoi(tokens[1]));
        d.d_name = Varchar<10>::castString(tokens[2].c_str(), tokens[2].length());
        d.d_street_1 = Varchar<20>::castString(tokens[3].c_str(), tokens[3].length());
        d.d_street_2 = Varchar<20>::castString(tokens[4].c_str(), tokens[4].length());
        d.d_city = Varchar<20>::castString(tokens[5].c_str(), tokens[5].length());
        d.d_state = Char<2>::castString(tokens[6].c_str(), tokens[6].length());
        d.d_zip = Char<9>::castString(tokens[7].c_str(), tokens[7].length());
        d.d_tax = Numeric<4, 4>::castString(tokens[8].c_str(), tokens[8].length());
        d.d_ytd = Numeric<12, 2>::castString(tokens[9].c_str(), tokens[9].length());
        d.d_next_o_id = Integer(std::stoi(tokens[10]));
        datastore_->Insert(std::move(d));
    }
}

void Database::LoadCustomer(std::istream &in) {
    std::string line_buffer;
    Datastore::customer_row c;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 21) { continue; }
        c.c_id = Integer(std::stoi(tokens[0]));
        c.c_d_id = Integer(std::stoi(tokens[1]));
        c.c_w_id = Integer(std::stoi(tokens[2]));
        c.c_first = Varchar<16>::castString(tokens[3].c_str(), tokens[3].length());
        c.c_middle = Char<2>::castString(tokens[4].c_str(), tokens[4].length());
        c.c_last = Varchar<16>::castString(tokens[5].c_str(), tokens[5].length());
        c.c_street_1 = Varchar<20>::castString(tokens[6].c_str(), tokens[6].length());
        c.c_street_2 = Varchar<20>::castString(tokens[7].c_str(), tokens[7].length());
        c.c_city = Varchar<20>::castString(tokens[8].c_str(), tokens[8].length());
        c.c_state = Char<2>::castString(tokens[9].c_str(), tokens[9].length());
        c.c_zip = Char<9>::castString(tokens[10].c_str(), tokens[10].length());
        c.c_phone = Char<16>::castString(tokens[11].c_str(), tokens[11].length());
        c.c_since = Timestamp::castString(tokens[12].c_str(), tokens[12].length());
        c.c_credit = Char<2>::castString(tokens[13].c_str(), tokens[13].length());
        c.c_credit_lim = Numeric<12, 2>::castString(tokens[14].c_str(), tokens[14].length());
        c.c_discount = Numeric<4, 4>::castString(tokens[15].c_str(), tokens[15].length());
        c.c_balance = Numeric<12, 2>::castString(tokens[16].c_str(), tokens[16].length());
        c.c_ytd_paymenr = Numeric<12, 2>::castString(tokens[17].c_str(), tokens[17].length());
        c.c_payment_cnt = Numeric<4, 0>::castString(tokens[18].c_str(), tokens[18].length());
        c.c_delivery_cnt = Numeric<4, 0>::castString(tokens[19].c_str(), tokens[19].length());
        c.c_data = Varchar<500>::castString(tokens[20].c_str(), tokens[20].length());
        datastore_->Insert(std::move(c));
    }
}

void Database::LoadHistory(std::istream &in) {
    std::string line_buffer;
    Datastore::history_row h;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 8) { continue; }
        h.h_c_id = Integer(std::stoi(tokens[0]));
        h.h_c_d_id = Integer(std::stoi(tokens[1]));
        h.h_c_w_id = Integer(std::stoi(tokens[2]));
        h.h_d_id = Integer(std::stoi(tokens[3]));
        h.h_w_id = Integer(std::stoi(tokens[4]));
        h.h_date = Timestamp::castString(tokens[5].c_str(), tokens[5].length());
        h.h_amount = Numeric<6, 2>::castString(tokens[6].c_str(), tokens[6].length());
        h.h_data = Varchar<24>::castString(tokens[7].c_str(), tokens[7].length());
        datastore_->Insert(std::move(h));
    }
}

void Database::LoadNewOrder(std::istream &in) {
    std::string line_buffer;
    Datastore::neworder_row no;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 3) { continue; }
        no.no_o_id = Integer(std::stoi(tokens[0]));
        no.no_d_id = Integer(std::stoi(tokens[1]));
        no.no_w_id = Integer(std::stoi(tokens[2]));
        datastore_->Insert(std::move(no));
    }
}

void Database::LoadOrder(std::istream &in) {
    std::string line_buffer;
    Datastore::order_row o;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 8) { continue; }
        o.o_id = Integer(std::stoi(tokens[0]));
        o.o_d_id = Integer(std::stoi(tokens[1]));
        o.o_w_id = Integer(std::stoi(tokens[2]));
        o.o_c_id = Integer(std::stoi(tokens[3]));
        o.o_entry_d = Timestamp::castString(tokens[4].c_str(), tokens[4].length());
        o.o_carrier_id = Integer(std::stoi(tokens[5]));
        o.o_ol_cnt = Numeric<2, 0>::castString(tokens[6].c_str(), tokens[6].length());
        o.o_all_local = Numeric<1, 0>::castString(tokens[7].c_str(), tokens[7].length());
        datastore_->Insert(std::move(o));
    }
}

void Database::LoadOrderLine(std::istream &in) {
    std::string line_buffer;
    Datastore::orderline_row ol;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 10) { continue; }
        ol.ol_o_id = Integer(std::stoi(tokens[0]));
        ol.ol_d_id = Integer(std::stoi(tokens[1]));
        ol.ol_w_id = Integer(std::stoi(tokens[2]));
        ol.ol_number = Integer(std::stoi(tokens[3]));
        ol.ol_i_id = Integer(std::stoi(tokens[4]));
        ol.ol_supply_w_id = Integer(std::stoi(tokens[5]));
        ol.ol_delivery_d = Timestamp::castString(tokens[6].c_str(), tokens[6].length());
        ol.ol_quantity = Numeric<2, 0>::castString(tokens[7].c_str(), tokens[7].length());
        ol.ol_amount = Numeric<6, 2>::castString(tokens[8].c_str(), tokens[8].length());
        ol.ol_dist_info = Char<24>::castString(tokens[9].c_str(), tokens[9].length());
        datastore_->Insert(std::move(ol));
    }
}

void Database::LoadItem(std::istream &in) {
    std::string line_buffer;
    Datastore::item_row i;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 5) { continue; }
        i.i_id = Integer(std::stoi(tokens[0]));
        i.i_im_id = Integer(std::stoi(tokens[1]));
        i.i_name = Varchar<24>::castString(tokens[2].c_str(), tokens[2].length());
        i.i_price = Numeric<5, 2>::castString(tokens[3].c_str(), tokens[3].length());
        i.i_data = Varchar<50>::castString(tokens[4].c_str(), tokens[4].length());
        datastore_->Insert(std::move(i));
    }
}

void Database::LoadStock(std::istream& in) {
    std::string line_buffer;
    Datastore::stock_row s;
    while (std::getline(in, line_buffer)) {
        auto tokens = Split(line_buffer, '|');
        if (tokens.size() < 17) { continue; }
        s.s_i_id = Integer(std::stoi(tokens[0]));
        s.s_w_id = Integer(std::stoi(tokens[1]));
        s.s_quantity = Numeric<4, 0>::castString(tokens[2].c_str(), tokens[2].length());
        s.s_dist_01 = Char<24>::castString(tokens[3].c_str(), tokens[3].length());
        s.s_dist_02 = Char<24>::castString(tokens[4].c_str(), tokens[4].length());
        s.s_dist_03 = Char<24>::castString(tokens[5].c_str(), tokens[5].length());
        s.s_dist_04 = Char<24>::castString(tokens[6].c_str(), tokens[6].length());
        s.s_dist_05 = Char<24>::castString(tokens[7].c_str(), tokens[7].length());
        s.s_dist_06 = Char<24>::castString(tokens[8].c_str(), tokens[8].length());
        s.s_dist_07 = Char<24>::castString(tokens[9].c_str(), tokens[9].length());
        s.s_dist_08 = Char<24>::castString(tokens[10].c_str(), tokens[10].length());
        s.s_dist_09 = Char<24>::castString(tokens[11].c_str(), tokens[11].length());
        s.s_dist_10 = Char<24>::castString(tokens[12].c_str(), tokens[12].length());
        s.s_ytd = Numeric<8, 0>::castString(tokens[13].c_str(), tokens[13].length());
        s.s_order_cnt = Numeric<4, 0>::castString(tokens[14].c_str(), tokens[14].length());
        s.s_remote_cnt = Numeric<4, 0>::castString(tokens[15].c_str(), tokens[15].length());
        s.s_data = Varchar<50>::castString(tokens[16].c_str(), tokens[16].length());
        datastore_->Insert(std::move(s));
    }
}

void Database::NewOrder(
        Integer w_id,
        Integer d_id,
        Integer c_id,
        Integer items,
        std::array<Integer, 15> &supware,
        std::array<Integer, 15> &itemid,
        std::array<Integer, 15> &qty,
        Timestamp datetime) {
    // select w_tax from warehouse w where w.w_id=w_id;
    size_t w_tid;
    if (!datastore_->Find<Datastore::warehouse_row>(Key<Integer>(w_id), w_tid)) {
        throw TransactionRollback("Warehouse not found");
    }
    auto w_tax = datastore_->Get<Datastore::warehouse_row>(w_tid).w_tax;

    // select c_discount from customer c where c_w_id=w_id and c_d_id=d_id and c.c_id=c_id;
    size_t c_tid;
    if (!datastore_->Find<Datastore::customer_row>(Key<Integer, Integer, Integer>(w_id, d_id, c_id), c_tid)) {
        throw TransactionRollback("Customer not found");
    }
    auto c_discount = datastore_->Get<Datastore::customer_row>(c_tid).c_discount;

    // select d_next_o_id as o_id,d_tax from district d where d_w_id=w_id and d.d_id=d_id;
    size_t d_tid;
    if (!datastore_->Find<Datastore::district_row>(Key<Integer, Integer>(w_id, d_id), d_tid)) {
        throw TransactionRollback("District not found");
    }
    auto &d = datastore_->Get<Datastore::district_row>(d_tid);
    auto o_id = d.d_next_o_id;
    auto d_tax = d.d_tax;
    d.d_next_o_id = o_id + Integer(1);

    // var integer all_local = 1;
    // forsequence (index between 0 and items-1) {
    //   if (w_id<>supware[index])
    //     all_local=0;
    // }
    auto all_local = Integer(1);
    for (auto index = Integer(0); index < items; index += Integer(1)) {
        if (w_id != supware[index.value])
            all_local = Integer(0);
    }

    // insert into "order" values (o_id,d_id,w_id,c_id,datetime,0,items,all_local);
    Datastore::order_row order;
    order.o_id = o_id;
    order.o_d_id = d_id;
    order.o_w_id = w_id;
    order.o_c_id = c_id;
    order.o_entry_d = datetime;
    order.o_carrier_id = Integer(0);
    order.o_ol_cnt = Numeric<2, 0>(items);
    order.o_all_local = Numeric<1, 0>(all_local);
    datastore_->Insert<Datastore::order_row>(std::move(order));

    // insert into neworder values (o_id,d_id,w_id);
    Datastore::neworder_row neworder;
    neworder.no_o_id = o_id;
    neworder.no_d_id = d_id;
    neworder.no_w_id = w_id;
    datastore_->Insert<Datastore::neworder_row>(std::move(neworder));

    // forsequence (index between 0 and items-1) {
    for (auto index = Integer(0); index < items; index += Integer(1)) {
        // select i_price from item where i_id=itemid[index];
        size_t i_tid;
        if (!datastore_->Find<Datastore::item_row>(Key<Integer>(itemid[index.value]), i_tid)) {
            throw TransactionRollback("Item not found");
        }
        auto &item = datastore_->Get<Datastore::item_row>(i_tid);
        auto i_price = item.i_price;

        // select s_quantity,s_remote_cnt,s_order_cnt,case d_id when 1 then s_dist_01 when ...
        size_t s_tid;
        if (!datastore_->Find<Datastore::stock_row>(Key<Integer, Integer>(supware[index.value], itemid[index.value]), s_tid)) {
            throw TransactionRollback("Stock not found");
        }
        auto &stock = datastore_->Get<Datastore::stock_row>(s_tid);
        auto s_quantity = stock.s_quantity;
        auto s_remote_cnt = stock.s_remote_cnt;
        auto s_order_cnt = stock.s_order_cnt;
        Char<24> s_dist;
        switch (d_id.value) {
            case 1: s_dist = stock.s_dist_01; break;
            case 2: s_dist = stock.s_dist_02; break;
            case 3: s_dist = stock.s_dist_03; break;
            case 4: s_dist = stock.s_dist_04; break;
            case 5: s_dist = stock.s_dist_05; break;
            case 6: s_dist = stock.s_dist_06; break;
            case 7: s_dist = stock.s_dist_07; break;
        }

        // if (s_quantity>qty[index]) {
        //    update stock set s_quantity=s_quantity-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
        // } else {
        //    update stock set s_quantity=s_quantity+91-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
        // }
        if (s_quantity > Numeric<4, 0>(qty[index.value])) {
            stock.s_quantity = stock.s_quantity - Numeric<4, 0>(qty[index.value]);
        } else {
            stock.s_quantity = stock.s_quantity + Numeric<4, 0>(91) - Numeric<4, 0>(qty[index.value]);
        }

        // if (supware[index]<>w_id) {
        //    update stock set s_remote_cnt=s_remote_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
        // } else {
        //    update stock set s_order_cnt=s_order_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
        // }
        if (supware[index.value] != w_id) {
            stock.s_remote_cnt += Numeric<4, 0>(1);
        } else {
            stock.s_order_cnt += Numeric<4, 0>(1);
        }

        // var numeric(6,2) ol_amount=qty[index]*i_price*(1.0+w_tax+d_tax)*(1.0-c_discount);
        // insert into orderline values (o_id,d_id,w_id,index+1,itemid[index],supware[index],0,qty[index],ol_amount,s_dist);
        auto order_line_key = Key<Integer, Integer, Integer, Integer>(w_id, d_id, o_id, index + Integer(1));
        Numeric<6, 2> ol_amount = Numeric<6, 2>(qty[index.value]);
        ol_amount = (ol_amount * i_price.castS<6>()).castM2<6>();
        ol_amount = (ol_amount * (Numeric<6, 2>(1) + w_tax.castM2<6>() + d_tax.castM2<6>())).castM2<6>();
        ol_amount = (ol_amount * (Numeric<6, 2>(1) - c_discount.castM2<6>())).castM2<6>();
        Datastore::orderline_row ol;
        ol.ol_o_id = o_id;
        ol.ol_d_id = d_id;
        ol.ol_w_id = w_id;
        ol.ol_number = index + Integer(1);
        ol.ol_i_id = itemid[index.value];
        ol.ol_supply_w_id = supware[index.value];
        ol.ol_delivery_d = Timestamp(0);
        ol.ol_quantity = Numeric<2, 0>(qty[index.value]);
        ol.ol_amount = ol_amount;
        ol.ol_dist_info = s_dist;
        datastore_->Insert<Datastore::orderline_row>(ol);
    }
}

void Database::Delivery(
        Integer w_id,
        Integer o_carrier_id,
        Timestamp datetime) {
    for (auto d_id = Integer(0); d_id < Integer(10); d_id += Integer(1)) {
        // select min(no_o_id) as o_id from neworder where no_w_id=w_id and no_d_id=d_id order by no_o_id else { continue; }
        auto no_iter = datastore_->neworder_pk.lower_bound(Key<Integer, Integer, Integer>(w_id, d_id, Integer(0)));
        tid_t no_tid = 0;
        Integer o_id = Integer(0);
        bool found_no = false;

        // Found nothing?
        if (no_iter == datastore_->neworder_pk.end()) continue;

        // Our partial key does not exist?
        auto &no = datastore_->Get<Datastore::neworder_row>(no_iter->second);
        if (no.no_w_id != w_id || no.no_d_id != d_id) continue;

        no_tid = no_iter->second;
        o_id = no.no_o_id;

        // delete from neworder where no_w_id=w_id and no_d_id=d_id and no_o_id=o_id;
        datastore_->Delete<Datastore::neworder_row>(no_tid);

        // select o_ol_cnt,o_c_id from "order" o where o_w_id=w_id and o_d_id=d_id and o.o_id=o_id;
        tid_t o_tid;
        if (!datastore_->Find<Datastore::order_row>(Key<Integer, Integer, Integer>(w_id, d_id, o_id), o_tid)) {
            throw TransactionRollback("Order not found");
        }

        // update "order" set o_carrier_id=o_carrier_id where o_w_id=w_id and o_d_id=d_id and "order".o_id=o_id;
        auto &o = datastore_->Get<Datastore::order_row>(o_tid);
        auto o_ol_cnt = o.o_ol_cnt;
        auto o_c_id = o.o_c_id;
        o.o_carrier_id = o_carrier_id;
        o.o_w_id = w_id;
        o.o_d_id = d_id;
        o.o_id = o_id;

        // var numeric(6,2) ol_total=0;
        auto ol_total = Numeric<6, 2>(0);

        // forsequence (ol_number between 1 and o_ol_cnt) {
        for (auto ol_number = Integer(1); Numeric<2, 0>(ol_number) <= o_ol_cnt; ol_number += Integer(1)) {
            // select ol_amount from orderline where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
            tid_t ol_tid;
            if (!datastore_->Find<Datastore::orderline_row>(Key<Integer, Integer, Integer, Integer>(w_id, d_id, o_id, ol_number), ol_tid)) {
                throw TransactionRollback("Order not found");
            }

            // ol_total=ol_total+ol_amount;
            auto &ol = datastore_->Get<Datastore::orderline_row>(ol_tid);
            ol_total += ol.ol_amount;

            // update orderline set ol_delivery_d=datetime where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
            ol.ol_delivery_d = datetime;
        }

        // update customer set c_balance=c_balance+ol_total where c_w_id=w_id and c_d_id=d_id and c_id=o_c_id;
        tid_t c_tid;
        if (!datastore_->Find<Datastore::customer_row>(Key<Integer, Integer, Integer>(w_id, d_id, o_c_id), c_tid)) {
            throw TransactionRollback("Customer not found");
        }
        auto &c = datastore_->Get<Datastore::customer_row>(c_tid);
        c.c_balance = c.c_balance + ol_total.castS<12>();
    }
}

Numeric<12, 2> Database::AnalyticalQuery() {
    LazyMultiMap<Key<Integer, Integer, Integer>, Numeric<12, 2>> ht_c;
    LazyMultiMap<Key<Integer, Integer, Integer>, std::pair<Numeric<12, 2>, Numeric<2, 0>>> ht_c_o;
    Numeric<12, 2> sum;

    // Build ht_c
    for (auto &c: datastore_->customer_data) {
        if (c.c_last.length() == 0) continue;
        if (*c.c_last.begin() != 'B') continue;
        ht_c.insert({ Key<Integer, Integer, Integer>(c.c_w_id, c.c_d_id, c.c_id), c.c_balance });
    }
    ht_c.finalize();

    // Probe ht_c and build ht_c_o
    for (auto &o: datastore_->order_data) {
        auto range = ht_c.equal_range(Key<Integer, Integer, Integer>(o.o_w_id, o.o_d_id, o.o_c_id));
        for (; range.first != range.second; ++range.first) {
            ht_c_o.insert({
                Key<Integer, Integer, Integer>(o.o_w_id, o.o_d_id, o.o_id),
                std::make_pair(range.first->value, o.o_ol_cnt)
            });
        }
    }
    ht_c_o.finalize();

    // Scan orderline
    for (auto &ol: datastore_->orderline_data) {
        auto range = ht_c_o.equal_range(Key<Integer, Integer, Integer>(ol.ol_w_id, ol.ol_d_id, ol.ol_o_id));
        for (; range.first != range.second; ++range.first) {
            auto x = (ol.ol_quantity.castP2()).castS<12>() * ol.ol_amount.castS<12>();
            auto y = range.first->value.first * (range.first->value.second.castP2()).castS<12>();
            sum += x.castM2<12>() - y.castM2<12>();
        }
    }

    return sum;
}

}  // namespace imlab
