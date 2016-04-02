#include <iostream>
#include <cstring>
#include <vector>
#include <array>

#include "mTypeTraits.hpp"

template<typename In, typename Out>
void CopyFast(In* begin, In* end, Out* out)
{
  std::cout << "FastCopy!\n";
  std::memcpy(out,begin,(end-begin)*sizeof(decltype(*begin)));
}

template<typename In, typename Out>
void CopyNormal(In begin, In end, Out out)
{
  std::cout << "NormalCopy.\n";
  while (begin!=end)
    *out++=*begin++;
}

template<bool Type, typename In, typename Out>
struct CopySelect
{
  static void select(In begin, In end, Out out)
  {CopyNormal(begin,end,out);}
};

template<typename In, typename Out>
struct CopySelect<true,In,Out>
{
  static void select(In begin, In end, Out out)
  {CopyFast(begin,end,out);}
};

template<typename In, typename Out>
void Copy(In begin, In end, Out out)
{
  CopySelect<isPointer<In>::value && isPointer<Out>::value 
	     && isTriviallyCopyable<decltype(*begin)>::value 
	     && isTriviallyCopyable<decltype(*out)>::value 
	     && isEqualSizePtr<In,Out>::value,
	     In,Out>::select(begin,end,out);
}

void test_arr();
void test_arr_vec();
void test_nontrivcopy();

int main()
{
  test_arr();
  test_arr_vec();
  test_nontrivcopy();
  return 0;
}

// std::array is trivially copyable class
void test_arr()
{
  constexpr size_t intr = 5;
  constexpr size_t extr = 5;
  using val2 = unsigned;

  std::array<std::array
	     <std::array<unsigned char,sizeof(val2)>,intr>,extr> a;

  for (size_t i=0;i<extr;++i) {
    for (size_t j=0;j<intr;++j) {
      for (size_t k=0;k<sizeof(val2);++k)
	a[i][j][k]=1<<k;
    }
  }

  std::array<std::array<val2,intr>,extr> b;
  Copy(a.begin(),a.begin()+extr,b.begin());

  bool success=true;
  for (size_t i=0;i<extr;++i) {
    for (size_t j=0;j<intr;++j) {
      success&=!std::memcmp(a[i][j].begin(),&b[i][j],sizeof(val2));
    }
  }
  if (success)
    std::cout << "Test 1 passed!\n";
  else std::cout << "Test 1 failed!\n";
}

// std::vector is not trivially copyable
void test_arr_vec()
{
  constexpr size_t sz = 5;
  
  std::vector<double> a {1.0,1.2,3.7,1.9,0.0};
  std::array<double,sz> b;

  Copy(a.begin(),a.begin()+sz,b.begin());
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=a[i]==b[i];
  }
  if (success)
    std::cout << "Test 1 passed!\n";
  else std::cout << "Test 1 failed!\n";
}

struct CopyStruct
{
  int a,b;
  
  CopyStruct() = default;
  CopyStruct(const CopyStruct&) {}
};

void test_nontrivcopy()
{
  constexpr size_t sz = 3;
  
  CopyStruct a[sz];
  for (size_t i=0;i<sz;++i) {
    a[i].a=2*i;
    a[i].b=2*i+1;
  }
  CopyStruct b[sz];

  Copy(a,a+sz,b);
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=(a[i].a==b[i].a && a[i].b==b[i].b);
  }
  if (success)
    std::cout << "Test 1 passed!\n";
  else std::cout << "Test 1 failed!\n";
}
