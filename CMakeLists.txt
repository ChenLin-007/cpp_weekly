cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpp_weekly)

# GoogleTest requires at least C++23
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# set(CMAKE_CXX_FLAGS "-stdlib=libc++ -lc++ -lc++abi -lgnustl_static -lsupc++")
enable_testing()

file(GLOB_RECURSE cpp_weekly_srcs *.cc)
add_executable(cpp_weekly
        conversion_function/conversion_function.cc
        class/class_test.cc
        formatting/formatting_test.cc
        functor/functor_test.cc
        io/io_test.cc
        pointer_like_classes/iterator_case_test.cc
        pointer_like_classes/shared_ptr_test.cc
        stl/valarray_test.cc
        strings/string_test.cc
        template/class_template_test.cc
        template/function_template_test.cc
        class/class_test.cc
        strings/string_view_test.cc
        future/future_test.cc
        template/chap_1_function_templates.cc
        template/ref_cref_test.cc
        template/chap4_variadic_templates.cc
        misc/optional_test.cc
        misc/typeinfo_test.cc
        template/using_template_test.cc
        template/partial_specialization_test.cc
        template/invoke_and_bind_back.cc
        )

include_directories(include)

target_link_libraries(
        cpp_weekly
        GTest::gtest_main
        fmt
        stdc++
)

include(GoogleTest)
gtest_discover_tests(cpp_weekly)