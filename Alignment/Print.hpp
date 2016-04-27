#ifndef PRINT_FUNC_HPP_INCLUDED
#define PRINT_FUNC_HPP_INCLUDED

#include <tuple>
#include <iostream>
#include <typeinfo>

void print_types(){}

template<typename T>
void print_types(T t)
{
  std::cout << typeid(T).name() << ':' << alignof(T);
}

template<typename T,typename... Args>
void print_types(T t,Args... args)
{
  std::cout << typeid(T).name() << ':' << alignof(T) << ", ";
  print_types(args...);
}

template<typename...S>
void print_tuple(std::tuple<S...>)
{
  std::cout << '(';
  print_types(S()...);
  std::cout << ')';
}

template<template<size_t>class Getter,
	 size_t...S,typename...Types>
void tuple_values_print_impl(std::index_sequence<S...>,
			     const std::tuple<Types...>& t)
{
  std::cout << '(';
  using process_pack = bool[];
  (void)process_pack
    {0,(std::cout 
	<< Getter<S>::get(t) 
	<< ':'
	<< alignof(decltype(Getter<S>::get(t)))
	<< (S==sizeof...(S)-1?')':','),0)...};
  if (sizeof...(S)==0)
    std::cout << ')';
}

template<template<size_t>class Getter,
	 typename...Types>
void tuple_values_print(const std::tuple<Types...>& t)
{
  tuple_values_print_impl<Getter>
    (std::make_index_sequence<sizeof...(Types)>(),t);
}

#endif
