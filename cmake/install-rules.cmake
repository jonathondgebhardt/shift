if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/shift-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
# should match the name of variable set in the install-config.cmake script
set(package shift)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT shift_Development
)

install(
    TARGETS shift_core
    EXPORT shiftTargets
    RUNTIME #
    COMPONENT shift_Runtime
    LIBRARY #
    COMPONENT shift_Runtime
    NAMELINK_COMPONENT shift_Development
    ARCHIVE #
    COMPONENT shift_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    shift_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE shift_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(shift_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${shift_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT shift_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${shift_INSTALL_CMAKEDIR}"
    COMPONENT shift_Development
)

install(
    EXPORT shiftTargets
    NAMESPACE shift::
    DESTINATION "${shift_INSTALL_CMAKEDIR}"
    COMPONENT shift_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
