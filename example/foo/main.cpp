#include <array>
#include <boost/hana.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <vector>
#include <utility>

#include <foo/bar.hpp>
#include <foo/fold_left.hpp>
#include <foo/integer_sequence.hpp>
#include <foo/print.hpp>

namespace hana = boost::hana;

/*************
 * sum
 *************/

template <typename Xs>
auto sum(Xs const& xs)
{
  return foo::fold_left(xs, [](auto const& state, auto const& x)
  {
    return hana::plus(state, x);
  });
}

int main()
{
  foo::print(
    sum(std::vector<int>{0, 1, 2, 3, 4, 5})
  );
  foo::print(
    sum(std::array<int, 6>{{0, 1, 2, 3, 4, 5}})
  );
  foo::print(
    sum(
      hana::make_tuple(
        std::index_sequence<0>{}
      , std::index_sequence<1>{}
      , std::index_sequence<2>{}
      , std::index_sequence<3, 4, 5>{}
      )
    )
  );
  foo::print(
    foo::bar(hana::tuple_c<int, 0, 1, 2, 3, 4, 5, 6, 7 ,8, 9>)
  );

  foo::print('\n');
}
