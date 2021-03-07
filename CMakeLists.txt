cmake_minimum_required(VERSION 3.16)
project(cpp-routines)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./dbus-publisher-subscriber)
add_subdirectory(./stoppable-task)