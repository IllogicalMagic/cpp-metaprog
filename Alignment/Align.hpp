#ifndef ALIGN_SORT_HPP_INCLUDED_
#define ALIGN_SORT_HPP_INCLUDED_

#include <utility>

#include "Sort.hpp"

// Generate powers of two
template<size_t N,size_t...S>
struct AlignList: AlignList<(N>>1),N,S...> {};

template<size_t...S>
struct AlignList<0,S...> 
{
  typedef std::integer_sequence<size_t,S...> seq;
};

// Elem2Val struct
template<typename T>
struct AlignOf
{
  static constexpr size_t value = alignof(T);
  using value_type = size_t;
};

// Main struct
template<typename T>
struct AlignTupleSort
{
  // alignof(struct) == max(alignof(struct_elem)...)
  static constexpr auto max_align = alignof(T);
  using type = 
    typename TupleSortImpl<T,AlignOf,
      typename AlignList<max_align>::seq>::type;
};

#endif

