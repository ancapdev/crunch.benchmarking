# Copyright (c) 2011, Christian Rorvik
# Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

vpm_set_default_versions(
  boost proxy
  crunch.base trunk)

vpm_depend(
  boost
  crunch.base)

vpm_include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

macro(crunch_add_benchmark _name)
  # Shared build target for all benchmarks
  if(NOT TARGET build-benchmarks)
    add_custom_target(build-benchmarks)
  endif()

  # Shared run target for all benchmarks
  if(NOT TARGET run-benchmarks)
    add_custom_target(run-benchmarks)
  endif()

  # Run target for this benchmark
  add_custom_target("run-${_name}"
    ${_name}
    WORKING_DIRECTORY ${CMAKE_CURRENTY_BINARY_DIR}
    VERBATIM)

  # Exclude benchmark run from default build in Visual Studio
  set_target_properties("run-${_name}" PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)

  # Add dependencies on shared build and run targets
  add_dependencies(build-benchmarks ${_name})
  add_dependencies(run-benchmarks "run-${_name}")
endmacro()
