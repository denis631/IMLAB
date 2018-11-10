// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#include <sstream>
#include "imlab/algebra/inner_join.h"
#include "imlab/datastore.h"
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------
using InnerJoin = imlab::InnerJoin;
using IU = imlab::IU;
// ---------------------------------------------------------------------------
std::string InnerJoin::hashTableName() {
    auto firstTable = std::string(hash_predicates_[0].first->table);
    auto secondTable = std::string(hash_predicates_[0].second->table);
    return firstTable + "_" + secondTable + "_" + "join_table";
}

std::string InnerJoin::leftJoinOperandKeyGenericType() {
    std::ostringstream ostringstream;
    ostringstream << "Key<";

    // key type
    for (int i = 0; i < hash_predicates_.size(); ++i) {
        const auto &predicate = hash_predicates_[i];

        ostringstream << predicate.first->type.Name();

        if (i != hash_predicates_.size() - 1) {
            ostringstream << ",";
        }
    }

    ostringstream << ">";
    return ostringstream.str();
}

std::string InnerJoin::keyFromPredicate(int predicateIndex = 0) {
    std::ostringstream stream;

    stream << leftJoinOperandKeyGenericType() << "(";

    for (int i = 0; i < hash_predicates_.size(); ++i) {
        const auto &predicate = hash_predicates_[i];

        stream << (predicateIndex == 0 ? predicate.first : predicate.second)->column;

        if (i != hash_predicates_.size() - 1) stream << ",";
    }

    stream << ")";

    return stream.str();
}
// ---------------------------------------------------------------------------
std::vector<const IU*> InnerJoin::CollectIUs() {
    std::vector<const IU*> childrenIus = left_child_->CollectIUs(), rightIus = right_child_->CollectIUs();
    childrenIus.insert(childrenIus.end(), rightIus.begin(), rightIus.end());
    return childrenIus;
}
// ---------------------------------------------------------------------------
void InnerJoin::Prepare(const std::vector<const IU*> &required, Operator* consumer, std::ostream &out) {
    required_ius_ = required;
    consumer_ = consumer;
    out_ = &out;

    for (const auto &predicate : hash_predicates_) {
        if (std::find(required_ius_.begin(), required_ius_.end(), predicate.first) == required_ius_.end()) {
            required_ius_.push_back(predicate.first);
        }

        if (std::find(required_ius_.begin(), required_ius_.end(), predicate.second) == required_ius_.end()) {
            required_ius_.push_back(predicate.second);
        }
    }

    for (const auto &requiredIU : required_ius_) {
        bool insertedOnTheLeft = false;
        for (const auto &leftIU : left_child_->CollectIUs()) {
            if (leftIU == requiredIU) {
                left_child_required_ius.push_back(requiredIU);
                insertedOnTheLeft = true;
                break;
            }
        }

        if (!insertedOnTheLeft) right_child_required_ius.push_back(requiredIU);
    }

    left_child_->Prepare(left_child_required_ius, this, out);
    right_child_->Prepare(right_child_required_ius, this, out);
}
// ---------------------------------------------------------------------------
void InnerJoin::Produce() {
    std::ostringstream stream;

    stream << "std::tuple<";
    for (int i = 0; i < left_child_required_ius.size(); ++i) {
        const auto& requiredIU = left_child_required_ius[i];

        stream << requiredIU->type.Name();

        if (i != left_child_required_ius.size() - 1) stream << ",";
    }
    stream << ">";

    // declare map
    (*out_) << "\tLazyMultiMap<" << leftJoinOperandKeyGenericType() << ", " << stream.str() << "> " << hashTableName() << ";" << std::endl << std::endl;

    // produce left tuples
    left_child_->Produce();

    // finalize after we produced all tuples in the left table
    (*out_) << "\t" << hashTableName() << ".finalize();" << std::endl << std::endl;

    // produce right tuples
    right_child_->Produce();
}
// ---------------------------------------------------------------------------
void InnerJoin::Consume(const Operator* child) {
    if (child == left_child_.get()) {
        std::ostringstream stream;

        stream << "std::make_tuple(";
        for (int i = 0; i< left_child_required_ius.size(); ++i) {
            stream << left_child_required_ius[i]->column;
            if (i != left_child_required_ius.size() - 1) stream << ",";
        }
        stream << ")";

        (*out_) << "\t\t\t" << hashTableName() << ".insert({ " << keyFromPredicate(0) << ", " << stream.str() << " });" << std::endl; // put into table
    } else { // right child
        (*out_) << "\t\tauto searchKey = " << keyFromPredicate(1) << ";\n"
                << "\t\tauto matches = " << hashTableName() << ".equal_range(searchKey);" << std::endl << std::endl;

        // check for match with the left child
        (*out_) << "\t\tfor (auto match = matches.first; match != matches.second; ++match) {\n";

        // declare the vars from the match so that the parent can use them
        for (int i = 0; i < left_child_required_ius.size(); ++i) {
            const auto &leftRequiredIU = left_child_required_ius[i];
            (*out_) << "\t\t\tauto " << leftRequiredIU->column << " = " << "std::get<" << i << ">(match->value);\n";
        }
        (*out_) << "\n";

        // if there is a match call parent.consume
        consumer_->Consume(this);
        (*out_) << "\t\t}" << std::endl;
    }
}
// ---------------------------------------------------------------------------
