#ifndef GRAY_SHARED_H_DEFINED_
#define GRAY_SHARED_H_DEFINED_

#ifndef G_BITS
#define G_BITS 4ul
#endif

#ifndef G_VIEW
#define G_VIEW DECIMAL
#endif

#if __cplusplus==199711L

typedef unsigned long g_uint_t;

#else

#include <cstdint>

typedef std::uint64_t g_uint_t;

#endif


// Simple Pow
template<g_uint_t N, g_uint_t E>
struct Pow
{
  enum {value=N*Pow<N,E-1>::value};
};

template<g_uint_t N>
struct Pow<N,0>
{
  enum {value=1};
};
// Pow end

// Decimal -> Binary converter
template<g_uint_t N,g_uint_t Res=0,g_uint_t Mult=1>
struct DecToBin: DecToBin< (N>>1), Res+(N&1)*Mult,Mult*10>
{};

template<g_uint_t Res,g_uint_t Mult>
struct DecToBin<0,Res,Mult>
{
  enum {value=Res};
};
// DecToBin end

typedef g_uint_t code_t;
typedef code_t codesize_t;

enum GrayView {BINARY,DECIMAL};

// GrayVisualize
// Produce binary or decimal code
template<code_t N, GrayView V>
struct GrayVisualize;

template<code_t N>
struct GrayVisualize<N,BINARY>
{
  enum {value=DecToBin<N>::value};
};

template<code_t N>
struct GrayVisualize<N,DECIMAL>
{
  enum {value=N};
};
// GrayVisualize end

// Encoder
template<code_t N>
struct GrayEncode
{
  enum {value=N^(N>>1)};
};
// Encoder end

// Decoder
template<code_t N>
struct GrayDecode
{
  enum {value=GrayDecode<(N>>1)>::value ^ N};
};

template<>
struct GrayDecode<0>
{
  enum {value=0};
};
// Decoder end

#endif
