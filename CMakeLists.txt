project(mastermind)

cmake_minimum_required(VERSION 2.8)

#add definitions, compiler switches, etc.
add_definitions(-Wall -O2 -ggdb -Wall -march=native -I/usr/include)

#list all source files here
set(mastermind_sources Agent.cpp Controller.cpp Environment.cpp State.cpp)

add_library(MastermindCore ${mastermind_sources})

add_executable(mastermind main.cpp)
add_executable(testMastermind test.cpp)

find_package(Boost COMPONENTS thread REQUIRED)

target_link_libraries(mastermind MastermindCore ${Boost_THREAD_LIBRARY})
target_link_libraries(testMastermind MastermindCore ${Boost_THREAD_LIBRARY})
