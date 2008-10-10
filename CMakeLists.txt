project(mastermind)

cmake_minimum_required(VERSION 2.8)

#add definitions, compiler switches, etc.
add_definitions(-Wall -O3 -ffast-math -fomit-frame-pointer -march=native -I/usr/include)

#list all source files here
add_executable(mastermind main.cpp Agent.cpp Environment.cpp State.cpp)

target_link_libraries(mastermind pthread)
