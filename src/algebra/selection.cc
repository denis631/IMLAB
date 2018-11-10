// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#include <sstream>
#include "imlab/algebra/selection.h"
#include "imlab/datastore.h"
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------
using Selection = imlab::Selection;
using IU = imlab::IU;
// ---------------------------------------------------------------------------
std::vector<const IU*> Selection::CollectIUs() {
    return child_->CollectIUs();
}
// ---------------------------------------------------------------------------
void Selection::Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) {
    required_ius_ = required;
    consumer_ = consumer;
    out_ = &out;

    std::vector<const IU*> childRequiredIUs = required;

    for (const auto &predicate : predicates_) {
        if (std::find(childRequiredIUs.begin(), childRequiredIUs.end(), predicate.first) == childRequiredIUs.end()) {
            childRequiredIUs.push_back(predicate.first);
        }
    }

    child_->Prepare(childRequiredIUs, this, out);
}
// ---------------------------------------------------------------------------
void Selection::Produce() {
    // let the child to produce the tuples
    child_->Produce();
}
// ---------------------------------------------------------------------------
void Selection::Consume(const Operator* child) {
    assert(predicates_.size() > 0);

    // check if predicate is satisfied
    (*out_) << "\t\tif (";

    for (int i = 0; i < predicates_.size(); ++i) {
        const auto &predicate = predicates_[i];

        auto iu = predicate.first;

        // if table name is set in the predicate
        if (i != 0) (*out_) << "\t\t\t";
        (*out_) << iu->column << " == "
                << predicate.first->type.Name() << "::build("
                << predicate.second
                << ")";

        if (i != predicates_.size() - 1) {
            (*out_) << " && \n";
        }
    }

    (*out_) << ") {" << std::endl;

    // let the parent node to consume, if the predicate is satisfied
    consumer_->Consume(this);

    (*out_) << "\t\t}" << std::endl;
}
// ---------------------------------------------------------------------------
