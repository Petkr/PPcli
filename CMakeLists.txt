cmake_minimum_required (VERSION 3.21)

if(CMAKE_COMPILER_IS_GNUCXX)
add_compile_options(
	-Wall
	-Wextra
	-pedantic
	-Werror
)
endif()

project(PPcli)

add_subdirectory(PPcli)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/PPclidemo/")
add_subdirectory(PPclidemo)
endif()
