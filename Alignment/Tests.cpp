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
void print_msg()
{
  std::cout << "sizeof ";
  print(T());
  std::cout << " == " << sizeof(T) << '\n';
}

int main()
{ 
  using t = std::tuple<short,double,int,char,short,void*,char>;
  using sorted = typename TupleSort<t>::type;
  print_msg<t>();
  print_msg<sorted>();
  return 0;
}
