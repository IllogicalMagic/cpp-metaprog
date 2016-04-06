#ifndef COPY_HPP_DEFINED_
#define COPY_HPP_DEFINED_

#include <iostream>
#include <cstring>
#include <vector>
#include <array>

#include "mTypeTraits.hpp"

template<typename In, typename Out>
void CopyFast(In* begin, In* end, Out* out)
{
  std::cout << "FastCopy!\n";
  std::memcpy(out,begin,(end-begin)*sizeof(decltype(*begin)));
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
  CopySelect<isPointer<In>::value && isPointer<Out>::value 
	     && isTriviallyCopyable<decltype(*begin)>::value 
	     && isTriviallyCopyable<decltype(*out)>::value 
	     && isEqualSizePtr<In,Out>::value,
	     In,Out>::select(begin,end,out);
}

#endif

