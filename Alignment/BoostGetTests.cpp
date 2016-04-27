#include <iostream>
#include <tuple>
#include <utility>
#include <string>
#include <complex>

#include "BoostAlign.hpp"
#include "Print.hpp"

template<size_t N>
struct StdGetter
{
  template<typename T>
  constexpr static
  auto get(const T& t)
  { 
    return std::get<N>(t);
  }   
};

struct Test
{
  // T will be captured by Getter
  template<typename T>
  struct Impl
  {
    template<size_t N>
    struct Getter
    {
      template<typename Tpl>
      constexpr static
      auto get(const Tpl& t)
      { 
	return T::decoder::template get<N>(t);
      }   
    };
    
    // Compare values
    template<typename...Types,
	     typename...Sorted,
	     size_t...S>
    static bool is_equal(const std::tuple<Types...>& old,
			 const std::tuple<Sorted...>& sorted,
			 std::index_sequence<S...>)
    {
      bool result=true;
      using process_pack = bool[];
      (void)process_pack 
	{0,result&=
	 (std::get<S>(old)==T::decoder::template get<S>(sorted))...};
      return result;
    }

    template<typename...Args>
    static void test_impl(const Args&&... args)
    {
      using tpl = std::tuple<Args...>;
      using sorted = typename AlignTupleSort<tpl>::type;

      tpl t = std::make_tuple(args...);
      sorted ts = 
	AlignTupleSort<tpl>::make_sorted_tuple(args...);
   
      std::cout << "Old: ";
      tuple_values_print<StdGetter>(t);
      std::cout << "\nSorted: ";
      tuple_values_print<StdGetter>(ts);
      std::cout << '\n';

      if (is_equal(t,ts,std::make_index_sequence<sizeof...(Args)>()))
      	std::cout << "Test passed!\n";
      else std::cout << "Test failed.\n";
    }
  };

  template<typename...Args>
  static void test(const Args&&... args)
  {
    Impl<AlignTupleSort<std::tuple<Args...>>>::
      test_impl(std::forward<decltype(args)>(args)...);
  }
};

void delim()
{
  std::cout << "---\n";
}

int main()
{
  Test::test(1.0,'a',std::string("Hello"),4);
  delim();
  Test::test(3.0,std::string("String"),'X',
  	     std::complex<float>(1.0,5.0));
  return 0;
}

