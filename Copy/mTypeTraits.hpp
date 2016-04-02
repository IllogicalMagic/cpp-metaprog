#ifndef _MY_TYPE_TRAITS_HPP_
#define _MY_TYPE_TRAITS_HPP_

template<typename T>
struct isTriviallyCopyableImpl
{
  union U {T a;};
  typedef U* no[2];
  
  template<typename X>
  static constexpr auto
  isCpb(const X* x) -> decltype(new X(*x));
  
  template<typename X>
  static constexpr no&
  isCpb(...);
  
  static constexpr bool value = 
    sizeof( isCpb<U>(nullptr) )!=sizeof(no);
};


template<typename T>
struct isTriviallyCopyable
{
  static constexpr bool value = isTriviallyCopyableImpl<T>::value;  
};

#endif
