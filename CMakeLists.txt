cmake_minimum_required(VERSION 3.2)

project(scheme_koans C)

include(ExternalProject)

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
set_target_properties(chibi_scheme PROPERTIES
  IMPORTED_LOCATION ${install_dir}/lib/libchibi-scheme.so
  INTERFACE_INCLUDE_DIRECTORIES ${install_dir}/include
)
add_dependencies(chibi_scheme chibi-scheme-external)

add_executable(main main.c)
target_link_libraries(main chibi_scheme)
