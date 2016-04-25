#ifndef SORT_WITH_BOOST_HPP_INCLUDED
#define SORT_WITH_BOOST_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>

#include <type_traits>
#include <utility>
#include <tuple>

// Pair (Elem,Index)
template<typename T, size_t I>
struct TupleElem
{
  using type = T;
  static constexpr size_t index = I;
};

// Form new predicate for TupleElem<T,I> from predicate for T
template<template<typename T1, typename T2> class Pred>
struct GetIndexPred
{
  template<typename T1, typename T2>
  struct IndexPred
  {
    using type = 
      typename Pred<typename T1::type,typename T2::type>::type;
  };

  template<typename T1,typename T2>
  using type = IndexPred<T1,T2>;
};

template<template <typename T1, typename  T2> class Pred,
	 typename Tpl>
struct TupleSortImpl
{
  using _1 = boost::mpl::_1;
  using _2 = boost::mpl::_2;

  // Get new Pred
  template<typename T1,typename T2>
  using IndexPred = 
    typename GetIndexPred<Pred>::template type<T1,T2>;

  static constexpr size_t size = std::tuple_size<Tpl>::value;
  using index_seq = std::make_index_sequence<size>;

  // Form TupleElem vector
  template<typename... Args,size_t...S>
  static auto tuple_to_vector
  (std::tuple<Args...>,std::index_sequence<S...>)
    -> boost::mpl::vector<TupleElem<Args,S>...>;

  using vec_types = 
    decltype(tuple_to_vector( std::declval<Tpl>(),
			      index_seq() ));
  using sorted = 
    typename boost::mpl::sort<vec_types,IndexPred<_1,_2>>::type;

  template <typename Vec, size_t...S>
  static auto cont_to_tuple(Vec,std::index_sequence<S...>)
  // decltype(at_c<Vec,S>::type)==TupleElem
    -> std::tuple<typename boost::mpl::at_c<Vec,S>::type::type...>;

  using type = 
    decltype(cont_to_tuple(std::declval<sorted>(),
			   index_seq() ));
};

#endif
