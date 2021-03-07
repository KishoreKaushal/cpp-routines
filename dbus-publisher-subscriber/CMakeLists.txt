cmake_minimum_required(VERSION 3.16)
project(dbus-publisher-subscriber)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS "dbus-1")

set(SRC_FILES
    publisher.cpp
    subscriber.cpp
)

set(HDR_FILES
    common.hpp
    publisher.hpp
    subscriber.hpp
)

add_library(dbuspubsub ${SRC_FILES} ${HDR_FILES})

target_include_directories(dbuspubsub PUBLIC ${DBUS_INCLUDE_DIRS})

target_link_directories(dbuspubsub PUBLIC ${DBUS_LIBRARY_DIRS})

target_link_libraries(dbuspubsub ${DBUS_LIBRARIES})