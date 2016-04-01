#include <array>
#include <ratio>

#include "DynamicRatio.hpp"
#include "BernoulliShared.hpp"
#include "BernoulliDynamic.hpp"

constexpr bern size = B_SIZE;

template<size_t... S>
struct Seq {};

template<size_t Begin,size_t End, size_t... S>
struct Gen: Gen<Begin,End-1,End-1,S...> {};

template<size_t Begin,size_t... S>
struct Gen<Begin,Begin,S...>
{
  using seq = Seq<S...>;
};

template<typename R1,typename R2,typename...Rest>
struct SumFoldl
{ 
  using value = 
    typename SumFoldl<std::ratio_add<R1,R2>,Rest...>::value;
};

template<typename R1,typename R2>
struct SumFoldl<R1,R2>
{
  using value=std::ratio_add<R1,R2>;
};

template<size_t N>
struct BSum 
{
  // Is these more readable?
  template<size_t... S>
  static constexpr
  auto compute(Seq<S...>) ->
    typename SumFoldl<		// Sum 1..N
    std::ratio_multiply		// C(N+1,K+1)*B(N-K)
      <typename Binomial<N+1,S+1>::value,
      typename Bernoulli<N-S>::value> ...>::value;

  using value = decltype(compute(typename Gen<1,N+1>::seq()));
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
