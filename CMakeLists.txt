cmake_minimum_required(VERSION 3.28)
project(comp)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SRC test/*.cpp test/*.h)

set(MAIN_CPP main.cpp)

add_executable(comp
        ${MAIN_CPP}
        ${SOURCES}
        )
add_executable(test_comp
        ${TEST_SRC}
        ${SOURCES}
)

target_include_directories(comp PRIVATE
        src
        test
)

include_directories( ${PROJECT_SOURCE_DIR}/include)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(comp PRIVATE /W4 /permissive-)
    if(TREAT_WARNINGS_AS_ERRORS)
        target_compile_options(comp PRIVATE /WX)
    endif()
    target_compile_definitions(comp PRIVATE -D_CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(comp PRIVATE -Wall -pedantic -Wextra)
    target_compile_options(comp PRIVATE -Wno-sign-compare -Wno-self-move -Wno-redundant-move)
    target_compile_options(comp PRIVATE -Wold-style-cast)
    target_compile_options(comp PRIVATE -Wextra-semi)
    target_compile_options(comp PRIVATE -Woverloaded-virtual)
    target_compile_options(comp PRIVATE -Wzero-as-null-pointer-constant)
    if(TREAT_WARNINGS_AS_ERRORS)
        target_compile_options(comp PRIVATE -Werror -pedantic-errors)
    endif()
endif()

# Compiler specific warnings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(comp PRIVATE -Wshadow=compatible-local)
    target_compile_options(comp PRIVATE -Wduplicated-branches)
    target_compile_options(comp PRIVATE -Wduplicated-cond)
    # Disabled due to GCC bug
    # target_compile_options(comp PRIVATE -Wnull-dereference)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(comp PRIVATE -Wshadow-uncaptured-local)
    target_compile_options(comp PRIVATE -Wloop-analysis)
    target_compile_options(comp PRIVATE -Wno-self-assign-overloaded)
endif()

option(USE_SANITIZERS "Enable to build with undefined and address sanitizers" OFF)
if(USE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Enabling ASAN")
        target_compile_options(comp PUBLIC /fsanitize=address)
        target_compile_definitions(comp PUBLIC _DISABLE_STRING_ANNOTATION=1 _DISABLE_VECTOR_ANNOTATION=1)
    else()
        message(STATUS "Enabling USAN and ASAN")
        target_compile_options(comp PUBLIC -fsanitize=undefined,address)
        target_link_options(comp PUBLIC -fsanitize=undefined,address)

        target_compile_options(comp PUBLIC -fno-sanitize-recover=all -fno-optimize-sibling-calls -fno-omit-frame-pointer)
    endif()
endif()

target_link_libraries(test_comp GTest::gtest GTest::gtest_main)
gtest_discover_tests(test_comp)