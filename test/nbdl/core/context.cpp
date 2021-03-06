//
// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <assets/TestContext.hpp>
#include <nbdl/make_context.hpp>
#include <nbdl/make_def.hpp>
#include <nbdl/message.hpp>
#include <nbdl/null_store.hpp>

#include <boost/hana/equal.hpp>
#include <boost/hana/value.hpp>
#include <catch.hpp>

namespace hana    = boost::hana;
namespace entity  = test_context::entity;
namespace message = nbdl::message;
namespace channel = nbdl::message::channel;
namespace action  = nbdl::message::action;

namespace
{
  struct my_context { };
}

namespace nbdl
{
  template <>
  struct make_def_impl<my_context>
  {
    static constexpr auto apply()
    {
      return test_context_def::make(
        test_context::provider_tag{},
        test_context::provider_tag{},
        test_context::consumer_tag{},
        test_context::consumer_tag{},
        nbdl::null_store{}
      );
    }
  };
}


namespace
{
  auto context = nbdl::make_unique_context<my_context>();

  auto& provider0 = context->cell<0>();
  auto& provider1 = context->cell<1>();
  auto& consumer2 = context->cell<2>();
  auto& consumer3 = context->cell<3>();

  void init_record_messages()
  {
    provider0.recorded_messages = {};
    provider1.recorded_messages = {};
    consumer2.recorded_messages = {};
    consumer3.recorded_messages = {};
  }

  struct check_message_equal_fn
  {
    template <typename Message, typename Orig>
    constexpr auto operator()(Message const& m, Orig const& o) const
    {
      return m.match(
        [&](auto const& m)
          -> std::enable_if_t<std::is_same<std::decay_t<decltype(m)>, std::decay_t<Orig>>::value, bool>
        {
          CHECK(hana::equal(
            hana::decltype_(message::get_channel(m)),
            hana::decltype_(message::get_channel(o))
          ));
          CHECK(hana::equal(
            hana::decltype_(message::get_action(m)),
            hana::decltype_(message::get_action(o))
          ));
          CHECK(hana::equal(message::get_path(m), message::get_path(o)));
          CHECK(hana::equal(message::get_maybe_payload(m), message::get_maybe_payload(o)));
          CHECK(hana::equal(message::get_maybe_private_payload(m), message::get_maybe_private_payload(o)));
          CHECK(hana::equal(message::get_maybe_is_from_root(m), message::get_maybe_is_from_root(o)));
          // TODO compare nbdl::uids
          return true;
        },
        [](auto const&) { return false; }
      );
    }
  };

  constexpr struct check_message_equal_fn check_message_equal{};
}

TEST_CASE("Dispatch Downstream Read Message", "[context]")
{
  init_record_messages();

  // Send downstream read to consumers.
  auto msg = provider0.push_api.message_api().make_downstream_read_message(
      test_context::path1(1, 2),
      entity::my_entity<1>{2, 1}
  );
  provider0.push_api.push(msg);

  CHECK(provider0.recorded_messages.size() == 0);
  CHECK(provider1.recorded_messages.size() == 0);
  CHECK(consumer2.recorded_messages.size() == 1);
  CHECK(consumer3.recorded_messages.size() == 1);

  // Both consumers got the downstream
  // read message from provider0
  CHECK(check_message_equal(consumer2.recorded_messages[0], msg));
  CHECK(check_message_equal(consumer3.recorded_messages[0], msg));
}

TEST_CASE("Dispatch Upstream Read Message", "[context]")
{
  init_record_messages();

  // Send upstream read to provider0.
  auto msg = consumer2.push_api.message_api().make_upstream_read_message(test_context::path1(1, 2));
  consumer2.push_api.push(msg);

  // provider1 should not receive the message.
  CHECK(provider0.recorded_messages.size() == 1);
  CHECK(provider1.recorded_messages.size() == 0);
  CHECK(consumer2.recorded_messages.size() == 0);
  CHECK(consumer3.recorded_messages.size() == 0);

  // provider0 should record an upstream read message.
  CHECK(check_message_equal(provider0.recorded_messages[0], msg));
}

TEST_CASE("Dispatch Downstream Create Message", "[context]")
{
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<0>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<1>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<2>>, hana::type_c<entity::my_entity<2>>),
    hana::make_pair(hana::type_c<test_context::path<3>>, hana::type_c<entity::my_entity<3>>),
    hana::make_pair(hana::type_c<test_context::path<4>>, hana::type_c<entity::my_entity<4>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send downstream create to consumers.
    auto msg = provider0.push_api.message_api().make_downstream_create_message(
      Path(1, 2),
      Entity{2, 1}
    );
    provider0.push_api.push(msg);

    CHECK(provider0.recorded_messages.size() == 0);
    CHECK(provider1.recorded_messages.size() == 0);
    CHECK(consumer2.recorded_messages.size() == 1);
    CHECK(consumer3.recorded_messages.size() == 1);

    // Both consumers got the downstream
    // create message from provider0
    CHECK(check_message_equal(consumer2.recorded_messages[0], msg));
    CHECK(check_message_equal(consumer3.recorded_messages[0], msg));
  });
}

