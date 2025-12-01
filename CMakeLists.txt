cmake_minimum_required(VERSION 3.14)
project(SmartCarExecutor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 主程序
add_executable(Executor
    src/Executor.cpp
    src/main.cpp
)
target_include_directories(Executor PRIVATE src)

# GoogleTest 自动下载
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# 单元测试
add_executable(test_executor
    src/Executor.cpp
    test/test_executor.cpp
)
target_include_directories(test_executor PRIVATE src)
target_link_libraries(test_executor GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_executor)

