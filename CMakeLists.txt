cmake_minimum_required(VERSION 3.14)
project(SmartCarExecutor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === 主程序：Executor ===
add_executable(Executor
    src/Executor.cpp
    src/main.cpp          # 必须是 main.cpp，不是 main.demo.cpp
)

target_include_directories(Executor PRIVATE src)  # 必须是 Executor，不是 demo

# === GoogleTest 自动下载 ===
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true   # <<<<< 就是在这里添加这一行
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === 启用测试 ===
enable_testing()

# === 测试程序：test_executor ===
add_executable(test_executor
    src/Executor.cpp
    test/test_executor.cpp   # 必须有这个文件
)

target_include_directories(test_executor PRIVATE src)
target_link_libraries(test_executor GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_executor)
