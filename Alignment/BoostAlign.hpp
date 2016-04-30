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

  template<typename... Args>
  static constexpr auto make_sorted_tuple(Args&&... args)
  {
    return impl::make_sorted_tuple_impl
      (std::make_index_sequence<sizeof...(Args)>(),
       std::forward_as_tuple(args...));
  }
};

#endif
