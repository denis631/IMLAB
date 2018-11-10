// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#ifndef INCLUDE_IMLAB_DATABASE_H_
#define INCLUDE_IMLAB_DATABASE_H_

#include <istream>
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>
#include "imlab/infra/types.h"
#include "imlab/infra/hash.h"
#include "imlab/datastore.h"

namespace imlab {

class Database {
 public:
    // Load the TPCC data.
    // Call these methods with std::ifstreams to load your data.
    void LoadCustomer(std::istream &in);
    void LoadDistrict(std::istream &in);
    void LoadHistory(std::istream &in);
    void LoadItem(std::istream &in);
    void LoadNewOrder(std::istream &in);
    void LoadOrder(std::istream &in);
    void LoadOrderLine(std::istream &in);
    void LoadStock(std::istream &in);
    void LoadWarehouse(std::istream &in);

    // Create a new order
    void NewOrder(
        Integer w_id,
        Integer d_id,
        Integer c_id,
        Integer items,
        std::array<Integer, 15> &supware,
        std::array<Integer, 15> &itemid,
        std::array<Integer, 15> &qty,
        Timestamp datetime);

    // Create a delivery
    void Delivery(
        Integer w_id,
        Integer o_carrier_id,
        Timestamp datetime);

    // Run an analytical query
    Numeric<12, 2> AnalyticalQuery();

    // Constructor
    Database();
    // Destructor
    ~Database();

    // Return datastore
    Datastore *datastore() { return datastore_.get(); }

 protected:
    // The data store
    std::unique_ptr<Datastore> datastore_;
};

}  // namespace imlab

#endif  // INCLUDE_IMLAB_DATABASE_H_
