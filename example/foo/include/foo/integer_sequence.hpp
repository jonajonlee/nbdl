#ifndef NBDL_EXAMPLE_FOO_INTEGER_SEQUENCE_HPP
#define NBDL_EXAMPLE_FOO_INTEGER_SEQUENCE_HPP

#include <boost/hana.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <utility>

namespace foo
{
  namespace hana = boost::hana;
  using integer_sequence_tag = hana::ext::std::integer_sequence_tag;
}

namespace boost::hana
{
  // Monoid

  template <>
  struct zero_impl<foo::integer_sequence_tag>
  {
    static constexpr auto apply()
      -> std::index_sequence<>
    { return {}; }
  };

  template <>
  struct plus_impl<foo::integer_sequence_tag, foo::integer_sequence_tag>
  {
    template <std::size_t ...x, std::size_t ...y>
    static constexpr auto apply(std::index_sequence<x...>, std::index_sequence<y...>)
      -> std::index_sequence<x..., y...>
    { return {}; }
  };
}

#endif
