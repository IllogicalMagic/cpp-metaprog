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

template<template <typename T1, typename  T2> class Pred,
	 typename Tpl>
struct TupleSortImpl
{
  using _1 = boost::mpl::_1;
  using _2 = boost::mpl::_2;

  template<typename... Args>
  static auto tuple_to_vector(std::tuple<Args...>)
  -> boost::mpl::vector<Args...>;

  using vec_types = decltype(tuple_to_vector( std::declval<Tpl>() ));
  using sorted = typename boost::mpl::sort<vec_types,Pred<_1,_2>>::type;

  template <typename Vec, size_t...S>
  static auto cont_to_tuple(Vec,std::index_sequence<S...>) 
  -> std::tuple<typename boost::mpl::at_c<Vec,S>::type...>;

  using size = typename boost::mpl::size<vec_types>::type;

  using type = 
    decltype(cont_to_tuple(std::declval<sorted>(),
		       std::make_index_sequence<size::value>() ));
};

#endif
