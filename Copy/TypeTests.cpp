#include <array>
#include <tuple>
#include <vector>
#include <typeinfo>
#include <iostream>

#include "mTypeTraits.hpp"

// Trivially copyable
struct DefCopy
{
  DefCopy(const DefCopy&) = default;
};

// Non-copyable
struct DelCopy
{
  DelCopy(const DelCopy&) = delete;
};

// Trivially copyable
struct ImplicitCopy {};

// Non-copyable
struct MoveCtor
{
  MoveCtor(MoveCtor&&) {} 
};

// Non-trivially copyable
struct UserCopy
{
  UserCopy(const UserCopy&) {}
};

template<typename T>
void test_copy()
{
  if (isTriviallyCopyable<T>::value)
    std::cout << typeid(T).name() << " is trivially copyable\n";
  else
    std::cout << typeid(T).name() << " is not trivially copyable\n";
}

template<typename T, typename T1, typename...Rest>
void test_copy()
{
  test_copy<T>();
  test_copy<T1,Rest...>();
}

int main()
{
  test_copy<DefCopy,DelCopy,ImplicitCopy,MoveCtor,UserCopy,
	    std::vector<DefCopy>,std::vector<MoveCtor>,
	    std::array<ImplicitCopy,3>,std::array<UserCopy,10>>();
  return 0;
}
