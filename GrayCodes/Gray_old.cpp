#include <iostream>
#include "GrayDynamic.hpp"
#include "GrayShared.hpp"

// Size and visualization of Gray codes
const codesize_t bit=4;
const GrayView view=BINARY;

// List with Gray codes
template<codesize_t Bit, GrayView T, code_t Val>
struct GrayList
{
  
  const static code_t mid = static_cast<code_t>(1)<<(Bit-1);
  
  typedef GrayList<Bit-1,T,Val> First;
  typedef GrayList<Bit-1,T,mid+Val> Second;

  static code_t get(code_t n) 
  {
    return (n<mid)?First::get(n):Second::get(n-mid);
  }
};

// Leaves
template<code_t Val, GrayView T>
struct GrayList<0,T,Val>
{
  static code_t get(code_t) 
  {
    return GrayVisualize<GrayEncode<Val>::value,T>::value;
  }
};
// Leaves end

// Main struct
template<unsigned Bit, GrayView T>
struct Gray
{
  typedef GrayList<Bit,T,0> Codes;

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

      std::cout << "Err: stat_gray[" 
		<< i
		<< "]!=dyn_gray[" 
		<< i
		<< "] ("
		<< stat_gray[i]
		<< "!="
		<< dyn_gray[i]
		<< " )\n";

    }
  }

  return 0;
}
