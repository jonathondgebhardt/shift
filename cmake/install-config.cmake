set(shift_FOUND YES)

include(CMakeFindDependencyMacro)
find_dependency(spdlog)
find_dependency(GeographicLib)

if(shift_FOUND)
  include("${CMAKE_CURRENT_LIST_DIR}/shiftTargets.cmake")
endif()
