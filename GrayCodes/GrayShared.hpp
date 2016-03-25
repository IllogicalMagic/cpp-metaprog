#ifndef GRAY_SHARED_H_DEFINED_
#define GRAY_SHARED_H_DEFINED_

#include "utils.h"

// Binary -   0  1 11 10
// Decimal -  0  1  3  2
enum class GrayType {BINARY,DECIMAL};

typedef long unsigned code_t;

// Get right value for concatenation
template<code_t Y,GrayType V>
struct GrayView;

// 0 1 3 2 etc.
template<code_t Y>
struct GrayView<Y,GrayType::DECIMAL>
{
  constexpr auto
  operator()(const code_t x){return (1<<(Y-1))+x;}
};

// 0 1 11 10 etc.
template<code_t Y>
struct GrayView<Y,GrayType::BINARY>
{
  constexpr auto
  operator()(const code_t x){return Pow<10,Y-1>::value+x;}
};

#endif
