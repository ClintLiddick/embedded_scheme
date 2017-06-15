ExternalProject_Add(
  chezscheme-external
  GIT_REPOSITORY https://github.com/cisco/chezscheme.git
  # GIT_TAG "0.7.3"
  UPDATE_DISCONNECTED 1
  CONFIGURE_COMMAND <SOURCE_DIR>/configure --installprefix=<INSTALL_DIR>
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  BUILD_IN_SOURCE ON
  BUILD_COMMAND make
  # TEST_BEFORE_INSTALL ON
  # TEST_COMMAND  test
  INSTALL_COMMAND make install
  LOG_DOWNLOAD ON
  LOG_BUILD ON
  # LOG_TEST ON
)

ExternalProject_Get_Property(chezscheme-external install_dir)
message(STATUS "Installing Chez to ${install_dir}")

add_executable(scheme IMPORTED)
add_dependencies(scheme chezscheme-external)
