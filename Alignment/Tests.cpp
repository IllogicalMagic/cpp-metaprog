#include <iostream>
#include <typeinfo>

#include "Align.hpp"

void print(){}

template<typename T>
void print(T t)
{
  std::cout << typeid(T).name() << ':' << alignof(T);
}

template<typename T,typename... Args>
void print(T t,Args... args)
{
  std::cout << typeid(T).name() << ':' << alignof(T) << ", ";
  print(args...);
}

template<typename...S>
void print(std::tuple<S...>)
{
  std::cout << '(';
  print(S()...);
  std::cout << ')';
}

template<typename T>
void print_size()
{
  std::cout << "sizeof ";
  print(T());
  std::cout << " == " << sizeof(T) << '\n';
}

template<typename Tpl1,typename Tpl2>
void print_result(int n)
{
  std::cout << "Test " << n;
  if (sizeof(Tpl2)<=sizeof(Tpl1))
    std::cout << " passed!\n";
  else
    std::cout << " failed.\n";
}

template<typename T1,typename T2>
void test_shared(int n);

void test_simple();
void test_different();
void test_structs();
void test_same();
void test_empty();

int main()
{ 
  test_simple();
  test_different();
  test_structs();
  test_same();
  test_empty();
  return 0;
}

template<typename T1,typename T2>
void test_shared(int n)
{
  print_result<T1,T2>(n);
  print_size<T1>();
  print_size<T2>();
}

void test_simple()
{
  using t = std::tuple<char,double,short>;
  using sorted = typename TupleSort<t>::type;
  test_shared<t,sorted>(1);
}

void test_different()
{
  using t = std::tuple<char,long double,bool,double,short,long long,bool>;
  using sorted = typename TupleSort<t>::type;
  test_shared<t,sorted>(2);
}

struct A4_S12 {int a[3];};
struct A8_S32 {double a[4];};
struct A1_S19 {char a[19];};

void test_structs()
{
  using t = std::tuple<char,A8_S32,A1_S19,double,A4_S12>;
  using sorted = typename TupleSort<t>::type;
  test_shared<t,sorted>(3);
}

void test_same()
{
  using t = std::tuple<char,bool,signed char,unsigned char>;
  using sorted = typename TupleSort<t>::type;
  test_shared<t,sorted>(4);
}

void test_empty()
{
  using t = std::tuple<>;
  using sorted = typename TupleSort<t>::type;
  test_shared<t,sorted>(5);
}

