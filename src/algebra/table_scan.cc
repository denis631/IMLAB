// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#include <iostream>
#include "imlab/algebra/table_scan.h"
#include "imlab/datastore.h"
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------
using TableScan = imlab::TableScan;
using IU = imlab::IU;
// ---------------------------------------------------------------------------
std::vector<const IU*> TableScan::CollectIUs() {
    std::vector<const IU*> tableIUs;
    auto match = imlab::Datastore::IUs.equal_range(table_);

    for (auto iter = match.first; iter != match.second; ++iter) {
        tableIUs.push_back(&iter->second);
    }

    return tableIUs;
}
// ---------------------------------------------------------------------------
void TableScan::Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) {
    required_ius_ = required;
    consumer_ = consumer;
    out_ = &out;
}
// ---------------------------------------------------------------------------
void TableScan::Produce() {
    // potentially can retrieve only needed columns, if for example column store is used
    (*out_) << "\tfor (const auto &row : db.datastore()->" << table_ << "_data) {" << std::endl;

    // create vars for the parent
    for (const auto &requiredIU : required_ius_) {
        (*out_) << "\t\tauto " << requiredIU->column << " = row." << requiredIU->column << ";\n";
    }
    (*out_) << "\n";

    consumer_->Consume(this);

    (*out_) << "\t}" << std::endl << std::endl;
}
// ---------------------------------------------------------------------------
