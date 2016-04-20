#include <iostream>
#include <type_traits>
#include <string>

#include "Align.hpp"
#include "Print.hpp"

void triv_copy();
template<int N,typename...Types>
void size_less_than();

template<typename T1,typename T2>
void msg_general();

int main()
{
  triv_copy();
  size_less_than<2,char,int,bool,short>();
  size_less_than<8,double,long double,short,int,char,bool,double>();
  return 0;
}

template<typename T1,typename T2>
void msg_general(const char* test_name, int n = 0)
{
  std::cout << test_name << n << ":\n";
  print_tuple(T1());
  std::cout << '\n';
  print_tuple(T2());
  std::cout << '\n';
  std::cout << test_name << n << " ended!\n";
}

// Sort :: tuple -> tuple<triv_copy...,non-triv_copy...>
template<typename T>
struct TrivCopySort
{
  using type = 
    typename TupleSortImpl<T,std::is_trivially_copyable,
			   std::integer_sequence<bool,true,false>>::type;
};

struct A 
{
  A() = default;
  A(const A&){};
};

struct B: A {};

void triv_copy()
{
  using t = std::tuple<A,char,B,A,int,double,char>;
  using sorted = typename TrivCopySort<t>::type;
  msg_general<t,sorted>("Triv_copy");
}

// Sort :: tuple -> tuple<sizeof(E)<N..., sizeof(E)>=N...>
template<int N>
struct LessThan
{
  template<typename T>
  struct LessThanN
  {
    static constexpr bool value = sizeof(T)<N;
    using value_type = bool;
  };
};

template<typename T,int N>
struct LessThanSort
{
  template<typename E>
  using ValFunc = typename LessThan<N>::template LessThanN<E>;
  
  using type = 
    typename TupleSortImpl<T,ValFunc,
			   std::index_sequence<true,false>>::type;
};

template<int N,typename...Types>
void size_less_than()
{
  using t = std::tuple<Types...>;
  using sorted = typename LessThanSort<t,N>::type;
  msg_general<t,sorted>("Size_less_than",N);
}
