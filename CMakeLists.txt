cmake_minimum_required(VERSION 3.20)
project(minitorch CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

# --- library target -------------------------------------------------------
# Empty for now. Once you add src/storage.cpp etc, list them here and this
# becomes a real static library that examples/tests link against.
file(GLOB_RECURSE MINITORCH_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
if(MINITORCH_SOURCES)
  add_library(minitorch_core STATIC ${MINITORCH_SOURCES})
  target_include_directories(minitorch_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
endif()

# --- sandbox executable ----------------------------------------------------
# Your scratch space for manually exercising whatever you just wrote.
if(EXISTS ${CMAKE_SOURCE_DIR}/examples/sandbox.cpp)
  add_executable(sandbox examples/sandbox.cpp)
  if(TARGET minitorch_core)
    target_link_libraries(sandbox PRIVATE minitorch_core)
  endif()
endif()

# --- tests ------------------------------------------------------------------
# Each tests/*.cpp becomes its own executable + a registered CTest case.
# A test should assert()-fail loudly, not print-and-eyeball.
enable_testing()
file(GLOB MINITORCH_TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
foreach(test_src ${MINITORCH_TEST_SOURCES})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  if(TARGET minitorch_core)
    target_link_libraries(${test_name} PRIVATE minitorch_core)
  endif()
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
