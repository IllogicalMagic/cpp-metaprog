#ifndef TMP_UTILS_H_INC_
#define TMP_UTILS_H_INC_

#include <tuple>
#include <array>

// Number sequence generator (NSG)
template<int...>
struct Seq {};

template<int N, int... R>
struct Gen: Gen<N-1,N-1,R...> {};

template<int... R>
struct Gen<0,R...>
{
  typedef Seq<R...> seq;
};
// NSG end

typedef std::array<int,0>::size_type arr_sz;

// Map
template<int... ST,int... SF, 
	 typename F, typename... FArgs, typename... TArgs>
constexpr auto
map_(Seq<ST...>,Seq<SF...>,
     const F&& func,const std::tuple<FArgs...>&& fpar,
     const std::tuple<TArgs...>&& t)
{
  return std::make_tuple(func(std::move(std::get<ST>(t)),
			      std::move(std::get<SF>(fpar))...)...);
}

template<int... ST,int... SF,
	 typename F,typename... FArgs,
	 typename T,arr_sz N>
constexpr auto
map_(Seq<ST...>,Seq<SF...>,
     const F&& func,const std::tuple<FArgs...>&& fpar,
     const std::array<T,N>&& t)
{
  return std::array<T,N>
    {func(std::move(std::get<ST>(t)),
	  std::move(std::get<SF>(fpar))...)...};
}

// Main map func
template<typename F,typename... FArgs, typename Cont>
constexpr auto
map(const F&& func,const std::tuple<FArgs...>&& fpar,
    const Cont&& t)
{
  return map_(typename Gen<std::tuple_size<Cont>::value>::seq(),
	      typename Gen<sizeof...(FArgs)>::seq(),
	      std::forward<decltype(func)>(func),
	      std::forward<decltype(fpar)>(fpar),
	      std::forward<decltype(t)>(t));
}
// Map end

// Tail
template<int... S,typename T,typename... Arg> 
constexpr auto 
tail_(Seq<S...>, const std::tuple<T,Arg...>&& t) -> std::tuple<Arg...>
{
  return std::make_tuple(std::get<S+1>(t)...);
}

template<int... S,typename T,arr_sz N> 
constexpr auto 
tail_(Seq<S...>, const std::array<T,N>&& t)
{
  return std::array<T,N-1> {std::get<S+1>(t)...};
}

// Main tail func
template<typename Cont> 
constexpr auto 
tail(const Cont&& t)
{
  static_assert(std::tuple_size<Cont>::value!=0,
		"tail is applied to empty container");
  return tail_(typename Gen<std::tuple_size<Cont>::value-1>::seq(),
	       std::forward<decltype(t)>(t));
}
// Tail end

// Head
template<typename Cont> constexpr
auto head(const Cont&& t)
{
  static_assert(std::tuple_size<Cont>::value!=0,
		"head is applied to empty container");
  return std::get<0>(t);
}
// Head end

// Append
template<int... S1,int... S2,typename... Arg1, typename... Arg2>
constexpr std::tuple<Arg1...,Arg2...> 
append_(Seq<S1...>,Seq<S2...>,
	const std::tuple<Arg1...>&& a,const std::tuple<Arg2...>&& b)
{
  return std::make_tuple
    (std::get<S1>(a)...,std::get<S2>(b)...);
}

template<int... S1,int... S2,
	 typename T, arr_sz N1, arr_sz N2>
constexpr std::array<T,N1+N2>
append_(Seq<S1...>,Seq<S2...>,
	const std::array<T,N1>&& a, const std::array<T,N2>&& b)
{
  return std::array<T,N1+N2> 
    {std::get<S1>(a)...,std::get<S2>(b)...};
}

// Main append func
template<typename C1,typename C2> 
constexpr auto
append(const C1&& a,
       const C2&& b)  
{
  return append_(typename Gen<std::tuple_size<C1>::value>::seq(),
		 typename Gen<std::tuple_size<C2>::value>::seq(),
		 std::forward<decltype(a)>(a),
		 std::forward<decltype(b)>(b));
}

// Append end

// Reverse
constexpr std::tuple<>
reverse(const std::tuple<>&& t)
{
  return t;
}

template<typename T>
constexpr std::array<T,0>
reverse(const std::array<T,0>&& t)
{
  return t;
}

template<typename T,typename... Rest>
constexpr auto
reverse(const std::tuple<T,Rest...>&& t)
{
  return append(reverse(tail(std::forward<decltype(t)>(t))),
		std::make_tuple(head(std::forward<decltype(t)>(t))));
}

template<typename T,arr_sz N>
constexpr auto
reverse(const std::array<T,N>&& t)
{
  return append(reverse(tail(std::forward<decltype(t)>(t))),
		std::array<T,1>{head(std::forward<decltype(t)>(t))});
}
// Reverse end

// Simple Pow
template<long unsigned N, long unsigned E>
struct Pow
{
  enum {value=N*Pow<N,E-1>::value};
};

template<long unsigned N>
struct Pow<N,0>
{
  enum {value=1};
};
// Pow end

#endif

