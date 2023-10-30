#PLEASE, DO NOT CHANGE THIS FILE
cmake_minimum_required(VERSION 3.5)
project(P2 C)
set(CMAKE_C_STANDARD 99)

include(config.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)
add_definitions(-DINPUT_FILE="${input}")
set(dependencies_video_list types.h video_list.h video_list.c)
set(dependencies ${dependencies_video_list} user_list.h user_list.c)
add_executable(test_video_list test/test_video_list.c ${dependencies_video_list})
add_executable(test_user_list test/test_user_list.c ${dependencies})
add_executable(main main.c ${dependencies})
target_compile_options(main PRIVATE -Wall -Wextra)
target_compile_options(test_video_list PRIVATE -Wall -Wextra)
target_compile_options(test_user_list PRIVATE -Wall -Wextra)
set_target_properties(main test_video_list test_user_list PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)
