cmake_minimum_required(VERSION 3.14)

project(shiftTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

shift_add_test(
  core
  SOURCES
  source/core/Clock_test.cpp
  source/core/Component_test.cpp
  source/core/Object_test.cpp
  source/core/TimeConvert_test.cpp
  source/core/Timer_test.cpp
  source/core/UUID_test.cpp
  LINKS
  shift::core
)
shift_add_test(
  logger
  SOURCES
  source/logger/Log_test.cpp
  source/logger/LogTesting.cpp
  LINKS
  shift::logger
)

add_folders(Test)
