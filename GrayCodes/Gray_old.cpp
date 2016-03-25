#include <cstdio>
#include "utils.h"
#include "GrayDynamic.hpp"
#include "GrayShared.hpp"

// Size and visualization of Gray codes
constexpr unsigned bit=5;
constexpr GrayType view=GrayType::DECIMAL;

enum class Order {NORMAL,REVERSED};

// List with Gray codes
template<unsigned Bit, code_t Val, Order Ord, GrayType T>
struct GrayList;

// Leaves
template<code_t Val, GrayType T>
struct GrayList<0,Val,Order::NORMAL,T>
{
  static code_t get(code_t n) {return Val;}
};

template<code_t Val, GrayType T>
struct GrayList<0,Val,Order::REVERSED,T>
{
  static code_t get(code_t n) {return Val;}
};
// Leaves end

// Normal ordered list
template<unsigned Bit, code_t Val, GrayType T>
struct GrayList<Bit,Val,Order::NORMAL,T>
{
  
  constexpr static code_t mid = static_cast<code_t>(1)<<(Bit-1);
  constexpr static code_t rval = GrayView<Bit,T>()(Val);
  
  typedef GrayList<Bit-1,Val,Order::NORMAL,T> First;
  typedef GrayList<Bit-1,rval,Order::REVERSED,T> Second;

  static code_t get(code_t n) 
  {
    return (n<mid)?First::get(n):Second::get(n-mid);
  }
};

// Reversed list
template<unsigned Bit,code_t Val, GrayType T>
struct GrayList<Bit,Val,Order::REVERSED,T>
{

  constexpr static code_t mid = static_cast<code_t>(1)<<(Bit-1);
  constexpr static code_t rval = GrayView<Bit,T>()(Val);

  typedef GrayList<Bit-1,rval,Order::NORMAL,T> First;
  typedef GrayList<Bit-1,Val,Order::REVERSED,T> Second;

  static code_t get(code_t n) 
  {
    return (n<mid)?First::get(n):Second::get(n-mid);
  }
  
};

// Main struct
template<unsigned Bit, GrayType T>
struct Gray
{
  typedef GrayList<Bit,0,Order::NORMAL,T> Codes;

  code_t operator[](code_t n) {return Codes::get(n);}
};

int main()
{
  Gray<bit,view> stat_gray;
  code_t dyn_gray[1<<bit];
  gray_dynamic(dyn_gray,bit,view);
  
  // Compare codes
  for (int i=0;i<(1<<bit);++i) {
    if (stat_gray[i]!=dyn_gray[i]) {
      printf("Err: stat_gray[%d]!=dyn_gray[%d] (%lu!=%lu)\n",
      	     i,i,stat_gray[i],dyn_gray[i]);
    }
  }

  return 0;
}
