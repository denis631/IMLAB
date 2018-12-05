// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <atomic>
#include <cstdint>
#include <chrono>  // NOLINT
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include "imlab/database.h"
#include "imlab/query/query_parse_context.h"
#include "imlab/infra/types.h"

namespace imlab {
class QueryREPL {
public:
    explicit QueryREPL(Database &db) : db(&db) {}

    void ExecuteCompiledQuery() {
        void *handle = dlopen(COMPILED_QUERY_LIB, RTLD_NOW);
        void (*queryFunction)(Database &) = nullptr;

        if (handle) {
            queryFunction = reinterpret_cast<void (*)(imlab::Database &)>(dlsym(handle, COMPILED_QUERY_FUNCTION_NAME));

            if (queryFunction) {
                queryFunction(*db);
            }
        }

        if (dlclose(handle)) {
            std::cerr << "error: " << dlerror() << std::endl;
            exit(EXIT_FAILURE);
        }

        // delete generated library
//        std::stringstream stream;
//        stream << "rm ../cmake-build-debug/" << COMPILED_QUERY_LIB;
//        std::system(stream.str().c_str());
    }

    void Start() {
        auto rawQueryString = readInput();
        QueryCompiler queryCompiler;

        std::string path = "../src/query/tmp_queryc.cc";

        do {
            queryCompiler.Compile(rawQueryString, path);
            ExecuteCompiledQuery();
            rawQueryString = readInput();
        } while(!rawQueryString.empty());
    }

private:

    std::string readInput() {
        std::cout << "----------------" << std::endl;
        std::cout << "Enter your query " << std::endl;
        std::string input;
        getline(std::cin, input);
        return input;
    }

    Database *db;
};
}

int main(int argc, char *argv[]) {
    imlab::Database db;

    // Create file streams
    std::ifstream tpcc_customer("../data/tpcc_5w/tpcc_customer.tbl");
    std::ifstream tpcc_item("../data/tpcc_5w/tpcc_item.tbl");
    std::ifstream tpcc_order("../data/tpcc_5w/tpcc_order.tbl");
    std::ifstream tpcc_stock("../data/tpcc_5w/tpcc_stock.tbl");
    std::ifstream tpcc_history("../data/tpcc_5w/tpcc_history.tbl");
    std::ifstream tpcc_district("../data/tpcc_5w/tpcc_district.tbl");
    std::ifstream tpcc_neworder("../data/tpcc_5w/tpcc_neworder.tbl");
    std::ifstream tpcc_orderline("../data/tpcc_5w/tpcc_orderline.tbl");
    std::ifstream tpcc_warehouse("../data/tpcc_5w/tpcc_warehouse.tbl");

    // Check if streams are open
    if (!tpcc_customer.is_open()) { std::cerr << "Failed to load customer" << std::endl; exit(-1); }
    if (!tpcc_item.is_open()) { std::cerr << "Failed to load item" << std::endl; exit(-1); }
    if (!tpcc_order.is_open()) { std::cerr << "Failed to load order" << std::endl; exit(-1); }
    if (!tpcc_stock.is_open()) { std::cerr << "Failed to load stock" << std::endl; exit(-1); }
    if (!tpcc_history.is_open()) { std::cerr << "Failed to load history" << std::endl; exit(-1); }
    if (!tpcc_district.is_open()) { std::cerr << "Failed to load district" << std::endl; exit(-1); }
    if (!tpcc_neworder.is_open()) { std::cerr << "Failed to load neworder" << std::endl; exit(-1); }
    if (!tpcc_orderline.is_open()) { std::cerr << "Failed to load orderline" << std::endl; exit(-1); }
    if (!tpcc_warehouse.is_open()) { std::cerr << "Failed to load warehouse" << std::endl; exit(-1); }

    // Load data
    db.LoadCustomer(tpcc_customer);
    db.LoadItem(tpcc_item);
    db.LoadOrder(tpcc_order);
    db.LoadStock(tpcc_stock);
    db.LoadHistory(tpcc_history);
    db.LoadDistrict(tpcc_district);
    db.LoadNewOrder(tpcc_neworder);
    db.LoadOrderLine(tpcc_orderline);
    db.LoadWarehouse(tpcc_warehouse);

    imlab::QueryREPL repl(db);
    repl.Start();

    return EXIT_SUCCESS;
}
