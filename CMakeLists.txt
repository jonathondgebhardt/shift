cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  shift
  VERSION 0.1.0
  DESCRIPTION "Simulation Host for Independent Frame Timing"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

find_package(spdlog CONFIG REQUIRED)
find_package(GeographicLib CONFIG REQUIRED)

include(cmake/shift-project.cmake)
shift_add_library(
  logger
  SOURCES
  source/logger/Log.cpp
  source/logger/LogBackend.cpp
  LINKS
  spdlog::spdlog
)
shift_add_library(
  math
  SOURCES
  source/math/Vec3.cpp
)
shift_add_library(
  time
  SOURCES
  source/time/Clock.cpp
  source/time/RealTimeUpdater.cpp
)
shift_add_library(
  core
  SOURCES
  source/core/Component.cpp
  source/core/Entity.cpp
  source/core/OptionalEntityReference.cpp
  source/core/SimulationRunner.cpp
  source/core/Systems.cpp
  source/core/UUID.cpp
  source/core/UpdateScheduler.cpp
  source/core/World.cpp
  # todo: should these be in their own library?
  source/telemetry/ConsoleTelemetryRecorder.cpp
  source/telemetry/MemoryTelemetryRecorder.cpp
  LINKS
  shift_logger
  shift_math
  shift_time
)

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${shift_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT shift_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of shift"
  )
endif()

include(cmake/dev-mode.cmake)
