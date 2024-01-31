cmake_minimum_required(VERSION 3.6)

project(volga-vm)

add_executable(main code/main.cpp)

add_library(volga-vm SHARED code/machine/machine.cpp)
add_library(misc SHARED code/misc/qstring.cpp)

target_link_libraries(main volga-vm misc)