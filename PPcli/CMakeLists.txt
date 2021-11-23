cmake_minimum_required (VERSION 3.21)

add_library(PPcli INTERFACE
#"main.cpp"
)
target_compile_features(PPcli INTERFACE cxx_std_20)
target_include_directories(PPcli INTERFACE "${CMAKE_SOURCE_DIR}/PP")

if(CMAKE_COMPILER_IS_GNUCXX)
set_target_properties(PPcli PROPERTIES COMPILE_FLAGS "-ftemplate-backtrace-limit=0 -fconcepts-diagnostics-depth=5")
endif()

#install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" DESTINATION "PPcli/include" FILES_MATCHING PATTERN "*.hpp")
