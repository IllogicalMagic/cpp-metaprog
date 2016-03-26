#include "GrayDynamic.hpp"
#include "GrayShared.hpp"
#include <cassert>
#include <cmath>

static void 
gray_fill(code_t *,codesize_t,codesize_t,codesize_t,GrayView);

static code_t get_gray_add(GrayView,code_t);

void gray_dynamic(code_t* a, codesize_t bits, GrayView view)
{
  if (bits==0)
    return;
  gray_fill(a,0,1<<bits,bits,view);
}

static void 
gray_fill(code_t * a,codesize_t begin,
	  codesize_t end,codesize_t bits,GrayView view)
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
code_t get_gray_add(GrayView view, codesize_t bits)
{
  switch (view) {
  case BINARY:
    return pow(10,bits-1);
  case DECIMAL:
    return 1<<(bits-1);
  default:
    assert(false);
    return 0;
  }
}
