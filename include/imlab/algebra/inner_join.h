// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
#define INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
// ---------------------------------------------------------------------------
#include <memory>
#include <utility>
#include <vector>
#include "imlab/algebra/iu.h"
#include "imlab/algebra/operator.h"
// ---------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------
class InnerJoin: public Operator {
#pragma mark - helper
    std::string hashTableName();
    std::string leftJoinOperandKeyGenericType();
    std::string keyFromPredicate(int predicateIndex);

 protected:
    // Left child operator
    std::unique_ptr<Operator> left_child_;
    // Right child operator
    std::unique_ptr<Operator> right_child_;
    // Hash preodicates
    std::vector<std::pair<const IU*, const IU*>> hash_predicates_;
    // Required ius
    std::vector<const IU*> left_child_required_ius, right_child_required_ius;
    std::vector<const IU*> required_ius_;
    // Consumer
    Operator *consumer_;
    // Out stream
    std::ostream *out_;

 public:
    // Constructor
    explicit InnerJoin(std::unique_ptr<Operator> left,
            std::unique_ptr<Operator> right,
            std::vector<std::pair<const IU*, const IU*>> predicates)
        : left_child_(std::move(left)), right_child_(std::move(right)), hash_predicates_(predicates) {}

    // Collect all IUs produced by the operator
    std::vector<const IU*> CollectIUs() override;

    // Prepare the operator
    void Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) override;
    // Produce all tuples
    void Produce() override;
    // Consume tuple
    void Consume(const Operator* child) override;
    };
// ---------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
// ---------------------------------------------------------------------------
