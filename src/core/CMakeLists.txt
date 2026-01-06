cmake_minimum_required(VERSION 3.15)

file(GLOB CORE_SRCS "*.cpp")
add_library(core_obj OBJECT ${CORE_SRCS})
target_compile_features(core_obj PUBLIC cxx_std_20)
target_include_directories(core_obj PRIVATE
				"${PROJECT_SOURCE_DIR}/include"
)
