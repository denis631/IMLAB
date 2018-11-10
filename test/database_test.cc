// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <sstream>
#include "imlab/test/data.h"
#include "imlab/database.h"
#include "imlab/datastore.h"
#include "gtest/gtest.h"

using namespace imlab; // NOLINT

namespace {

TEST(DatabaseTest, LoadWarehouse) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestWarehouse);
    db.LoadWarehouse(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::warehouse_row>()), 5);

    auto &w1 = db.datastore()->Get<imlab::Datastore::warehouse_row>(0);
    EXPECT_EQ(w1.w_id, Integer(4));
    EXPECT_EQ(w1.w_name, Varchar<10>::build("LPESIfo"));
    EXPECT_EQ(w1.w_street_1, Varchar<20>::build("aiAcXSImDqLf"));
    EXPECT_EQ(w1.w_street_2, Varchar<20>::build("wVqSpx1e3DNVdD3mo"));
    EXPECT_EQ(w1.w_city, Varchar<20>::build("2vIomPtgo1U3PJUgHYr"));
    EXPECT_EQ(w1.w_state, Char<2>::build("bw"));
    EXPECT_EQ(w1.w_zip, Char<9>::build("584811111"));
    EXPECT_EQ(w1.w_tax, (Numeric<4, 4>::castString(".1973", 5)));
    EXPECT_EQ(w1.w_ytd, (Numeric<12, 2>::castString("3000000.00", 10)));

    auto &w2 = db.datastore()->Get<imlab::Datastore::warehouse_row>(1);
    EXPECT_EQ(w2.w_id, Integer(1));
    EXPECT_EQ(w2.w_name, Varchar<10>::build("2Xtbfe"));
    EXPECT_EQ(w2.w_street_1, Varchar<20>::build("XlZDbdUdAn6B9wq5qmzV"));
    EXPECT_EQ(w2.w_street_2, Varchar<20>::build("8SGj3S1diu"));
    EXPECT_EQ(w2.w_city, Varchar<20>::build("qFlC5kZz3Rk"));
    EXPECT_EQ(w2.w_state, Char<2>::build("Nb"));
    EXPECT_EQ(w2.w_zip, Char<9>::build("657611111"));
    EXPECT_EQ(w2.w_tax, (Numeric<4, 4>::castString(".1923", 5)));
    EXPECT_EQ(w2.w_ytd, (Numeric<12, 2>::castString("3000000.00", 10)));
}

TEST(DatabaseTest, LoadDistrict) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestDistrict);
    db.LoadDistrict(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::district_row>()), 4);

    auto d1 = db.datastore()->Get<imlab::Datastore::district_row>(0);
    EXPECT_EQ(d1.d_id, Integer(1));
    EXPECT_EQ(d1.d_w_id, Integer(4));
    EXPECT_EQ(d1.d_name, Varchar<10>::build("5u3yvni"));
    EXPECT_EQ(d1.d_street_1, Varchar<20>::build("QregMnUUiBguHR7IvCQ"));
    EXPECT_EQ(d1.d_street_2, Varchar<20>::build("YGr4aw648K"));
    EXPECT_EQ(d1.d_city, Varchar<20>::build("s6Omh1ILJqaO6"));
    EXPECT_EQ(d1.d_state, Char<2>::build("ll"));
    EXPECT_EQ(d1.d_zip, Char<9>::build("517111111"));
    EXPECT_EQ(d1.d_tax, (Numeric<4, 4>::castString(".0168", 5)));
    EXPECT_EQ(d1.d_ytd, (Numeric<12, 2>::castString("3000000.00", 10)));
    EXPECT_EQ(d1.d_next_o_id, Integer(3001));

    auto d2 = db.datastore()->Get<imlab::Datastore::district_row>(1);
    EXPECT_EQ(d2.d_id, Integer(2));
    EXPECT_EQ(d2.d_w_id, Integer(4));
    EXPECT_EQ(d2.d_name, Varchar<10>::build("aoWdUqPR"));
    EXPECT_EQ(d2.d_street_1, Varchar<20>::build("rYJvhEktAJeOgY2jTS"));
    EXPECT_EQ(d2.d_street_2, Varchar<20>::build("H8vvscHXHp"));
    EXPECT_EQ(d2.d_city, Varchar<20>::build("zD5C8hhb5g1FHNfv8R"));
    EXPECT_EQ(d2.d_state, Char<2>::build("Kl"));
    EXPECT_EQ(d2.d_zip, Char<9>::build("989611111"));
    EXPECT_EQ(d2.d_tax, (Numeric<4, 4>::castString(".0291", 5)));
    EXPECT_EQ(d2.d_ytd, (Numeric<12, 2>::castString("3000000.00", 10)));
    EXPECT_EQ(d2.d_next_o_id, Integer(3001));
}

