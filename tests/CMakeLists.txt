cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE  
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests test_main.cpp)
target_compile_features(unit_tests PRIVATE cxx_std_20)
target_link_libraries(unit_tests PRIVATE logger gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
