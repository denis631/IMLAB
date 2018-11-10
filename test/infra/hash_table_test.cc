// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "imlab/infra/types.h"
#include "imlab/infra/hash.h"
#include "imlab/infra/hash_table.h"
#include "gtest/gtest.h"

using namespace imlab; // NOLINT

namespace {

TEST(LazyMultiMapTest, Empty) {
    LazyMultiMap<Key<Integer, Integer>, uint64_t> ht;
    ht.finalize();
    auto key = Key<Integer, Integer>(Integer(0), Integer(1));
    auto range = ht.equal_range(key);
    ASSERT_TRUE(range.first == range.second);
}

TEST(LazyMultiMapTest, SingleElement) {
    LazyMultiMap<Key<Integer, Integer>, uint64_t> ht;
    ht.insert({ Key<Integer, Integer>(Integer(0), Integer(1)), 42 });
    ht.finalize();
    auto key = Key<Integer, Integer>(Integer(0), Integer(1));
    auto range = ht.equal_range(key);
    ASSERT_TRUE(range.first != range.second);
    EXPECT_EQ(range.first->value, 42);
    EXPECT_TRUE(++range.first == range.second);
}

TEST(LazyMultiMapTest, SingleCollidingElement) {
    LazyMultiMap<Key<Integer, Integer>, uint64_t> ht;
    ht.insert({ Key<Integer, Integer>(Integer(0), Integer(1)), 42 });
    ht.insert({ Key<Integer, Integer>(Integer(0), Integer(1)), 43 });
    ht.finalize();
    auto key = Key<Integer, Integer>(Integer(0), Integer(1));
    auto range = ht.equal_range(key);
    ASSERT_TRUE(range.first != range.second);
    EXPECT_EQ(range.first->value, 43);
    ASSERT_TRUE(++range.first != range.second);
    EXPECT_EQ(range.first->value, 42);
    EXPECT_TRUE(++range.first == range.second);
}

TEST(LazyMultiMapTest, MultipleElements) {
    LazyMultiMap<Key<Integer, Integer>, uint64_t> ht;
    int counter = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            ht.insert({ Key<Integer, Integer>(Integer(i), Integer(j)), counter++ });
        }
    }
    ht.finalize();
    counter = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            auto range = ht.equal_range(Key<Integer, Integer>(Integer(i), Integer(j)));
            ASSERT_TRUE(range.first != range.second);
            ASSERT_EQ(range.first->value, counter++);
        }
    }
}

TEST(LazyMultiMapTest, MultipleCollidingElements) {
    LazyMultiMap<Key<Integer, Integer>, uint64_t> ht;
    unsigned counter = 0;
    for (unsigned i = 0; i < 100; ++i) {
        for (unsigned j = 0; j < 100; ++j) {
            ht.insert({ Key<Integer, Integer>(Integer(i), Integer(j)), counter++ });
            ht.insert({ Key<Integer, Integer>(Integer(i), Integer(j)), counter++ });
        }
    }
    ht.finalize();
    counter = 0;
    for (unsigned i = 0; i < 100; ++i) {
        for (unsigned j = 0; j < 100; ++j) {
            std::unordered_set<unsigned> matches;
            for (auto range = ht.equal_range(Key<Integer, Integer>(Integer(i), Integer(j)));
                    range.first != range.second;
                    ++range.first) {
                matches.insert(range.first->value);
            }
            ASSERT_EQ(matches.size(), 2);
            ASSERT_TRUE(matches.find(counter++) != matches.end());
            ASSERT_TRUE(matches.find(counter++) != matches.end());
        }
    }
}

}  // namespace
