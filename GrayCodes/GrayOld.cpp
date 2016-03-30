#include <iostream>
#include <array>
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

  // Uses fill_div to significantly decrease recursion depth
  template<codesize_t Size>
  static void fill(std::array<code_t,Size>& a)
  {
    a[Val]=value;
    GrayList<T,(Val>>1)>::template fill_div<Size,((Val+1)>>2)>(a);
  }

  template<codesize_t Size,codesize_t Len>
  static void fill_div(std::array<code_t,Size>& a)
  {
    mStaticAssert<(Val<Size)> ("Val >= Size");
    a[Val]=value;
    if (Len) {
      GrayList<T,Val+Len>::template fill_div<Size,(Len>>1)>(a);
      GrayList<T,Val-Len>::template fill_div<Size,(Len>>1)>(a);
    }
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

  template<codesize_t Size>
  static void fill(std::array<code_t,Size>& a)
  {
    a[0]=value;
  }

  template<codesize_t Size,codesize_t Len>
  static void fill_div(std::array<code_t,Size>& a)
  {
    a[0]=value;
  }
};

// Main struct
template<unsigned Bit, GrayView T>
struct Gray
{
  typedef GrayList<T,((codesize_t)1<<Bit)-1> Codes;

  code_t operator[](code_t n) {return Codes::get(n);}

  static void fill(std::array<code_t,(1<<Bit)>& a)
  {
    Codes::fill(a);
  }
};

int main()
{
  mStaticAssert<!(view==BINARY && bit>=9)>("Binary bits should be < 9");
  code_t dyn_gray[1<<bit];
  gray_dynamic(dyn_gray,bit,view);
  std::array<code_t,1<<bit> stat_gray;
  Gray<bit,view>::fill(stat_gray);
  // Compare codes
  bool success=true;
  for (codesize_t i=0;i<(1<<bit);++i) {
    success&=gray_check(stat_gray[i],dyn_gray[i],i);
  }

  if (success==true)
    print_success(__FILE__);

  return 0;
}
