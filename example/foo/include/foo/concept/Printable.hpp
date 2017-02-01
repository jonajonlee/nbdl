#ifndef NBDL_EXAMPLE_FOO_CONCEPT_PRINTABLE_HPP
#define NBDL_EXAMPLE_FOO_CONCEPT_PRINTABLE_HPP

#include <boost/hana.hpp>

namespace foo
{
  namespace hana = boost::hana;

  // fwd decl
  template <typename Tag>
  struct print_impl;

  template<typename T>
  struct Printable
  {
    using Tag = typename hana::tag_of<T>::type;
    static constexpr bool value = !hana::is_default<
      foo::print_impl<Tag>
    >::value;
  };
}

#endif
