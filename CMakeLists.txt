cmake_minimum_required(VERSION 3.20)
project(IndirectPrefetch LANGUAGES CXX)

set(LLVM_DIR /usr/lib/llvm-22/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVM ${LLVM_PACKAGE_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFS NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFS})

# LLVM is built without RTTI; the plugin must match.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

add_library(LoopCounter MODULE src/LoopCounter.cpp)