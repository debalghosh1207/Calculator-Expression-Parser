cmake_minimum_required(VERSION 3.10)
project(expression_parser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
	expression_parser
	SHARED
	./src/expression_parser.cpp
	./src/tokenizer.cpp
	./src/parser.cpp
)

# Set library version and soversion
set_target_properties(expression_parser PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)

set(
	HEADER_DIRECTORIES
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_include_directories(
	expression_parser
	PUBLIC
	${HEADER_DIRECTORIES}
)

# Internal headers (in src) are automatically visible to these sources; no need to install them.

# Install the library
install(
	TARGETS expression_parser
	EXPORT expression_parser-targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

# Install headers
install(
	DIRECTORY include/ 
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp"
	PATTERN "*.h"
)

# Install export targets for find_package support
install(
	EXPORT expression_parser-targets
	FILE expression_parser-targets.cmake
	DESTINATION lib/cmake/expression_parser
)

# Configure and install the config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
	cmake/expression_parser-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/expression_parser-config.cmake"
	INSTALL_DESTINATION lib/cmake/expression_parser
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/expression_parser-config-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/expression_parser-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/expression_parser-config-version.cmake"
	DESTINATION lib/cmake/expression_parser
)

