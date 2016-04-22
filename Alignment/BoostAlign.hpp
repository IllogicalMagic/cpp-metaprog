#ifndef ALIGN_WITH_BOOST_HPP_INCLUDED
#define ALIGN_WITH_BOOST_HPP_INCLUDED

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
    
    using type = boost::mpl::less< sz_t<alignof(T1)>, sz_t<alignof(T2)>>;
  };

  using type = typename TupleSortImpl<AlignLess,T>::type;
};

#endif
