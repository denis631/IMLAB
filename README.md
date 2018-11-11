# IMLAB Project

This is in-memory database project developed as a part from the in-memory database implementation lab at TU Munich.

Both SQL schema and simple select statements parsers are generated via BISON/FLEX.

The query compilation model is data-centric, as described in [Efficiently Compiling Efficient Query Plans for Modern Hardware](http://www.vldb.org/pvldb/vol4/p539-neumann.pdf)

## How to start

run `download_files.sh` script in order to download the tpcc_5w data

`imlabdb` is the target of the SQL query REPL.

Any queries consisting of selections with constants and hash-join must be evaluated correctly.

Caution: no query optimizer is written therefore query is compiled and executed exactly how it is defined. Provide right execution order for successful evaluation.

Sample queries:
`select c_id, c_first, c_middle, c_last from customer where c_last = 'BARBARBAR';`

`select d_name from district, order where d_w_id = o_w_id and  d_id = o_d_id and o_id = 7;`

`select o_id, ol_dist_info from order, orderline where o_id = ol_o_id and ol_d_id = o_d_id and o_w_id = ol_w_id and ol_number = 1 and ol_o_id = 100;`

`select c_last, o_id, i_id, ol_dist_info from customer, order, orderline, item where c_id = o_c_id and c_d_id = o_d_id and c_w_id = o_w_id and o_id = ol_o_id and ol_d_id = o_d_id and o_w_id = ol_w_id and ol_number = 1 and ol_o_id = 100 and ol_i_id = i_id;`

`select c_last, o_id, ol_dist_info from customer, order, orderline where c_id = o_c_id and o_id = ol_o_id and ol_d_id = o_d_id and o_w_id = ol_w_id and ol_number = 1 and ol_o_id = 100;`
