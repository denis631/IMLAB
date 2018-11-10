// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_ALGEBRA_TABLE_SCAN_H_
#define INCLUDE_IMLAB_ALGEBRA_TABLE_SCAN_H_
// ---------------------------------------------------------------------------
#include <memory>
#include <utility>
#include <vector>
#include "imlab/algebra/operator.h"
// ---------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------
class TableScan: public Operator {
 protected:
    // Child operator
    std::unique_ptr<Operator> child_;
    // Table
    const char *table_;

    // Required ius
    std::vector<const IU*> required_ius_;
    // Consumer
    Operator *consumer_;
    // Out stream
    std::ostream *out_;

 public:
    // Constructor
    TableScan(const char *table)
        : table_(table) {}

    // Collect all IUs produced by the operator
    std::vector<const IU*> CollectIUs() override;

    // Prepare the operator
    void Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) override;
    // Produce all tuples
    void Produce() override;
    // Consume tuple
    void Consume(const Operator* child) override {}

    const char *TableName() const { return table_; }
};
// ---------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_ALGEBRA_TABLE_SCAN_H_
// ---------------------------------------------------------------------------
