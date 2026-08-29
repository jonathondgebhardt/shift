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
find_package(Boost REQUIRED CONFIG COMPONENTS serialization)

include(cmake/shift-project.cmake)
shift_add_library(logger
  SOURCES
  source/logger/Log.cpp
  LINKS
  spdlog::spdlog
)
shift_add_library(core
  SOURCES
  source/core/Clock.cpp
  source/core/Component.cpp
  source/core/Object.cpp
  source/core/UUID.cpp
  LINKS
)

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
