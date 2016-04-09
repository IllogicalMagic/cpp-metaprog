#ifndef ALIGN_SORT_HPP_INCLUDED_
#define ALIGN_SORT_HPP_INCLUDED_

#include <utility>
#include <tuple>

// Generate powers of two
template<int N,int...S>
struct AlignList: AlignList<(N>>1),N,S...> {};

template<int...S>
struct AlignList<0,S...> {typedef std::index_sequence<S...> seq;};

// Struct to filter tuple
template<typename T,int A,int N,size_t...S>
struct Filter: 
  std::conditional<
  alignof(typename std::tuple_element<N-1,T>::type)==A,
  Filter<T,A,N-1,N-1,S...>,Filter<T,A,N-1,S...>>::type {};

template<typename T,int A,size_t...S>
struct Filter<T,A,0,S...> {typedef std::index_sequence<S...> seq;};

// Implementation for all tuples
template<typename T,typename Aligns>
struct TupleSortImpl
{
  template<size_t...S>
  using Seq = std::index_sequence<S...>;

  // Concatenate two sequences of int
  template<size_t... S1,size_t... S2>
  static constexpr auto
  concat_seq(Seq<S1...>,Seq<S2...>)
    -> Seq<S1...,S2...>;

  // Concatenate any number of sequences
  template<typename S,typename...Rest>
  static constexpr auto
  concat_seq(S s,Rest... rest)
    -> decltype(concat_seq(s,concat_seq(rest...)));

  // Get indexes of elements in right position
  // For <int,char> will be <1,0>
  template<size_t...S>
  static constexpr auto
  indexes(Seq<S...>)
    -> decltype(concat_seq
		(typename Filter<T,S,std::tuple_size<T>::value>::seq()...));

  // Form reordered tuple from old tuple
  template<size_t...S>
  static constexpr auto
  get_tuple(Seq<S...>,T t)
    -> decltype(std::make_tuple(std::get<S>(t)...));

  using type = 
    decltype(get_tuple(indexes(Aligns()),T()));
};

// For tuples with alignof == 1
template<typename T>
struct TupleSortImpl<T,std::index_sequence<1>>
{
  using type = T;
};

// Main struct
template<typename T>
struct TupleSort
{
  // alignof(struct) == max(alignof(struct_elem)...)
  static constexpr auto max_align = alignof(T);
  using type = 
    typename TupleSortImpl<T,typename AlignList<max_align>::seq>::type;
};

// For empty tuples
template<>
struct TupleSort<std::tuple<>>
{
  using type = std::tuple<>;
};

#endif

