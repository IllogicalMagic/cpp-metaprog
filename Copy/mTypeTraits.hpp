#ifndef _MY_TYPE_TRAITS_HPP_
#define _MY_TYPE_TRAITS_HPP_

template<typename Iter>
struct getPointedType
{
  using type = typename Iter::value_type;
};

template<typename T>
struct getPointedType<T*>
{
  using type = T;
};

template<typename T>
struct hasBitwiseCopy
{
  static constexpr bool value = false;
};

#endif
