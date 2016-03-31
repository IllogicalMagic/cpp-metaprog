#include <array>
#include <cstdint>
#include <cassert>

#include "BernoulliDynamic.hpp"
#include "DynamicRatio.hpp"

// Specialized for small values
template<>
void dyn_fill<1>(std::array<DRatio::DRatio,1>& a)
{
  a[0]=1;
}

template<>
void dyn_fill<2>(std::array<DRatio::DRatio,2>& a)
{
  a[0]=1;
  a[1]=DRatio::DRatio(-1,2);
}

