project(mastermind)

cmake_minimum_required(VERSION 2.8)

#add definitions, compiler switches, etc.
add_definitions(-Wall -O3 -ffast-math -fomit-frame-pointer -march=native -I/usr/include)

#list all source files here
set(mastermind_sources Agent.cpp Controller.cpp Environment.cpp State.cpp)

add_executable(mastermind main.cpp ${mastermind_sources})
add_executable(testMastermind test.cpp ${mastermind_sources})

find_package(Boost COMPONENTS thread REQUIRED)

target_link_libraries(mastermind ${Boost_THREAD_LIBRARY})
target_link_libraries(testMastermind ${Boost_THREAD_LIBRARY})