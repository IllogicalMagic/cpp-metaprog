#include "GrayDynamic.hpp"
#include <cassert>
#include <cmath>

typedef long unsigned lu;
static void gray_fill(lu *,unsigned,unsigned,unsigned,GrayType);
static lu get_gray_add(GrayType,unsigned);

void gray_dynamic(lu* a, unsigned bits, GrayType view)
{
  if (bits==0)
    return;
  gray_fill(a,0,1<<bits,bits,view);
}

void gray_fill(lu* a, unsigned begin, unsigned end,
	      unsigned bits, GrayType view)
{
  if (bits==0) {
    a[begin]=0;
    return;
  }

  unsigned mid=begin+(end-begin)/2;
  gray_fill(a,begin,mid,bits-1,view);

  unsigned add=get_gray_add(view,bits);
  // Reverse right part and concat with 1
  for (unsigned i=0;i<mid;++i)
    a[end-i-1]=a[i]+add;
}

// Generate right value for concatenation
lu get_gray_add(GrayType view, unsigned bits)
{
  switch (view) {
  case GrayType::BINARY:
    return pow(10,bits-1);
  case GrayType::DECIMAL:
    return 1<<(bits-1);
  default:
    assert(false);
    return 0;
  }
}
