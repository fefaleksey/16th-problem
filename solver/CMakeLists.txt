cmake_minimum_required(VERSION 3.9)
project(solver C)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_C_STANDARD 11)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_PREFIX} ${CMAKE_CURRENT_LIST_DIR}) #why?

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH} include)

add_executable( solver main.c
                include/Structures.h
                src/Structures.c
                src/Files.c
                include/Files.h
                src/Logic.c
                include/Logic.h
                src/SingularPoints.c
                include/SingularPoints.h
                include/CustomDataTypes.h)

target_link_libraries(solver m)
target_link_libraries(solver ${MPI_LIBRARIES})

target_compile_options(solver PRIVATE -Wall -Wextra -march=native -Wpedantic)

set_property(TARGET solver PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
