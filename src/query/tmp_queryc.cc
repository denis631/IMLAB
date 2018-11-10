#include <iostream>

#include "imlab/database.h"
#include "imlab/infra/hash_table.h"

using namespace imlab;

extern "C" void generated_query(imlab::Database &db) {

	for (const auto &row : db.datastore()->customer_data) {
		auto c_id = row.c_id;
		auto c_first = row.c_first;
		auto c_middle = row.c_middle;
		auto c_last = row.c_last;

		if (c_last == Varchar<16>::build("BARBARBAR")) {
			std::cout 
				<< c_id << " "
				<< c_first << " "
				<< c_middle << " "
				<< c_last << " "
				<< std::endl;
		}
	}

}
