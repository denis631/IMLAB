// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_INFRA_TEMPLATE_H_
#define INCLUDE_IMLAB_INFRA_TEMPLATE_H_
//---------------------------------------------------------------------------
#include <array>
#include <tuple>
#include <numeric>
// ---------------------------------------------------------------------------
namespace imlab {
//---------------------------------------------------------------------------
// Apply function f on the tuple elements with an index sequence
template<typename F, typename... Types, std::size_t... Indexes>
void ForEachInTuple(const std::tuple<Types ...>& tuple, F func, std::index_sequence<Indexes... >) {
    using expander = int[];
    (void)expander { 0, ((void)func(std::get<Indexes>(tuple)), 0)... };
}
//---------------------------------------------------------------------------
// Apply function f on the tuple elements
template<typename F, typename... Types>
void ForEachInTuple(const std::tuple<Types...>& tuple, F func) {
    ForEachInTuple(tuple, func, std::make_index_sequence<sizeof... (Types)>());
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples with an index sequence
template<typename... Types, std::size_t... Indexes>
bool PairwiseEQ(const std::tuple<Types ...>& left, const std::tuple<Types...>& right,
        std::index_sequence<Indexes... >) {
    std::array<bool, std::index_sequence<Indexes... >::size()> results {
        (std::get<Indexes>(left) == std::get<Indexes>(right))...
    };
    auto conjunction = [](bool l, bool r) { return l & r; };
    return std::accumulate(results.begin(), results.end(), true, conjunction);
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples
template<typename... Types>
bool PairwiseEQ(const std::tuple<Types ...>& left, const std::tuple<Types...>& right) {
    return PairwiseEQ(left, right, std::make_index_sequence<sizeof... (Types)>());
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples with an index sequence
template<typename... Types, std::size_t... Indexes>
bool PairwiseLEQ(const std::tuple<Types ...>& left, const std::tuple<Types...>& right,
        std::index_sequence<Indexes... >) {
    std::array<bool, std::index_sequence<Indexes... >::size()> results {
        (std::get<Indexes>(left) <= std::get<Indexes>(right))...
    };
    auto conjunction = [](bool l, bool r) { return l & r; };
    return std::accumulate(results.begin(), results.end(), true, conjunction);
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples
template<typename... Types>
bool PairwiseLEQ(const std::tuple<Types ...>& left, const std::tuple<Types...>& right) {
    return PairwiseLEQ(left, right, std::make_index_sequence<sizeof... (Types)>());
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples with an index sequence
template<typename... Types, std::size_t... Indexes>
bool PairwiseLT(const std::tuple<Types ...>& left, const std::tuple<Types...>& right,
        std::index_sequence<Indexes... >) {
    std::array<bool, std::index_sequence<Indexes... >::size()> lt {
        (std::get<Indexes>(left) < std::get<Indexes>(right))...
    };
    std::array<bool, std::index_sequence<Indexes... >::size()> eq {
        (std::get<Indexes>(left) == std::get<Indexes>(right))...
    };
    for (size_t i = 0; i < std::index_sequence<Indexes... >::size(); ++i) {
        if (lt[i]) return true;
        if (!eq[i]) return false;
    }
    return false;
}
//---------------------------------------------------------------------------
// Pairwise compare two tuples
template<typename... Types>
bool PairwiseLT(const std::tuple<Types ...>& left, const std::tuple<Types...>& right) {
    auto result = PairwiseLT(left, right, std::make_index_sequence<sizeof... (Types)>());
    return result;
}
//---------------------------------------------------------------------------
}  // namespace imlab
//---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_INFRA_TEMPLATE_H_
//---------------------------------------------------------------------------
