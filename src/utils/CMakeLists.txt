cmake_minimum_required(VERSION 3.15)

file(GLOB UTILS_SRCS "*.cpp")
add_library(utils_obj OBJECT ${UTILS_SRCS})
target_include_directories(utils_obj PRIVATE
				"${CMAKE_SOURCE_DIR}/include"
)
