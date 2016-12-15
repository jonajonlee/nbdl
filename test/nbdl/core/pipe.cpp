//
// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <nbdl/pipe.hpp>

#include <catch.hpp>
#include <boost/hana.hpp>

namespace hana = boost::hana;

namespace
{
  template <int i>
  auto make_op()
  {
    return [](auto&& resolve, auto&& /* reject */, auto&& state)
    { resolve(hana::append(state, i)); };
  }
  template <int i>
  auto op = make_op<i>();

  auto tap = [](auto fn)
  {
    return [fn_ = std::move(fn)](auto&& resolve, auto&&, auto&& state)
    {
      using State = decltype(state);
      fn_(state);
      resolve(std::forward<State>(state));
    };
  };
}

TEST_CASE("Pipe asynchronous events", "[pipe]")
{
  auto pipe = nbdl::pipe(
    op< 1 >,
    tap([](auto const& state) { CHECK(hana::equal(state, hana::make_tuple(42, 1))); }),
    op< 2 >,
    op< 3 >,
    op< 4 >,
    tap([](auto const& state) { CHECK(hana::equal(state, hana::make_tuple(42, 1, 2, 3, 4))); })
  )(hana::make_tuple(42));
  (void)pipe;
}

TEST_CASE("Pipe with a rejection", "[pipe]")
{
  bool check1 = false;

  auto pipe = nbdl::pipe(
    op< 1 >
  , [](auto&&, auto&& reject, auto&&) { reject(hana::int_c<1>); }
  , tap([](auto const&) { CHECK(false); })
  , op< 3 >
  , tap([](auto const&) { CHECK(false); })
  , op< 4 >
  , nbdl::catch_([&](hana::int_<1>) { check1 = true; })
  , nbdl::catch_([&](hana::int_<2>) { CHECK(false); })
  )(hana::make_tuple(42));
  (void)pipe;

  CHECK(check1);
}

TEST_CASE("Pipe with a rejection", "[pipe]")
{
  bool check1 = false;

  auto pipe = nbdl::pipe(
    op< 1 >
  , [](auto&&, auto&& reject, auto&&) { reject(hana::int_c<2>); }
  , tap([](auto const&) { CHECK(false); })
  , op< 3 >
  , tap([](auto const&) { CHECK(false); })
  , op< 4 >
  , nbdl::catch_([&](hana::int_<1>) { CHECK(false); })
  , nbdl::catch_([&](hana::int_<2>) { check1 = true; })
  )(hana::make_tuple(42));
  (void)pipe;

  CHECK(check1);
}
