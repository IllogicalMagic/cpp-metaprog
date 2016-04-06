#ifndef COPY_HPP_DEFINED_
#define COPY_HPP_DEFINED_

#include <iostream>
#include <cstring>
#include <type_traits>

#include "mTypeTraits.hpp"

template<typename In, typename Out>
void CopyFast(In* begin, In* end, Out* out)
{
  std::cout << "MemCpy!\n";
  std::memcpy((void*)out,
	      (const void*)begin,
	      (end-begin)*sizeof(In));
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
  using in_type = typename std::remove_cv
    <typename getPointedType<In>::type>::type;
  using out_type = typename std::remove_volatile
    <typename getPointedType<Out>::type>::type;

  static_assert
    (std::is_assignable<out_type&,in_type>::value,
     "Out type is not assignable");
  static_assert
    (std::is_same<out_type,in_type>::value,
     "In and out types are not the same");

  CopySelect<
    (std::is_pointer<In>::value && std::is_pointer<Out>::value) &&
    ((std::is_trivially_copyable<in_type>::value &&
      std::is_trivially_copyable<out_type>::value) ||
     (hasBitwiseCopy<in_type>::value &&
      hasBitwiseCopy<out_type>::value)),
    In,Out>::select(begin,end,out);
}

#endif

