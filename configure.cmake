# Copyright (c) 2011-2013, Christian Rorvik
# Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

vpm_set_default_variant(boost proxy)
vpm_set_default_version(boost 1.53.0)

vpm_set_default_versions(
  crunch.base master
  crunch.test master)

vpm_depend(
  boost
  crunch.base
  crunch.test)

vpm_include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

macro(crunch_add_benchmark _name)
  crunch_add_test_executable(${_name} ${ARGN})
  target_link_libraries(${_name} crunch_benchmarking_lib)

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
