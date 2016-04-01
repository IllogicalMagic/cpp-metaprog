#include <iostream>
#include <ratio>
#include <cstdint>
#include <array>

#include "DynamicRatio.hpp"
#include "BernoulliDynamic.hpp"
#include "BernoulliShared.hpp"

constexpr bern size = B_SIZE;

// Recursive Bernoulli number computing
// B(N) = Sum ( C(N+1,K+1)*B(N-K))
template<bern N, bern K=N>
struct BSumOld
{
  using value=
    std::ratio_add
    <std::ratio_multiply
     <typename Binomial<N+1,K+1>::value,
      typename Bernoulli<N-K>::value>,
    typename BSumOld<N,K-1>::value>;
};

template<bern N>
struct BSumOld<N,1>
{
  using value=
    std::ratio_multiply
    <typename Binomial<N+1,2>::value,
     typename Bernoulli<N-1>::value>;
};

template<bern N>
struct BSum
{
  using value=typename BSumOld<N>::value;
};

int main()
{
  std::array<DRatio::DRatio,size+1> stat_bern;
  BernoulliList<size>::fill(stat_bern);
  std::array<DRatio::DRatio,size+1> dyn_bern;
  dyn_fill(dyn_bern);

  bool success=true;
  for (bern i=0;i<size+1;++i)
    success=check_value(stat_bern[i],dyn_bern[i],i);

  if (success)
    std::cout << __FILE__ << " succesfully passed tests!\n";
  return 0;
}
