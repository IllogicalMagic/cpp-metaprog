#ifndef BERNOULLI_DYNAMIC_HPP_INCLUDED_
#define BERNOULLI_DYNAMIC_HPP_INCLUDED_

#include <array>
#include <cstdint>
#include <cassert>

#include "DynamicRatio.hpp"

template<size_t N>
class DynBinomial
{
  std::array<std::uint64_t,((N+2)*(N+1))/2> m_quot;
  
  void set(size_t n,size_t k,std::uint64_t val)
  {
    assert(k<=n);
    m_quot[(n+1)*n/2+k]=val;
  }

public:
  DynBinomial()
  {
    // set 1 to the head of triangle
    set(0,0,1);
    for (size_t i=1;i<N+1;++i) {
      // 1 ..... 1
      set(i,0,1);
      set(i,i,1);
      for (size_t j=1;j<i;++j) {
	set(i,j,get(i-1,j)+get(i-1,j-1));
      }
    }
  }

  std::uint64_t get(size_t n,size_t k)
  {
    assert(k<=n);
    return m_quot[((n+1)*n)/2+k];
  }
}; // DynBinomial

template<size_t N>
void dyn_fill(std::array<DRatio::DRatio,N>& a)
{
  a[0]=1;
  a[1]=DRatio::DRatio(-1,2);

  DynBinomial<N> bin;
  for (size_t i=2;i<N;i+=2) {
    for (size_t j=1;j<=i;++j) {
      a[i]+=std::move(a[i-j])*bin.get(i+1,j+1);
    }
    a[i]*=DRatio::DRatio(-1,i+1);
  }
}

#endif
