function(shift_add_library LIB_NAME)
	set(multiValueArgs SOURCES INCLUDE_DIRS LINKS)
	cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	add_library(shift_${LIB_NAME} ${ARG_SOURCES})
	add_library(shift::${LIB_NAME} ALIAS shift_${LIB_NAME})

	include(GenerateExportHeader)
	generate_export_header(
		shift_${LIB_NAME}
		BASE_NAME shift_${LIB_NAME}
		EXPORT_FILE_NAME export/shift/${LIB_NAME}/shift_${LIB_NAME}_export.hpp
		CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
	)

	if(NOT BUILD_SHARED_LIBS)
		target_compile_definitions(shift_${LIB_NAME} PUBLIC shift_STATIC_DEFINE)
	endif()

	set_target_properties(
		shift_${LIB_NAME} PROPERTIES
		CXX_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN YES
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION_MAJOR}"
		EXPORT_NAME shift_${LIB_NAME}
		OUTPUT_NAME shift_${LIB_NAME}
	)

	target_include_directories(
		shift_${LIB_NAME} ${warning_guard}
		PUBLIC
		"\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
	)

	target_include_directories(
		shift_${LIB_NAME} SYSTEM
		PUBLIC
		"\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
	)

	target_compile_features(shift_${LIB_NAME} PUBLIC cxx_std_23)

	if(ARG_LINKS)
		target_link_libraries(shift_${LIB_NAME} PRIVATE ${ARG_LINKS})
	endif()
endfunction()

function(shift_add_test TEST_NAME)
	set(multiValueArgs SOURCES INCLUDE_DIRS LINKS)
	cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	add_executable(shift_${TEST_NAME}_test ${ARG_SOURCES})

	target_compile_features(shift_${TEST_NAME}_test PRIVATE cxx_std_23)

	target_link_libraries(
		shift_${TEST_NAME}_test PRIVATE
		shift::${ARG_LINKS}
		Catch2::Catch2WithMain
	)

	if(PROJECT_IS_TOP_LEVEL)
		foreach(item IN LISTS ARG_LINKS)
			find_package(${item} REQUIRED)
		endforeach()

		target_link_libraries(
			shift_${TEST_NAME}_test PRIVATE
			shift::${ARG_LINKS}
		)
	endif()

	catch_discover_tests(shift_${TEST_NAME}_test)
endfunction()

