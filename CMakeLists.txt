cmake_minimum_required(VERSION 3.10)
project(expression_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
	expression_parser
	SHARED
	./src/expression_parser.cpp
	./src/tokenizer.cpp
	./src/parser.cpp
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

install(
	TARGETS expression_parser
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(
	DIRECTORY include/ DESTINATION include
)