TEST_CASE("Dispatch Upstream Create Message", "[context]")
{
  // root1
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<0>>, hana::type_c<entity::my_entity<1>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send upstream create to provider0.
    auto msg = consumer2.push_api.message_api().make_upstream_create_message(
      Path::make_create_path(1),
      Entity{2, 1}
    );
    consumer2.push_api.push(msg);

    // provider1 should not receive the message.
    CHECK(provider0.recorded_messages.size() == 1);
    CHECK(provider1.recorded_messages.size() == 0);
    CHECK(consumer2.recorded_messages.size() == 0);
    CHECK(consumer3.recorded_messages.size() == 0);

    // provider0 should record an upstream create message.
    CHECK(check_message_equal(provider0.recorded_messages[0], msg));
  });

  // root2
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<1>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<2>>, hana::type_c<entity::my_entity<2>>),
    hana::make_pair(hana::type_c<test_context::path<3>>, hana::type_c<entity::my_entity<3>>),
    hana::make_pair(hana::type_c<test_context::path<4>>, hana::type_c<entity::my_entity<4>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send upstream create to provider0.
    auto msg = consumer2.push_api.message_api().make_upstream_create_message(
      Path::make_create_path(1),
      Entity{2, 1}
    );
    consumer2.push_api.push(msg);

    // provider0 should not receive the message.
    CHECK(provider0.recorded_messages.size() == 0);
    CHECK(provider1.recorded_messages.size() == 1);
    CHECK(consumer2.recorded_messages.size() == 0);
    CHECK(consumer3.recorded_messages.size() == 0);

    // provider1 should record an upstream create message.
    CHECK(check_message_equal(provider1.recorded_messages[0], msg));
  });
}

TEST_CASE("Dispatch Downstream Update Message", "[context]")
{
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<0>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<1>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<2>>, hana::type_c<entity::my_entity<2>>),
    hana::make_pair(hana::type_c<test_context::path<3>>, hana::type_c<entity::my_entity<3>>),
    hana::make_pair(hana::type_c<test_context::path<4>>, hana::type_c<entity::my_entity<4>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send downstream update to consumers.
    auto msg = provider0.push_api.message_api().make_downstream_update_raw_message(
      Path(1, 2),
      Entity{2, 1}
    );
    provider0.push_api.push(msg);

    CHECK(provider0.recorded_messages.size() == 0);
    CHECK(provider1.recorded_messages.size() == 0);
    CHECK(consumer2.recorded_messages.size() == 1);
    CHECK(consumer3.recorded_messages.size() == 1);

    // Both consumers got the downstream
    // update message from provider0
    CHECK(check_message_equal(consumer2.recorded_messages[0], msg));
    CHECK(check_message_equal(consumer3.recorded_messages[0], msg));
  });
}

TEST_CASE("Dispatch Upstream Update Message", "[context]")
{
  // root1
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<0>>, hana::type_c<entity::my_entity<1>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send upstream update to provider0.
    auto msg = consumer2.push_api.message_api().make_upstream_update_raw_message(
      Path(1, 2),
      Entity{2, 1}
    );
    consumer2.push_api.push(msg);

    // provider1 should not receive the message.
    CHECK(provider0.recorded_messages.size() == 1);
    CHECK(provider1.recorded_messages.size() == 0);
    CHECK(consumer2.recorded_messages.size() == 0);
    CHECK(consumer3.recorded_messages.size() == 0);

    // provider0 should record an upstream update message.
    CHECK(check_message_equal(provider0.recorded_messages[0], msg));
  });

  // root2
  hana::for_each(hana::make_tuple(
    hana::make_pair(hana::type_c<test_context::path<1>>, hana::type_c<entity::my_entity<1>>),
    hana::make_pair(hana::type_c<test_context::path<2>>, hana::type_c<entity::my_entity<2>>),
    hana::make_pair(hana::type_c<test_context::path<3>>, hana::type_c<entity::my_entity<3>>),
    hana::make_pair(hana::type_c<test_context::path<4>>, hana::type_c<entity::my_entity<4>>)
  ), [](auto types)
  {
    using Path = typename decltype(+hana::first(types))::type;
    using Entity = typename decltype(+hana::second(types))::type;
    init_record_messages();

    // Send upstream update to provider0.
    auto msg = consumer2.push_api.message_api().make_upstream_update_raw_message(
      Path(1, 2),
      Entity{2, 1}
    );
    consumer2.push_api.push(msg);

    // provider0 should not receive the message.
    CHECK(provider0.recorded_messages.size() == 0);
    CHECK(provider1.recorded_messages.size() == 1);
    CHECK(consumer2.recorded_messages.size() == 0);
    CHECK(consumer3.recorded_messages.size() == 0);

    // provider1 should record an upstream update message.
    CHECK(check_message_equal(provider1.recorded_messages[0], msg));
  });
}
