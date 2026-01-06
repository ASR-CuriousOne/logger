cmake_minimum_required(VERSION 3.15)

file(GLOB UTILS_SRCS "*.cpp")
add_library(utils_obj OBJECT ${UTILS_SRCS})
target_compile_features(utils_obj PRIVATE cxx_std_20)
target_include_directories(utils_obj PRIVATE
				"${PROJECT_SOURCE_DIR}/include"
)
