#include <tuple>
#include <array>
#include <cstdio>

#include "utils.h"
#include "GrayDynamic.hpp"

// Size and visualization of Gray codes
constexpr unsigned bit=4;
constexpr GrayType view=GrayType::DECIMAL;

typedef long unsigned lu;

// Get right value for concatenation
template<lu Y,GrayType V>
struct GrayView;

// 0 1 3 2 etc.
template<lu Y>
struct GrayView<Y,GrayType::DECIMAL>
{
  constexpr auto
  operator()(const lu x){return (1<<(Y-1))+x;}
};

// 0 1 11 10 etc.
template<lu Y>
struct GrayView<Y,GrayType::BINARY>
{
  constexpr auto
  operator()(const lu x){return Pow<10,Y-1>::value+x;}
};

// Main struct
// gray bit  = (map ('0':) gray (bit-1)) 
//          ++ (map ('1':) (reverse (gray (bit-1))))
template<unsigned Bit,GrayType v>
struct Gray
{
  static constexpr std::array<lu,(1<<Bit)> result =
    append(std::move(Gray<Bit-1,v>::result),
	   map(GrayView<Bit,v>(),
	       std::make_tuple(),
	       reverse(std::move(Gray<Bit-1,v>::result))));
};

template<GrayType v>
struct Gray<1,v>
{
  static constexpr std::array<lu,2> result {0,1};
};

template<GrayType v>
struct Gray<0,v>
{
  static constexpr std::array<lu,1> result {0};
};



int main()
{
  std::array<lu,(1<<bit)> stat_gray = Gray<bit,view>::result;
  lu dyn_gray[1<<bit];
  gray_dynamic(dyn_gray,bit,view);

  // Compare codes
  for (int i=0;i<(1<<bit);++i) {
    if (stat_gray[i]!=dyn_gray[i]) {
      printf("Err: stat_gray[%d]!=dyn_gray[%d] (%lu!=%lu)\n",
      	     i,i,stat_gray[i],dyn_gray[i]);
    }
  }
}

