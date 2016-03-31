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

bool check_value(DRatio::DRatio& stat, DRatio::DRatio& dyn, size_t i)
{
  if (stat==dyn)
    return true;
  std::cout << "Error: stat_bern[" 
	    << i 
	    << "]!=dyn_bern[" 
	    << i 
	    << "] ("
	    << stat
	    << "!="
	    << dyn 
	    << ")!\n";
  return false;
}