TEST(DatabaseTest, LoadHistory) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestHistory);
    db.LoadHistory(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::history_row>()), 4);

    auto h1 = db.datastore()->Get<imlab::Datastore::history_row>(0);
    EXPECT_EQ(h1.h_c_id, Integer(1));
    EXPECT_EQ(h1.h_c_d_id, Integer(1));
    EXPECT_EQ(h1.h_c_w_id, Integer(1));
    EXPECT_EQ(h1.h_d_id, Integer(4));
    EXPECT_EQ(h1.h_w_id, Integer(4));
    EXPECT_EQ(h1.h_date, Timestamp::castString("39", 2));
    EXPECT_EQ(h1.h_amount, (Numeric<6, 2>::castString("10.00", 5)));
    EXPECT_EQ(h1.h_data, (Varchar<24>::build("L1xLeaMBVGZwT50")));

    auto h2 = db.datastore()->Get<imlab::Datastore::history_row>(1);
    EXPECT_EQ(h2.h_c_id, Integer(2));
    EXPECT_EQ(h2.h_c_d_id, Integer(1));
    EXPECT_EQ(h2.h_c_w_id, Integer(1));
    EXPECT_EQ(h2.h_d_id, Integer(4));
    EXPECT_EQ(h2.h_w_id, Integer(4));
    EXPECT_EQ(h2.h_date, Timestamp::castString("39", 2));
    EXPECT_EQ(h2.h_amount, (Numeric<6, 2>::castString("10.00", 5)));
    EXPECT_EQ(h2.h_data, (Varchar<24>::build("KGOgpAuKu5qZnug")));
}

TEST(DatabaseTest, LoadItem) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestItem);
    db.LoadItem(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::item_row>()), 4);

    auto i1 = db.datastore()->Get<imlab::Datastore::item_row>(0);
    EXPECT_EQ(i1.i_id, Integer(1));
    EXPECT_EQ(i1.i_im_id, Integer(3164));
    EXPECT_EQ(i1.i_name, (Varchar<24>::build("hIHbFrcahBDz0ej7")));
    EXPECT_EQ(i1.i_price, (Numeric<5, 2>::castString("67.80", 5)));
    EXPECT_EQ(i1.i_data, (Varchar<50>::build("p6reTzhitjOHtkvrzBfPo7qX2Mh7WvrL0Rbp")));

    auto i2 = db.datastore()->Get<imlab::Datastore::item_row>(1);
    EXPECT_EQ(i2.i_id, Integer(2));
    EXPECT_EQ(i2.i_im_id, Integer(2426));
    EXPECT_EQ(i2.i_name, (Varchar<24>::build("Yz8my7wFQHwAKYCEk")));
    EXPECT_EQ(i2.i_price, (Numeric<5, 2>::castString("42.98", 5)));
    EXPECT_EQ(i2.i_data, (Varchar<50>::build("EIw2Ra3ZcgzkGjpS2X5SM6qEHoPvyfN6wWM4muaH6u")));
}

TEST(DatabaseTest, LoadNewOrder) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestNewOrder);
    db.LoadNewOrder(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::neworder_row>()), 4);

    auto no1 = db.datastore()->Get<imlab::Datastore::neworder_row>(0);
    EXPECT_EQ(no1.no_o_id, Integer(2101));
    EXPECT_EQ(no1.no_d_id, Integer(1));
    EXPECT_EQ(no1.no_w_id, Integer(4));

    auto no2 = db.datastore()->Get<imlab::Datastore::neworder_row>(1);
    EXPECT_EQ(no2.no_o_id, Integer(2102));
    EXPECT_EQ(no2.no_d_id, Integer(1));
    EXPECT_EQ(no2.no_w_id, Integer(4));
}

