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
     <typename BinomCoeff<N+1,K+1>::value,
      typename Bernoulli<N-K>::value>,
    typename BSumOld<N,K-1>::value>;
};

template<bern N>
struct BSumOld<N,1>
{
  using value=
    std::ratio_multiply
    <typename BinomCoeff<N+1,2>::value,
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
  bern_test(stat_bern);
  return 0;
}
