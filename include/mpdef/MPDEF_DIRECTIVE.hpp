//
// Copyright Jason Rice 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef NBDL_MPDEF_DIRECTIVE_HPP
#define NBDL_MPDEF_DIRECTIVE_HPP

#include <mpdef/list.hpp>
#include <mpdef/map.hpp>
#include <mpdef/tree_node.hpp>

#include <boost/hana.hpp>

#define MPDEF_DIRECTIVE(NAME)                           \
namespace tag {                                         \
  struct NAME##_t {};                                   \
  constexpr auto NAME = boost::hana::type_c<NAME##_t>;  \
}                                                       \
template<typename... Tn> constexpr auto NAME(Tn...)  \
{ return mpdef::make_tree_node(tag::NAME, mpdef::make_map(Tn{}...)); }

#define MPDEF_DIRECTIVE_LIST(NAME)                                              \
namespace tag {                                                                 \
  struct NAME##_t {};                                                           \
  constexpr auto NAME = boost::hana::type_c<NAME##_t>;                          \
}                                                                               \
template<typename... Tn> constexpr auto NAME(Tn...)                             \
{ return mpdef::tree_node<decltype(tag::NAME), mpdef::list<Tn...>>{}; };

#define MPDEF_DIRECTIVE_LEAF(NAME)                      \
namespace tag {                                         \
  struct NAME##_t {};                                   \
  constexpr auto NAME = boost::hana::type_c<NAME##_t>;  \
}                                                       \
template<typename T> constexpr auto NAME(T)             \
{ return mpdef::tree_node<decltype(tag::NAME), T>{}; };

#endif
