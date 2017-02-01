#ifndef NBDL_EXAMPLE_FOO_PRINT_HPP
#define NBDL_EXAMPLE_FOO_PRINT_HPP

#include <boost/hana.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <iostream>
#include <utility>

#include <foo/concept/Printable.hpp>

namespace foo
{
  namespace hana = boost::hana;
  using integer_sequence_tag = hana::ext::std::integer_sequence_tag;

  // default implementation
  template <typename Tag>
  struct print_impl : hana::default_
  {
    template <typename X>
    static void apply(X const&) = delete;
  };

  struct print_fn
  {
    template <typename X>
    void operator()(X&& x) const
    {
      using Tag = hana::tag_of_t<X>;

      static_assert(foo::Printable<Tag>::value,
        "X is not foo::Printable");

      print_impl<Tag>::apply(std::forward<X>(x));
    }
  };

  constexpr print_fn print{};

  template <>
  struct print_impl<int>
  {
    static void apply(int x)
    {
      std::cout << x << '\n';
    }
  };

  template <>
  struct print_impl<integer_sequence_tag>
  {
    template <std::size_t ...i>
    static void apply(std::index_sequence<i...>)
    {
      (std::cout << ... << i) << '\n';
    }
  };

  template <>
  struct print_impl<hana::tuple_tag>
  {
    template <typename Xs>
    static void apply(Xs const& xs)
    {
      hana::for_each(xs, [](auto const& x)
      {
        print_fn{}(x);
      });
      std::cout << '\n';
    }
  };

  template <typename T>
  struct print_impl<hana::integral_constant_tag<T>>
  {
    template <typename X>
    static void apply(X)
    {
      std::cout << X::value;
    }
  };

}

#endif
