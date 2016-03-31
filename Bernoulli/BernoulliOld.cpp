#include <iostream>
#include <ratio>
#include <cstdint>
#include <array>

#include "DynamicRatio.hpp"
#include "BernoulliDynamic.hpp"

#ifndef B_SIZE
#define B_SIZE 3ul
#endif

using bern = std::uint64_t;

constexpr bern size = B_SIZE;

// Binomial quotient C(n,k)
template<bern N, bern K>
struct Binomial
{
  using value=
    std::ratio_add<typename Binomial<N-1,K-1>::value,
		   typename Binomial<N-1,K>::value>;
};

template<bern N>
struct Binomial<N,0>{using value=std::ratio<1>;};

template<bern N>
struct Binomial<N,N>{using value=std::ratio<1>;};

template<bern N>
struct Bernoulli;

// Recursive Bernoulli number computing
// B(N) = Sum ( C(N+1,K+1)*B(N-K))
template<bern N, bern K=N>
struct BSum
{
  using value=
    std::ratio_add
    <std::ratio_multiply
     <typename Binomial<N+1,K+1>::value,
      typename Bernoulli<N-K>::value>,
    typename BSum<N,K-1>::value>;
};

template<bern N>
struct BSum<N,1>
{
  using value=
    std::ratio_multiply
    <typename Binomial<N+1,2>::value,
     typename Bernoulli<N-1>::value>;
};

template<bern N,bool Opt>
struct BernFast;

template<bern N>
struct BernFast<N,true>
{
  using value=std::ratio<0>;
};

template<bern N>
struct BernFast<N,false>
{
  using value=
    std::ratio_multiply<std::ratio<-1,N+1>,typename BSum<N>::value>;
};

template<bern N>
struct Bernoulli
{
  using value=typename BernFast<N,N&1>::value;
};

template<>
struct Bernoulli<1>
{
  using value = std::ratio<-1,2>;
};

template<>
struct Bernoulli<0>
{
  using value = std::ratio<1>;
};

// Struct to dynamically fill std::array
template<bern N>
struct BernoulliList
{
  template<size_t Size>
  static void fill(std::array<DRatio::DRatio,Size>& a)
  {
    a[N].num=Bernoulli<N>::value::num;
    a[N].den=Bernoulli<N>::value::den;
    BernoulliList<N-1>::fill(a);
  }
};

template<>
struct BernoulliList<0>
{
  template<size_t Size>
  static void fill(std::array<DRatio::DRatio,Size>& a)
  {
    a[0].num=Bernoulli<0>::value::num;
    a[0].den=Bernoulli<0>::value::den;
  }
};

int main()
{
  std::array<DRatio::DRatio,size+1> stat_bern;
  BernoulliList<size>::fill(stat_bern);
  for (bern i=0;i<size+1;++i)
    std:: cout << stat_bern[i] << '\n';
  std::cout << "---\n";

  std::array<DRatio::DRatio,size+1> dyn_bern;
  dyn_fill(dyn_bern);
  for (bern i=0;i<size+1;++i)
    std::cout << dyn_bern[i] << '\n';
  return 0;
}
