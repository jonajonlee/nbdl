#
# Copyright Jason Rice 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

include_directories(${nbdl_project_SOURCE_DIR}/src)
nbdl_catch_test_suite(build_targets test.nbdl.websocket
  generate_handshake_response.cpp
  messages.cpp
  parse_handshake_request.cpp
)

foreach(_target IN LISTS build_targets)
  target_link_libraries(${_target} nbdl_servers_ws)
endforeach()
