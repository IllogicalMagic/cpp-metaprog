#ifndef MY_STATIC_ASSERT_HPP_DEFINED
#define MY_STATIC_ASSERT_HPP_DEFINED

template<bool>
struct mStaticAssert;

template<>
struct mStaticAssert<true>
{
  mStaticAssert(const char*){}
};

template<>
class mStaticAssert<false>
{
  mStaticAssert(const char*){}
};

#endif

