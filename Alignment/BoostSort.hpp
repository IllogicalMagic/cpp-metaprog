#ifndef SORT_WITH_BOOST_HPP_INCLUDED
#define SORT_WITH_BOOST_HPP_INCLUDED

#include <type_traits>
#include <utility>
#include <tuple>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>

// Pair (Elem,Index)
template<typename T, size_t I>
struct TupleElem
{
  using type = T;
  using index = boost::mpl::size_t<I>;
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

// Get element from new tuple with old index
template<typename SortImpl>
struct Decoder
{
  template<size_t Index>
  static constexpr auto recode()
  {
    using namespace boost;

    using index_map = 
      typename SortImpl::index_map;
    using old = mpl::size_t<Index>;
    using index = typename mpl::at<index_map,old>::type;

    return index::value;
  }

  template<size_t Index>
  static constexpr auto& get(typename SortImpl::type& t)
  {
    return std::get<recode<Index>()>(t);
  }
  
  template<size_t Index>
  static constexpr auto&& get(typename SortImpl::type&& t)
  {
    return get<Index>(t);
  }

  template<size_t Index>
  static constexpr auto& get(const typename SortImpl::type& t)
  {
    return std::get<recode<Index>()>(t);
  }

  template<size_t Index>
  static constexpr auto&& get(const typename SortImpl::type&& t)
  {
    return get<Index>(t);
  }

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
    decltype(tuple_to_vector(std::declval<Tpl>(),index_seq()));
  using sorted = 
    typename boost::mpl::sort<vec_types,IndexPred<_1,_2>>::type;

  template <typename Vec, size_t...S>
  static auto cont_to_tuple(Vec,std::index_sequence<S...>)
  // decltype(at_c<Vec,S>::type)==TupleElem
    -> std::tuple<typename boost::mpl::at_c<Vec,S>::type::type...>;

  using type = 
    decltype(cont_to_tuple(std::declval<sorted>(),index_seq()));

  // For make_sorted_tuple
  template<size_t I>
  struct OldIndex
  {
    static constexpr size_t value = 
      boost::mpl::at_c<sorted,I>::type::index::value;
  };

  template<typename Vec, size_t...S>
  static auto get_index_map(Vec,std::index_sequence<S...>)
    -> boost::mpl::map<boost::mpl::pair
    <typename boost::mpl::at_c<Vec,S>::type::index, 
    boost::mpl::size_t<S>>...>;

  using index_map = decltype(get_index_map(std::declval<sorted>(),
					   index_seq()));

  using decoder = Decoder<TupleSortImpl<Pred,Tpl>>;

  template<size_t...S,typename...Args>
  static constexpr auto 
  make_sorted_tuple_impl(std::index_sequence<S...>,
			 Args&&... args)
  {
    using tpl = decltype(std::make_tuple(args...));
    static_assert(std::is_same<tpl,Tpl>::value,
		  "Cannot construct tuple with wrong arguments");
    
    using impl = TupleSortImpl<Pred,tpl>;
    using sorted = typename impl::type;

    auto tmp = std::tie(args...);
    return 
      sorted(std::get<impl::template OldIndex<S>::value>(tmp)...);
  }
};

#endif
