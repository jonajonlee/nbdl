//
// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef NBDL_PIPE_HPP
#define NBDL_PIPE_HPP

#include <nbdl/catch.hpp>
#include <nbdl/detail/pipe_rejection.hpp>

#include <boost/hana/core/is_a.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/functional/overload_linearly.hpp>
#include <type_traits>
#include <utility>

namespace nbdl
{
  namespace hana = boost::hana;

  namespace detail
  {
    struct end_pipe_fn
    {
      template <typename ...Args>
      void operator()(Args&& ...) const
      {
        static_assert(!is_pipe_rejection<std::decay_t<Args>...>::value, "Unhandled Rejection!");
      }
    };

    template <typename Handlers>
    struct pipe_t
    {
      Handlers handlers;

      pipe_t(Handlers&& h)
        : handlers(std::move(h))
      { } 

      template <typename InitialValue>
      decltype(auto) operator()(InitialValue&& value)
      {
        hana::fold_right(handlers, end_pipe_fn{}, [](auto& x, auto&& state)
        {
          return [resolve = std::move(state), &x](auto&& ...results)
          {
            if constexpr(!is_pipe_rejection<std::decay_t<decltype(results)>...>::value)
            {
              x(
                resolve,
                [&](auto&& ...args)
                {
                  resolve(pipe_rejection{}, std::forward<decltype(args)>(args)...);
                },
                std::forward<decltype(results)>(results)...
              );
            }
            else if constexpr(hana::is_a<catch_tag, decltype(x)>())
            {
              hana::overload_linearly(x, resolve)(std::forward<decltype(results)>(results)...);
            }
            else
            {
              resolve(std::forward<decltype(results)>(results)...);
            }
          };
        })(std::forward<InitialValue>(value));

        return *this;
      }
    };
  }

  struct pipe_fn
  {
    template <typename ...Args>
    auto operator()(Args&&... args) const
    {
      using Tuple = decltype(hana::make_tuple(std::forward<Args>(args)...));
      return detail::pipe_t<Tuple>{hana::make_tuple(std::forward<Args>(args)...)};
    }
  };

  constexpr pipe_fn pipe{};
}

#endif
