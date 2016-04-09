#ifndef ALIGN_SORT_HPP_INCLUDED_
#define ALIGN_SORT_HPP_INCLUDED_

#include <utility>
#include <tuple>

// Struct to filter tuple
template<typename T,template <typename E> class Elem2Val,
	 int A,int N,size_t...S>
struct Filter: 
  std::conditional<
  Elem2Val<typename std::tuple_element<N-1,T>::type>::value==A,
  Filter<T,Elem2Val,A,N-1,N-1,S...>,
  Filter<T,Elem2Val,A,N-1,S...>>::type {};

template<typename T,template <typename E> class Elem2Val,
	 int A,size_t...S>
struct Filter<T,Elem2Val,A,0,S...> {using seq = std::index_sequence<S...>;};

// Implementation for all tuples
template<typename T,template<typename E> class Elem2Val,typename Values>
struct TupleSortImpl
{
  template<size_t...S>
  using Seq = std::index_sequence<S...>;

  static constexpr auto
  concat_seq()
    -> Seq<>;

  // Concatenate two sequences of int
  template<size_t... S1,size_t... S2>
  static constexpr auto
  concat_seq2(Seq<S1...>,Seq<S2...>)
    -> Seq<S1...,S2...>;

  // Concatenate any number of sequences
  template<typename S1,typename...Rest>
  static constexpr auto
  concat_seq(S1 s1, Rest... rest)
    -> decltype(concat_seq2(s1,concat_seq(rest...)));

  // Get indexes of elements in right position
  template<size_t...S>
  static constexpr auto
  indexes(Seq<S...>)
    -> decltype(concat_seq
		(typename Filter<T,Elem2Val,S,
		 std::tuple_size<T>::value>::seq()...));

  // Form reordered tuple from old tuple
  template<size_t...S>
  static constexpr auto
  get_tuple(Seq<S...>,T t)
    -> decltype(std::make_tuple(std::get<S>(t)...));

  using type = 
    decltype(get_tuple(indexes(Values()),T()));
};

// For empty tuples
template<template<typename E> class Elem2Val,typename S>
struct TupleSortImpl<std::tuple<>,Elem2Val,S>
{
  using type = std::tuple<>;
};

// Generate powers of two
template<int N,int...S>
struct AlignList: AlignList<(N>>1),N,S...> {};

template<int...S>
struct AlignList<0,S...> {typedef std::index_sequence<S...> seq;};

// Elem2Val struct
template<typename T>
struct AlignOf
{
  static constexpr size_t value = alignof(T);
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

