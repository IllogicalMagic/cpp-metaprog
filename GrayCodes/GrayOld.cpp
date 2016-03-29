#include <iostream>
#include "GrayDynamic.hpp"
#include "GrayShared.hpp"
#include "mStaticAssert.hpp"

// Size and visualization of Gray codes
const codesize_t bit=G_BITS;
const GrayView view=G_VIEW;

// List with Gray codes
template<GrayView T, code_t Val>
struct GrayList
{

  enum {value=GrayVisualize<GrayEncode<Val>::value,T>::value};

  typedef GrayList<T,Val-1> next;
  static code_t get(code_t n) 
  {
    return (n==Val) ? 
      (code_t)value 
      : (n>(Val>>1) ? 
      	 next::get(n) :
      	 GrayList<T,(Val>>1)>::get(n));
  }
};

// Last
template<GrayView T>
struct GrayList<T,0>
{
  enum {value=GrayVisualize<0,T>::value};

  static code_t get(code_t) 
  {
    return (code_t)value;
  }
};

// Main struct
template<unsigned Bit, GrayView T>
struct Gray
{
  typedef GrayList<T,((codesize_t)1<<Bit)-1> Codes;

  code_t operator[](code_t n) {return Codes::get(n);}
};

int main()
{
  mStaticAssert<!(view==BINARY && bit>=9)>("Binary bits should be < 9");
  Gray<bit,view> stat_gray;
  code_t dyn_gray[1<<bit];
  gray_dynamic(dyn_gray,bit,view);
  
  // Compare codes
  bool success=true;
  for (codesize_t i=0;i<(1<<bit);++i) {
    success&=gray_check(stat_gray[i],dyn_gray[i],i);
  }

  if (success==true)
    print_success(__FILE__);

  return 0;
}
