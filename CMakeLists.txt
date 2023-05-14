cmake_minimum_required(VERSION 3.25)
project(DinArray)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include/)

if (MSVC)
    # Compile commands for Windows
else()
    # Compile commands for Linux
    add_compile_options(-Wall -Wpedantic -Wextra -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()


add_executable(ctorTest1 src/test_constructors1.cc)
add_executable(ctorTest2 src/test_constructors2.cc)
