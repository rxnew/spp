cmake_minimum_required(VERSION 2.8)

add_executable(io-test
  input_test.cpp
  )

target_link_libraries(io-test
  gtest
  gtest_main
  pthread
  ${EXTERNAL_PROJECTS_LIBRARIES}
  )

add_test(
  NAME io
  COMMAND $<TARGET_FILE:io-test>
  )

# run with: ctest -L lib
set_property(
  TEST io
  PROPERTY LABELS lib io
  )
