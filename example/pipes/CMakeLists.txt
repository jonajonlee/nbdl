#
# Copyright Jason Rice 2016
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#

if (NOT JsonCpp)
  message(WARNING "Skipping example.pipes")
  return()
endif()

add_executable("example.pipes" EXCLUDE_FROM_ALL main.cpp)
target_link_libraries("example.pipes"
  ${JsonCpp}
  ${CMAKE_THREAD_LIBS_INIT}
)

add_custom_target(run.example.pipes
  COMMAND ./example.pipes
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Build and run: example.pipes"
)
add_dependencies(run.example.pipes example.pipes)
