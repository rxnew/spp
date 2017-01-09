# http://qiita.com/janus_wel/items/4e6c12f9104f501104c7

cmake_minimum_required(VERSION 2.8)

# Google Test settings
include(ExternalProject)

ExternalProject_Add(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG release-1.8.0
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/projects/gtest
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )

ExternalProject_Get_Property(GoogleTest source_dir)
ExternalProject_Get_Property(GoogleTest binary_dir)

include_directories(
  ${source_dir}/googletest/include
  ${source_dir}/googlemock/include
  )

add_library(gtest STATIC IMPORTED)
add_library(gtest_main STATIC IMPORTED)

set_property(
  TARGET gtest
  PROPERTY IMPORTED_LOCATION ${binary_dir}/googlemock/gtest/libgtest.a
  )

set_property(
  TARGET gtest_main
  PROPERTY IMPORTED_LOCATION ${binary_dir}/googlemock/gtest/libgtest_main.a
  )
