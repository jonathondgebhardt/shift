set(shift_FOUND YES)

include(CMakeFindDependencyMacro)
find_dependency(fmt)

if(shift_FOUND)
  include("${CMAKE_CURRENT_LIST_DIR}/shiftTargets.cmake")
endif()
