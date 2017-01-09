cmake_minimum_required(VERSION 2.8)

add_executable(spp3-test
  spp3_test.cpp
  )

target_link_libraries(spp3-test
  gtest
  gtest_main
  pthread
  spp
  )

add_test(
  NAME spp3
  COMMAND $<TARGET_FILE:spp3-test>
  )

# run with: ctest -L lib
set_property(
  TEST spp3
  PROPERTY LABELS lib spp3
  )
