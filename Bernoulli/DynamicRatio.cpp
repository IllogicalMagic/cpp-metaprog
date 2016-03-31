#include <cstdint>
#include "DynamicRatio.hpp"

std::uint64_t DRatio::gcd(std::uint64_t a, std::uint64_t b)
{
  std::uint64_t t;
  if (a<b) {
    t=a;
    a=b;
    b=t;
  }
  while (b) {
    unsigned t=b;
    b=a%b;
    a=t;
  }
  return a;
}
