cmake_minimum_required(VERSION 3.2)

project(scheme_koans C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_LIST_DIR}/cmake"
  /usr/share/cmake-3.0/Modules
)

include(External_GTest)
include_directories(${GTEST_INCLUDE_DIRS})

ExternalProject_Add(
  chibi-scheme-external
  GIT_REPOSITORY https://github.com/ashinn/chibi-scheme.git
  GIT_TAG "0.7.3"
  UPDATE_DISCONNECTED 1
  CONFIGURE_COMMAND ""
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  BUILD_IN_SOURCE ON
  BUILD_COMMAND make PREFIX=<INSTALL_DIR>
  TEST_BEFORE_INSTALL ON
  TEST_COMMAND make test
  INSTALL_COMMAND make install PREFIX=<INSTALL_DIR>
  LOG_DOWNLOAD ON
  LOG_BUILD ON
  LOG_TEST ON
)

ExternalProject_Get_Property(chibi-scheme-external install_dir)

add_library(chibi_scheme SHARED IMPORTED)
add_dependencies(chibi_scheme chibi-scheme-external)

set_target_properties(chibi_scheme PROPERTIES
  IMPORTED_LOCATION ${install_dir}/lib/libchibi-scheme.so
)

include_directories(${install_dir}/include)

add_executable(main main.cpp)
target_link_libraries(main chibi_scheme)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(run_koans run_koans.cpp)
target_link_libraries(run_koans
  chibi_scheme
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
)
