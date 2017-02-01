#
# Copyright Jason Rice 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

add_executable("example.foo" EXCLUDE_FROM_ALL main.cpp)
target_link_libraries("example.foo"
  ${JsonCpp}
  ${CMAKE_THREAD_LIBS_INIT}
)

add_custom_target(run.example.foo
  COMMAND ./example.foo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Build and run: example.foo"
)
add_dependencies(run.example.foo example.foo)
include_directories("./include")
