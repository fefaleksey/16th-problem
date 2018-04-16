cmake_minimum_required(VERSION 3.5)
project(solver C)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(solver main.c include/Structures.h src/Structures.c src/Files.c include/Files.h src/Logic.c include/Logic.h src/SingularPoints.c include/SingularPoints.h)

target_link_libraries(solver m)
target_link_libraries(solver ${MPI_LIBRARIES})


target_compile_options(solver PRIVATE -Wall -Wextra -march=native -Wpedantic)