TEST(DatabaseTest, LoadOrder) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestOrder);
    db.LoadOrder(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::order_row>()), 4);

    auto o1 = db.datastore()->Get<imlab::Datastore::order_row>(0);
    EXPECT_EQ(o1.o_id, Integer(1));
    EXPECT_EQ(o1.o_d_id, Integer(1));
    EXPECT_EQ(o1.o_w_id, Integer(4));
    EXPECT_EQ(o1.o_c_id, Integer(2946));
    EXPECT_EQ(o1.o_entry_d, Timestamp::castString("39", 2));
    EXPECT_EQ(o1.o_carrier_id, Integer(9));
    EXPECT_EQ(o1.o_ol_cnt, (Numeric<2, 0>::castString("10", 2)));
    EXPECT_EQ(o1.o_all_local, (Numeric<1, 0>::castString("1", 1)));

    auto o2 = db.datastore()->Get<imlab::Datastore::order_row>(1);
    EXPECT_EQ(o2.o_id, Integer(2));
    EXPECT_EQ(o2.o_d_id, Integer(1));
    EXPECT_EQ(o2.o_w_id, Integer(4));
    EXPECT_EQ(o2.o_c_id, Integer(1404));
    EXPECT_EQ(o2.o_entry_d, Timestamp::castString("39", 2));
    EXPECT_EQ(o2.o_carrier_id, Integer(7));
    EXPECT_EQ(o2.o_ol_cnt, (Numeric<2, 0>::castString("13", 2)));
    EXPECT_EQ(o2.o_all_local, (Numeric<1, 0>::castString("1", 1)));
}

TEST(DatabaseTest, LoadOrderLine) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestOrderLine);
    db.LoadOrderLine(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::orderline_row>()), 4);

    auto ol1 = db.datastore()->Get<imlab::Datastore::orderline_row>(0);
    EXPECT_EQ(ol1.ol_o_id, Integer(1));
    EXPECT_EQ(ol1.ol_d_id, Integer(1));
    EXPECT_EQ(ol1.ol_w_id, Integer(4));
    EXPECT_EQ(ol1.ol_number, Integer(1));
    EXPECT_EQ(ol1.ol_i_id, Integer(36861));
    EXPECT_EQ(ol1.ol_supply_w_id, Integer(4));
    EXPECT_EQ(ol1.ol_delivery_d, Timestamp::castString("39", 2));
    EXPECT_EQ(ol1.ol_quantity, (Numeric<2, 0>::castString("5", 1)));
    EXPECT_EQ(ol1.ol_amount, (Numeric<6, 2>::castString("0.00", 1)));
    EXPECT_EQ(ol1.ol_dist_info, Char<24>::build("eZ4Gm8NmGHTbalXoY3bO2RLo"));

    auto ol2 = db.datastore()->Get<imlab::Datastore::orderline_row>(1);
    EXPECT_EQ(ol2.ol_o_id, Integer(1));
    EXPECT_EQ(ol2.ol_d_id, Integer(1));
    EXPECT_EQ(ol2.ol_w_id, Integer(4));
    EXPECT_EQ(ol2.ol_number, Integer(2));
    EXPECT_EQ(ol2.ol_i_id, Integer(36444));
    EXPECT_EQ(ol2.ol_supply_w_id, Integer(4));
    EXPECT_EQ(ol2.ol_delivery_d, Timestamp::castString("39", 2));
    EXPECT_EQ(ol2.ol_quantity, (Numeric<2, 0>::castString("5", 1)));
    EXPECT_EQ(ol2.ol_amount, (Numeric<6, 2>::castString("0.00", 1)));
    EXPECT_EQ(ol2.ol_dist_info, Char<24>::build("KjUPAh6wEvJr6M4ruFKjUWML"));
}

