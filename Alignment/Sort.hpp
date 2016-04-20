#ifndef SORT_HPP_INCLUDED_
#define SORT_HPP_INCLUDED_

#include <utility>
#include <tuple>

// Struct to filter tuple
template<typename T,template <typename E> class Elem2Val,
	 typename Elem2Val<char>::value_type A,size_t N,size_t...S>
struct Filter: 
  std::conditional<
  Elem2Val<typename std::tuple_element<N-1,T>::type>::value==A,
  Filter<T,Elem2Val,A,N-1,N-1,S...>,
  Filter<T,Elem2Val,A,N-1,S...>>::type {};

template<typename T,template <typename E> class Elem2Val,
	 typename Elem2Val<char>::value_type A,size_t...S>
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

  // Concatenate two index sequences
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
  template<typename Val, Val...S>
  static constexpr auto
  indexes(std::integer_sequence<Val,S...>)
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

#endif
