// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_ALGEBRA_OPERATOR_H_
#define INCLUDE_IMLAB_ALGEBRA_OPERATOR_H_
// ---------------------------------------------------------------------------
#include <vector>
#include "imlab/algebra/iu.h"
// ---------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------
class Operator {
 public:
    // Destructor
    virtual ~Operator() {};

    // Collect all IUs produced by the operator

    // Gather all IUs that can be produced.
    // Allow joins to track which IUS build the key of the hash table
    virtual std::vector<const IU*> CollectIUs() = 0;

    // Prepare the operator

    // Propagate required IUs through the tree.
    // Joins add their predicate IUs to the required IUs as they need to be "produced" by the TableScan
    virtual void Prepare(const std::vector<const IU*> &required, Operator* parent, std::ostream &out) = 0;

    // Produce all tuples
    virtual void Produce() = 0;

    // Consume tuple
    virtual void Consume(const Operator* child) = 0;
};
// ---------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_ALGEBRA_OPERATOR_H_
// ---------------------------------------------------------------------------
