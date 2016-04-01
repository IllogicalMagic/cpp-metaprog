#ifndef BERNOULLI_SHARED_HPP_INCLUDED_
#define BERNOULLI_SHARED_HPP_INCLUDED_

#include <cstdint>
#include <ratio>
#include <array>

#include "DynamicRatio.hpp"

#ifndef B_SIZE
#define B_SIZE 3ul
#endif

using bern = std::uint64_t;

template<bern N, bern K>
struct Binomial;

// To lower number of generated classes
template<bern N, bern K>
using BinomCoeff=Binomial<N, (K < N-K) ? K : N-K>;

// Binomial quotient C(n,k)
template<bern N, bern K>
struct Binomial
{
  using value=
    std::ratio_add<typename BinomCoeff<N-1,K-1>::value,
		   typename BinomCoeff<N-1,K>::value>;
};

template<bern N>
struct Binomial<N,0>{using value=std::ratio<1>;};

// Struct for computing sum for Bernoulli number
// Should be implemented in modules
template<bern N>
struct BSum;

// Skip odd numbers
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

// Main struct for numbers
template<bern N>
struct Bernoulli
{
  using value=typename BernFast<N,N&1>::value;
};

// Predefined values for special numbers
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

#endif
