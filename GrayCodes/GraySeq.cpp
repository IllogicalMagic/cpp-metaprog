#include <array>

#include "GrayShared.hpp"
#include "GrayDynamic.hpp"

#ifndef G_BITS
#define G_BITS 4
#endif

constexpr codesize_t bits = G_BITS;
constexpr GrayView view = DECIMAL;

// GrayCodes array
template<GrayView V, code_t N,code_t...S>
struct GrayCodes:GrayCodes<V,N-1,N-1,S...>{};

template <GrayView V, code_t...S>
struct GrayCodes<V,0,S...>
{
  static constexpr std::array<code_t,sizeof...(S)> 
  make_codes()
  { 
    return {GrayVisualize<GrayEncode<S>::value,V>::value...};
  }
};

int main()
{
  const codesize_t size = static_cast<codesize_t>(1)<<bits;
  auto gray_stat=GrayCodes<view,size>::make_codes();
  code_t gray_dyn[size];
  gray_dynamic(gray_dyn,bits,view);
  
  bool success=true;
  for (codesize_t i=0;i<size;++i) {
    success&=gray_check(gray_stat[i],gray_dyn[i],i);
  }

  if (success==true)
    print_success(__FILE__);
  return 0;
}
