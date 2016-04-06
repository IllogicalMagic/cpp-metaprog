#include <iostream>
#include <array>
#include <vector>
#include <iterator>

#include "Copy.hpp"

void print_result(bool);

void test_arr();
void test_arr_vec();
void test_nontrivcopy();
void test_const_source();
void test_bitwise_support();
void test_move();
void test_copy();

int main()
{
  test_arr();
  test_arr_vec();
  test_nontrivcopy();
  test_const_source();
  test_bitwise_support();
  test_move();
  test_copy();
  return 0;
}

void print_result(bool cond, int num)
{
  if (cond)
    std::cout << "Test " << num << " passed!\n";
  else std::cout << "Test " << num << " failed!\n";
}

// Test 1
// std::array is trivially copyable class
void test_arr()
{
  constexpr size_t intr = 5;
  constexpr size_t extr = 5;
  using val = unsigned;
  using val2 = val;

  std::array<std::array
	     <val,intr>,extr> a;

  for (size_t i=0;i<extr;++i) {
    for (size_t j=0;j<intr;++j) {
	a[i][j]=1<<j;
    }
  }

  std::array<std::array<val2,intr>,extr> b;
  Copy(a.begin(),a.begin()+extr,b.begin());

  bool success=true;
  for (size_t i=0;i<extr;++i) {
    for (size_t j=0;j<intr;++j) {
      success&= (a[i][j]==b[i][j]);
    }
  }
  print_result(success,1);
}

// Test 2
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
  print_result(success,2);
}

// Test 3
// Has user-defined copy ctor
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
  print_result(success,3);
}

// Test 4
// Source is constant but it is trivially copyable
void test_const_source()
{
  constexpr size_t sz = 3;
  
  const int a[sz] = {1,6,2};

  int b[sz];
  Copy(a,a+sz,b);
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=(a[i]==b[i]);
  }
  print_result(success,4);
}

// Test 5
struct NonTrivialCopy
{
  int x;
  NonTrivialCopy() {x=7;}
  NonTrivialCopy(int i):x(i) {}
  NonTrivialCopy(const NonTrivialCopy& rhs):
    x(rhs.x) {}

  NonTrivialCopy& operator=(const NonTrivialCopy&) = default;
};

// Add to list of copied types
template<>
struct hasBitwiseCopy<NonTrivialCopy>
{
  static constexpr bool value = true;
};

void test_bitwise_support()
{
  constexpr size_t sz = 3;
  using test_type = NonTrivialCopy;
  
  volatile const test_type a[sz] {8,1,2};

  volatile test_type b[sz*2];

  Copy(a,a+sz,b+sz);
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=(a[i].x==b[i+sz].x);
  }
  print_result(success,5);
}

struct WithMove
{
  int x;
  WithMove():x(0) {}

  WithMove& operator=(WithMove&& rhs)
  {
    std::cout << "Move assignment is called!\n";
    x=1;
    rhs.x=2;
    return *this;
  }

  WithMove& operator=(const WithMove& rhs)
  {
    std::cout << "Assignment is called!\n";
    x=2;
    return *this;
  }
};

void test_move()
{
  constexpr size_t sz = 3;
  using test_type = WithMove;
  
  test_type a[sz];
  test_type b[sz];

  Copy(std::make_move_iterator(std::begin(a)),
       std::make_move_iterator(std::end(a)),
       b);
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=(a[i].x==2 && b[i].x==1);
  }
  print_result(success,6);
}

void test_copy()
{
  constexpr size_t sz = 3;
  using test_type = WithMove;
  
  test_type a[sz];
  test_type b[sz];

  Copy(a,a+sz,b);
  
  bool success=true;
  for (size_t i=0;i<sz;++i) {
    success&=(b[i].x==2 && a[i].x==0);
  }
  print_result(success,7);
}

