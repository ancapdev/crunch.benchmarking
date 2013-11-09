# Copyright (c) 2011-2013, Christian Rorvik
# Distributed under the Simplified BSD License (See accompanying file LICENSE.txt)

vpm_depend_self()

vpm_add_library(crunch_benchmarking_lib
  include/crunch/benchmarking/api.hpp
  include/crunch/benchmarking/result_sink.hpp
  include/crunch/benchmarking/result_table.hpp
  include/crunch/benchmarking/result_table_descriptor.hpp
  include/crunch/benchmarking/statistical_profiler.hpp
  include/crunch/benchmarking/stopwatch.hpp
  include/crunch/benchmarking/stream_result_sink.hpp
  source/result_sink.cpp
  source/statistical_profiler.cpp
  source/stream_result_sink.cpp)

target_link_libraries(crunch_benchmarking_lib
  crunch_base_lib)
