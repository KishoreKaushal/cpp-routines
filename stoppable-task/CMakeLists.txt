cmake_minimum_required(VERSION 3.16)
project(stoppable_task)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SRC_FILES
    main.cpp
)

set(HDR_FILES
    stoppable_task.hpp
)

add_executable(stoppable_task ${SRC_FILES} ${HDR_FILES})

target_link_libraries(stoppable_task Threads::Threads)