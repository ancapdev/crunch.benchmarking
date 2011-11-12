# Copyright (c) 2011, Christian Rorvik
# Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

vpm_depend(
  boost
  crunch_base)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

macro(crunch_add_benchmark _name)
  add_custom_target("run-${_name}"
    ${_name}
    WORKING_DIRECTORY ${CMAKE_CURRENTY_BINARY_DIR}
    VERBATIM)
endmacro()
