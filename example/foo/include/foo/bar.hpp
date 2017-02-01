#ifndef NBDL_EXAMPLE_FOO_BAR_HPP
#define NBDL_EXAMPLE_FOO_BAR_HPP

#include <boost/hana.hpp>
#include <utility>

namespace foo
{
  namespace hana = boost::hana;

  struct bar_fn
  {
    template <typename Xs>
    auto operator()(Xs const& xs) const
    {
      return hana::chain(xs, [](auto x)
      {
        using X = decltype(x);

        if constexpr(X::value % 2 == 0)
        {
          return hana::make_tuple(x); 
        }
        else
        {
          return hana::make_tuple(); 
        }
      });
    }
  };

  constexpr bar_fn bar{};
}

#endif
