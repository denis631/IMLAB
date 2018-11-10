// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_INFRA_HASH_TABLE_H_
#define INCLUDE_IMLAB_INFRA_HASH_TABLE_H_
//---------------------------------------------------------------------------
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <limits>
#include "imlab/infra/hash.h"
#include "imlab/infra/bits.h"
// ---------------------------------------------------------------------------
namespace imlab {
//---------------------------------------------------------------------------
template<typename ... T> struct IsKey : std::false_type { };
template<typename ... T> struct IsKey<Key<T...>> : std::true_type { };
//---------------------------------------------------------------------------
template <typename KeyT, typename ValueT>
class LazyMultiMap {
    // Check key type
    static_assert(IsKey<KeyT>::value, "The key of LazyMultiMap must be a Key<T>");

 protected:
    // Entry in the hash table
    struct Entry {
        // Pointer to the next element in the collision list
        Entry *next;
        // Key of the hash table entry
        KeyT key;
        // Value of the hash table entry
        ValueT value;

        // Constructor
        Entry(KeyT key, ValueT value)
            : next(nullptr), key(key), value(value) {}
    };

    // EqualRangeIterator for the hash table
    class EqualRangeIterator: public std::iterator<std::forward_iterator_tag, Entry> {
     public:
        // Default constructor
        EqualRangeIterator(): ptr_(nullptr), key_() {}
        // Constructor
        explicit EqualRangeIterator(Entry *ptr, KeyT key): ptr_(ptr), key_(key) {}
        // Destructor
        ~EqualRangeIterator() = default;

        // Find the first entry
        static EqualRangeIterator Find(Entry *ptr, KeyT key) {
            while (!!ptr) {
                if (ptr->key == key) return EqualRangeIterator(ptr, key);
                ptr = ptr->next;
            }
            return EqualRangeIterator(ptr, key);
        }
        // Postfix increment
        EqualRangeIterator operator++(int) {
            auto ptr = ptr_;
            do { ptr = ptr->next; } while (!!ptr && ptr->key != key_);
            return EqualRangeIterator(ptr, key_);
        }
        // Prefix increment
        EqualRangeIterator &operator++() {
            do { ptr_ = ptr_->next; } while (!!ptr_ && ptr_->key != key_);
            return *this;
        }
        // Reference
        Entry &operator*() { return *ptr_; }
        // Pointer
        Entry *operator->() { return ptr_; }
        // Equality
        bool operator==(const EqualRangeIterator &other) const { return ptr_ == other.ptr_; }
        // Inequality
        bool operator!=(const EqualRangeIterator &other) const { return ptr_ != other.ptr_; }

     protected:
        // Entry pointer
        Entry *ptr_;
        // Key that is being searched for
        KeyT key_;
    };

 public:
    // End of the equal range
    EqualRangeIterator end() { return EqualRangeIterator(); }

    // Insert an element into the hash table
    //  * Gather all entries with insert and build the hash table with finalize.
    void insert(const std::pair<KeyT, ValueT> &val) {
        entries_.emplace_back(val.first, val.second);
    }

    // Finalize the hash table
    //  * Get the next power of two, which is larger than the number of entries.
    //  * Resize the hash table to that size.
    //  * For each entry in entries_, calculate the hash and prepend it to the collision list in the hash table.
    void finalize() {
        if (entries_.size() >= std::numeric_limits<uint32_t>::max()) {
            throw std::runtime_error("Too large");
        }

        // Build the hash table
        uint32_t ht_size = std::max(NextPow2_32(entries_.size()), 32u);
        hash_table_.resize(ht_size, nullptr);
        hash_table_mask_ = ht_size - 1;

        // Insert all elements into the hash table.
        for (auto &entry : entries_) {
            uint32_t hash = entry.key.Hash() & hash_table_mask_;
            entry.next = hash_table_[hash];
            hash_table_[hash] = &entry;
        }
    }

    // To find an element, calculate the hash (Key::Hash), and search this list until you reach a nullptr;
    std::pair<EqualRangeIterator, EqualRangeIterator> equal_range(KeyT key) {
        uint32_t hash = key.Hash() & hash_table_mask_;
        return std::make_pair(EqualRangeIterator::Find(hash_table_[hash], key), EqualRangeIterator());
    }

 protected:
    // Entries of the hash table.
    // If you are motivated, you can replace this vector with an own fixed-size memory allocator.
    std::vector<Entry> entries_;
    // The hash table.
    // Use the next_ pointers in the entries to store the collision list of the hash table.
    //
    //      hash_table_     entries_
    //      +---+           +---+
    //      | * | --------> | x | --+
    //      | 0 |           |   |   |
    //      | 0 |           |   |   |
    //      | 0 |           | z | <-+
    //      +---+           +---+
    //
    std::vector<Entry*> hash_table_;
    // The hash table mask.
    uint32_t hash_table_mask_;
};
//---------------------------------------------------------------------------
}  // namespace imlab
//---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_INFRA_HASH_TABLE_H_
//---------------------------------------------------------------------------
