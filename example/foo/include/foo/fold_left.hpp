#ifndef NBDL_EXAMPLE_FOO_FOLD_LEFT_HPP
#define NBDL_EXAMPLE_FOO_FOLD_LEFT_HPP

#include <boost/hana.hpp>
#include <boost/hana/ext/std/array.hpp>
#include <utility>

namespace foo
{
  namespace hana = boost::hana;

  template <typename Tag, typename = void>
  struct fold_left_impl;

  struct fold_left_fn
  {
    template <typename Xs, typename Fn>
    auto operator()(Xs&& xs, Fn&& fn) const
    {
      using Tag = hana::tag_of_t<Xs>;

      return fold_left_impl<Tag>::apply(
        std::forward<Xs>(xs)
      , std::forward<Fn>(fn)
      );
    }
  };

  constexpr fold_left_fn fold_left{};

  template <typename Tag>
  struct fold_left_impl<Tag, std::enable_if_t<!hana::Foldable<Tag>::value>>
  {
    template <typename Xs, typename Fn>
    static constexpr auto apply(Xs&& xs, Fn const& fn)
    {
      auto state = *xs.begin();
      for (auto const& x : xs)
      {
        state = fn(state, x);
      }
      return state;
    }
  };

  template <typename Tag>
  struct fold_left_impl<Tag, std::enable_if_t<hana::Foldable<Tag>::value>>
  {
    template <typename Xs, typename Fn>
    static constexpr auto apply(Xs&& xs, Fn&& fn)
    {
      return hana::fold_left(
        std::forward<Xs>(xs)
      , std::forward<Fn>(fn)
      );
    }
  };
}

#endif
