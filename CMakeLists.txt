cmake_minimum_required(VERSION 3.25)
project(DinArray)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include/)

if (MSVC)
    # Compile commands for Windows
    message("Using compilation flags for non MSVC")
else()
    # Compile commands for Linux
    message("Using compilation flags for non MSVC compilers")
    add_compile_options(-Wall -Wpedantic -Wextra -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()


add_executable(ctorTest1 src/test_constructors1.cc)
add_executable(ctorTest2 src/test_constructors2.cc)

add_executable(assignmentOp src/copy_assigment.cc)

add_executable(accessors1 src/accessors1.cc)

add_executable(pushingElems1 src/pushing_elements1.cc)
add_executable(pushingElems2 src/pushing_elements2.cc)

add_executable(demo src/demo.cc)
# MSVC already defines _DEBUG on Debug builds
target_compile_definitions(demo PRIVATE _DEBUG)

add_executable(testVector src/main.cc)
