// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#include <sstream>
#include "imlab/algebra/print.h"
#include "imlab/datastore.h"
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------
using Print = imlab::Print;
using IU = imlab::IU;
// ---------------------------------------------------------------------------
std::vector<const IU*> Print::CollectIUs() {
    return child_.get()->CollectIUs();
}
// ---------------------------------------------------------------------------
void Print::Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) {
    required_ius_ = required;
    consumer_ = consumer;
    out_ = &out;

    child_->Prepare(required, this, out);
}
// ---------------------------------------------------------------------------
void Print::Produce() {
    child_->Produce();
}
// ---------------------------------------------------------------------------
void Print::Consume(const Operator* child) {
    (*out_) << "\t\t\tstd::cout \n";
    for (int i = 0; i < required_ius_.size(); ++i) {
        (*out_) << "\t\t\t\t<< " << required_ius_[i]->column << " << \" \"\n";
    }
    (*out_) << "\t\t\t\t<< std::endl;\n";
}
// ---------------------------------------------------------------------------
