#include <iostream>
#include <boost/hana.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>

namespace hana = boost::hana;
using integer_sequence_tag = hana::ext::std::integer_sequence_tag;

namespace boost::hana
{
  // Monoid
  template <>
  struct zero_impl<integer_sequence_tag>
  {
    static constexpr auto apply()
      -> std::index_sequence<>
    { return {}; }
  };

  template <>
  struct plus_impl<integer_sequence_tag, integer_sequence_tag>
  {
    template <std::size_t ...x, std::size_t ...y>
    static constexpr auto apply(std::index_sequence<x...>, std::index_sequence<y...>)
      -> std::index_sequence<x..., y...>
    { return {}; }
  };
}

void print(int x)
{
  std::cout << x << '\n';
}

template <std::size_t ...i>
void print(std::index_sequence<i...>)
{
  (std::cout << ... << i) << '\n';
}

int main()
{
  print(5);
  print(std::make_index_sequence<10>{});
  print(
    hana::plus(
      std::make_index_sequence<10>{}
    , std::index_sequence<10, 11, 12, 13, 14>{}
    )
  );
}
