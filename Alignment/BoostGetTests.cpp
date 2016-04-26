#include <iostream>
#include <tuple>
#include <utility>
#include <string>

#include "BoostAlign.hpp"
#include "Print.hpp"

template<size_t N>
struct StdGetter
{
  template<typename T>
  constexpr static
  auto get(const T& t)
  { 
    return std::get<N>(t);
  }   
};

template<template<size_t>class Getter,
	 size_t...S,typename...Types>
void tuple_values_print_impl(std::index_sequence<S...>,
			     const std::tuple<Types...>& t)
{
  std::cout << '(';
  int dummy[]
  {(std::cout << Getter<S>::get(t) 
    << (S==sizeof...(S)-1?')':' '),0)...};
}

template<template<size_t>class Getter,
	 typename...Types>
void tuple_values_print(const std::tuple<Types...>& t)
{
  tuple_values_print_impl<Getter>
    (std::make_index_sequence<sizeof...(Types)>(),t);
}

struct Test
{
  template<typename T>
  struct Impl
  {
    template<size_t N>
    struct Getter
    {
      template<typename Tpl>
      constexpr static
      auto get(const Tpl& t)
      { 
	return T::decoder::template get<N>(t);
      }   
    };

    template<typename...Args>
    static void test_impl(const Args&&... args)
    {
      using tpl = std::tuple<Args...>;
      using sorted = typename AlignTupleSort<tpl>::type;

      sorted ts = 
	AlignTupleSort<tpl>::make_sorted_tuple(args...);
   
      tuple_values_print<StdGetter>(ts);
      std::cout << '\n';
      tuple_values_print<Getter>(ts);
      std::cout << '\n';
    }
  };

  template<typename...Args>
  static void test(const Args&&... args)
  {
    Impl<AlignTupleSort<std::tuple<Args...>>>::
      test_impl(std::forward<decltype(args)>(args)...);
  }
};

int main()
{
  Test::test(1.0,'a',std::string("Hello"),4);
  return 0;
}

