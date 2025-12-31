cmake_minimum_required(VERSION 3.15)

file(GLOB CORE_SRCS "*.cpp")
add_library(core_obj OBJECT ${CORE_SRCS})
target_include_directories(core_obj PRIVATE
				"${PROJECT_SOURCE_DIR}/include"
)
