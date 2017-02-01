#include <array>
#include <boost/hana.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <boost/hana/experimental/printable.hpp>
#include <iostream>
#include <vector>
#include <utility>

#include "fold_left.hpp"

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

namespace example
{
  template <typename Xs>
  std::size_t size(Xs const& xs)
  {
    return xs.size();
  }

  template <std::size_t ...x>
  std::size_t size(std::index_sequence<x...>)
  {
    return sizeof...(x);
  }
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

/*************
 * sum
 *   Note that iterating like this is bad.
 *************/

template <typename Xs>
auto sum(Xs const& xs)
{
  return example::fold_left(xs, [](auto const& state, auto const& x)
  {
    return hana::plus(state, x);
  });
}

int main()
{
  print(
    sum(std::vector<int>{0, 1, 2, 3, 4, 5})
  );
  print(
    sum(std::array<int, 6>{0, 1, 2, 3, 4, 5})
  );
  print(
    sum(
      hana::make_tuple(
        std::index_sequence<0>{}
      , std::index_sequence<1>{}
      , std::index_sequence<2>{}
      , std::index_sequence<3, 4, 5>{}
      )
    )
  );
}
