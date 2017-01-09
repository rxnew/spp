cmake_minimum_required(VERSION 3.2)

project(spp CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(TARGETS spp3)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAIN_SOURCE_DIR ${SOURCE_DIR}/main)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/external_projects.cmake)

include_directories(${SOURCE_DIR})
include_directories(${EXTERNAL_PROJECTS_INCLUDE_PATHS})

foreach(TARGET ${TARGETS})
  add_executable(${TARGET} ${MAIN_SOURCE_DIR}/${TARGET}.cpp)
  target_link_libraries(${TARGET} PUBLIC ${EXTERNAL_PROJECTS_LIBRARIES})
  if(BUILD_EXTERNAL_PROJECT_NAMES)
    add_dependencies(${TARGET} ${BUILD_EXTERNAL_PROJECT_NAMES})
  endif()
endforeach(TARGET)

install(DIRECTORY ${SOURCE_DIR}/
        DESTINATION include/${TARGET}
        FILES_MATCHING PATTERN *.hpp)

option(SPP_BUILD_TESTS "Build unit tests" off)

if(SPP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(${TEST_DIR})
endif()

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2")

add_definitions(${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")
