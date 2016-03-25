#include <tuple>
#include <array>
#include <cstdio>

#include "utils.h"
#include "GrayDynamic.hpp"
#include "GrayShared.hpp"

// Size and visualization of Gray codes
constexpr unsigned bit=4;
constexpr GrayType view=GrayType::DECIMAL;

// Main struct
// gray bit  = (map ('0':) gray (bit-1)) 
//          ++ (map ('1':) (reverse (gray (bit-1))))
template<unsigned Bit,GrayType v>
struct Gray
{
  static constexpr std::array<code_t,(1<<Bit)> result =
    append(std::move(Gray<Bit-1,v>::result),
	   map(GrayView<Bit,v>(),
	       std::make_tuple(),
	       reverse(std::move(Gray<Bit-1,v>::result))));
};

template<GrayType v>
struct Gray<1,v>
{
  static constexpr std::array<code_t,2> result {0,1};
};

template<GrayType v>
struct Gray<0,v>
{
  static constexpr std::array<code_t,1> result {0};
};



int main()
{
  std::array<code_t,(1<<bit)> stat_gray = Gray<bit,view>::result;
  code_t dyn_gray[1<<bit];
  gray_dynamic(dyn_gray,bit,view);

  // Compare codes
  for (int i=0;i<(1<<bit);++i) {
    if (stat_gray[i]!=dyn_gray[i]) {
      printf("Err: stat_gray[%d]!=dyn_gray[%d] (%lu!=%lu)\n",
      	     i,i,stat_gray[i],dyn_gray[i]);
    }
  }
}

