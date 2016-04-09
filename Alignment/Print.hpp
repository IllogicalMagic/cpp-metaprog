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

#endif
