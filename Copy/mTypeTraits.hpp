#ifndef _MY_TYPE_TRAITS_HPP_
#define _MY_TYPE_TRAITS_HPP_

// isTriviallyCopyable
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

template<typename T>
struct isTriviallyCopyable<T&>
{
  static constexpr bool value = isTriviallyCopyableImpl<T>::value;  
};
// isTriviallyCopyable

// isPointer
template<typename T>
struct isPointer
{
  static constexpr bool value = false;
};

template<typename T>
struct isPointer<T*>
{
  static constexpr bool value = true;
};
// isPointer end

// isEqualSizePtr
template<typename T1, typename T2>
struct isEqualSizePtr
{
  static constexpr bool value = 
    sizeof(typename T1::value_type) == sizeof(typename T2::value_type);
};

template<typename T1, typename T2>
struct isEqualSizePtr<T1,T2*>
{
  static constexpr bool value = 
    sizeof(typename T1::value_type) == sizeof(T2);
};

template<typename T1, typename T2>
struct isEqualSizePtr<T1*,T2>
{
  static constexpr bool value = 
    sizeof(T1) == sizeof(typename T2::value_type);
};

template<typename T1, typename T2>
struct isEqualSizePtr<T1*,T2*>
{
  static constexpr bool value = sizeof(T1) == sizeof(T2);
};

// isEqualSizePtr end

#endif