TEST(DatabaseTest, LoadStock) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestStock);
    db.LoadStock(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::stock_row>()), 4);

    auto s1 = db.datastore()->Get<imlab::Datastore::stock_row>(0);
    EXPECT_EQ(s1.s_i_id, Integer(1));
    EXPECT_EQ(s1.s_w_id, Integer(4));
    EXPECT_EQ(s1.s_quantity, (Numeric<4, 0>::castString("50", 2)));
    EXPECT_EQ(s1.s_dist_01, Char<24>::build("E2ziJ56SXnbFcrcnDi5FKqRv"));
    EXPECT_EQ(s1.s_dist_02, Char<24>::build("AwPAys0aNNHP4o9SlHpkJI2t"));
    EXPECT_EQ(s1.s_dist_03, Char<24>::build("FNVIJAjFFANrHERWNCjnhszI"));
    EXPECT_EQ(s1.s_dist_04, Char<24>::build("h7NrfFS9UufVWRtaUwEElAsA"));
    EXPECT_EQ(s1.s_dist_05, Char<24>::build("gMhJEauViF4FpJU4UcUpvnpj"));
    EXPECT_EQ(s1.s_dist_06, Char<24>::build("AICeLd3JVQ1buyyB4oWBlFB3"));
    EXPECT_EQ(s1.s_dist_07, Char<24>::build("5J7pCvPxMOCvd2a14rWQGNyZ"));
    EXPECT_EQ(s1.s_dist_08, Char<24>::build("kVaZZn0baRTfc9NyanHcX48f"));
    EXPECT_EQ(s1.s_dist_09, Char<24>::build("Of21nORYZTecK1KrPhYz3wEX"));
    EXPECT_EQ(s1.s_dist_10, Char<24>::build("3cG81VzizwSI04WrbYtbofns"));
    EXPECT_EQ(s1.s_ytd, (Numeric<8, 0>::castString("0", 1)));
    EXPECT_EQ(s1.s_order_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(s1.s_remote_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(s1.s_data, Varchar<50>::build("q81z6IbDzyHZDrc1LxG0ze0h9Vmk60EW9JR75lMr9cVj"));

    auto s2 = db.datastore()->Get<imlab::Datastore::stock_row>(1);
    EXPECT_EQ(s2.s_i_id, Integer(2));
    EXPECT_EQ(s2.s_w_id, Integer(4));
    EXPECT_EQ(s2.s_quantity, (Numeric<4, 0>::castString("57", 2)));
    EXPECT_EQ(s2.s_dist_01, Char<24>::build("mzpinD70eGOMDksyzExf5sdi"));
    EXPECT_EQ(s2.s_dist_02, Char<24>::build("dlgObIQycGqFBTVQLiDMwmYF"));
    EXPECT_EQ(s2.s_dist_03, Char<24>::build("nJU5H3nzknmrsL8BNuy2bhHY"));
    EXPECT_EQ(s2.s_dist_04, Char<24>::build("3OsXJwiDbbepHdU0NU8ZNWXq"));
    EXPECT_EQ(s2.s_dist_05, Char<24>::build("4fWq2moWkRc0ASjXVbQUeDAI"));
    EXPECT_EQ(s2.s_dist_06, Char<24>::build("2Zi2j3vLWaXjZ4LpZ0YrHh97"));
    EXPECT_EQ(s2.s_dist_07, Char<24>::build("MYMHmeUvP12B8LsCVmLbVthq"));
    EXPECT_EQ(s2.s_dist_08, Char<24>::build("QaK8mz69Dsrkxhq2hO2wKAs4"));
    EXPECT_EQ(s2.s_dist_09, Char<24>::build("ixBvJJoIiu0Wp9mcRN80ne3B"));
    EXPECT_EQ(s2.s_dist_10, Char<24>::build("HqztpECTLVlqCrkUEcUYNOG5"));
    EXPECT_EQ(s2.s_ytd, (Numeric<8, 0>::castString("0", 1)));
    EXPECT_EQ(s2.s_order_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(s2.s_remote_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(s2.s_data, Varchar<50>::build("Rlwl2jbTUXBtdU6NUjKOB41aHwbf8gL7qsFfzOL4X"));
}

TEST(DatabaseTest, LoadCustomer) {
    imlab::Database db;
    std::stringstream in(imlab_test::kTestCustomer);
    db.LoadCustomer(in);
    ASSERT_EQ((db.datastore()->Size<imlab::Datastore::customer_row>()), 2);

    auto c1 = db.datastore()->Get<imlab::Datastore::customer_row>(0);
    EXPECT_EQ(c1.c_id, Integer(1));
    EXPECT_EQ(c1.c_d_id, Integer(1));
    EXPECT_EQ(c1.c_w_id, Integer(4));
    EXPECT_EQ(c1.c_first, Varchar<16>::build("XvTC9cQ1BnpH3ue"));
    EXPECT_EQ(c1.c_middle, Char<2>::build("OE"));
    EXPECT_EQ(c1.c_last, Varchar<16>::build("BARBARBAR"));
    EXPECT_EQ(c1.c_street_1, Varchar<20>::build("ik1yiPkonwJ"));
    EXPECT_EQ(c1.c_street_2, Varchar<20>::build("pAxmX3VomS5QzAP1K"));
    EXPECT_EQ(c1.c_city, Varchar<20>::build("SPtt5EcqNaafy"));
    EXPECT_EQ(c1.c_state, Char<2>::build("hD"));
    EXPECT_EQ(c1.c_zip, Char<9>::build("525811111"));
    EXPECT_EQ(c1.c_phone, Char<16>::build("9613662508411977"));
    EXPECT_EQ(c1.c_since, Timestamp::castString("39", 2));
    EXPECT_EQ(c1.c_credit, Char<2>::build("GC"));
    EXPECT_EQ(c1.c_credit_lim, (Numeric<12, 2>::castString("50000.00", 8)));
    EXPECT_EQ(c1.c_discount, (Numeric<4, 4>::castString(".4211", 5)));
    EXPECT_EQ(c1.c_balance, (Numeric<12, 2>::castString("-10.00", 6)));
    EXPECT_EQ(c1.c_ytd_paymenr, (Numeric<12, 2>::castString("1.00", 4)));
    EXPECT_EQ(c1.c_payment_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(c1.c_delivery_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(c1.c_data, (Varchar<500>::build(imlab_test::kTestCustomer1Data)));

    auto c2 = db.datastore()->Get<imlab::Datastore::customer_row>(1);
    EXPECT_EQ(c2.c_id, Integer(2));
    EXPECT_EQ(c2.c_d_id, Integer(1));
    EXPECT_EQ(c2.c_w_id, Integer(4));
    EXPECT_EQ(c2.c_first, Varchar<16>::build("tZhugfr7h"));
    EXPECT_EQ(c2.c_middle, Char<2>::build("OE"));
    EXPECT_EQ(c2.c_last, Varchar<16>::build("BARBAROUGHT"));
    EXPECT_EQ(c2.c_street_1, Varchar<20>::build("TnMb0jwcz8rD"));
    EXPECT_EQ(c2.c_street_2, Varchar<20>::build("4zIePdXwuBxB2MTz1J"));
    EXPECT_EQ(c2.c_city, Varchar<20>::build("PBG2lSGTSRjeESt"));
    EXPECT_EQ(c2.c_state, Char<2>::build("YW"));
    EXPECT_EQ(c2.c_zip, Char<9>::build("853311111"));
    EXPECT_EQ(c2.c_phone, Char<16>::build("1380558293894392"));
    EXPECT_EQ(c2.c_since, Timestamp::castString("39", 2));
    EXPECT_EQ(c2.c_credit, Char<2>::build("GC"));
    EXPECT_EQ(c2.c_credit_lim, (Numeric<12, 2>::castString("50000.00", 8)));
    EXPECT_EQ(c2.c_discount, (Numeric<4, 4>::castString(".4309", 5)));
    EXPECT_EQ(c2.c_balance, (Numeric<12, 2>::castString("-10.00", 6)));
    EXPECT_EQ(c2.c_ytd_paymenr, (Numeric<12, 2>::castString("1.00", 4)));
    EXPECT_EQ(c2.c_payment_cnt, (Numeric<4, 0>::castString("0", 1)));
    EXPECT_EQ(c2.c_delivery_cnt, (Numeric<4, 0>::castString("0", 1)));
}

}  // namespace
