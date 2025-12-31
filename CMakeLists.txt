cmake_minimum_required(VERSION 3.15)

project(logger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/core)
add_subdirectory(src/utils)

add_library(logger STATIC)
target_include_directories(logger PUBLIC
	"${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(logger PUBLIC core_obj utils_obj)

option(BUILD_TESTING "Build the testing suite" ON)

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()
add_library(Logger::logger ALIAS logger)
