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
  source/core/Component_test.cpp
  source/core/Entity_test.cpp
  source/core/OptionalEntityReference_test.cpp
  source/core/SimulationRunner_test.cpp
  source/core/Systems_test.cpp
  source/core/UUID_test.cpp
  source/core/UpdateScheduler_test.cpp
  source/core/World_test.cpp
  LINKS
  shift_core
)
shift_add_test(
  time
  SOURCES
  source/time/RealTimeUpdater_test.cpp
  source/time/FixedTimeUpdater_test.cpp
  source/time/SimulationTime_test.cpp
  source/time/Timer_test.cpp
  LINKS
  shift_time
)
shift_add_test(
  logger
  SOURCES
  source/logger/Log_test.cpp
  source/logger/LogTesting.cpp
  LINKS
  shift_logger
)
shift_add_test(
  telemetry
  SOURCES
  source/telemetry/MemoryTelemetryRecorder_test.cpp
  source/telemetry/TelemetryValue_test.cpp
  LINKS
  shift_core
)
shift_add_test(
  math
  SOURCES
  source/math/Utilities_test.cpp
  source/math/Vec3_test.cpp
  LINKS
  shift_math
)
shift_add_test(
  coordinate
  SOURCES
  source/coordinate/CoordinateTransform_test.cpp
  source/coordinate/EcefVector_test.cpp
  LINKS
  shift_coordinate
)

add_folders(Test)
