#include <iostream>
#include <tuple>

#include "BoostAlign.hpp"
#include "Print.hpp"

int main()
{
  using tpl = std::tuple<double,char,const char*,int>;

  using decoder = typename AlignTupleSort<tpl>::decoder;

  auto ts = make_sorted_tuple(1.0,'a',"Hello",4);
  
  std::cout << decoder::get<2>(ts) << '\n';

  return 0;
}
