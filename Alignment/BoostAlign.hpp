#ifndef ALIGN_WITH_BOOST_HPP_INCLUDED
#define ALIGN_WITH_BOOST_HPP_INCLUDED

#include <tuple>
#include <utility>
#include <type_traits>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/less.hpp>

#include "BoostSort.hpp"

template <typename T>
struct AlignTupleSort
{
  template<typename T1,typename T2>
  struct AlignLess
  {
    template<size_t N>
    using sz_t = boost::mpl::size_t<N>;
    
    using type = 
      boost::mpl::less< sz_t<alignof(T1)>, sz_t<alignof(T2)>>;
  };

  using impl = TupleSortImpl<AlignLess,T>;

  using type = typename impl::type;

  using decoder = typename impl::decoder;
};

template<size_t...S,typename...Args>
constexpr auto make_sorted_tuple_impl(std::index_sequence<S...>,
			    Args&&... args)
{
  using tpl = decltype(std::make_tuple(args...));
  using sorted = typename AlignTupleSort<tpl>::type;
  using impl = typename AlignTupleSort<tpl>::impl;
  auto tmp = std::tie(args...);

  return 
    sorted(std::get<impl::template OldIndex<S>::value>(tmp)...);
}

template<typename... Args>
constexpr auto make_sorted_tuple(Args&&... args)
{
  return make_sorted_tuple_impl
    (std::make_index_sequence<sizeof...(Args)>(),
     std::forward<Args>(args)...);
}

#endif
