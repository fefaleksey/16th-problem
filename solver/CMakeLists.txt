cmake_minimum_required(VERSION 3.9)
project(solver C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
set(MPI_COMPILE_FLAGS -lm ${MPI_COMPILE_FLAGS})

add_executable(solver main.c include/Structures.h src/Structures.c src/Files.c include/Files.h src/Logic.c include/Logic.h src/SingularPoints.c include/SingularPoints.h)

target_link_libraries(solver m)
target_link_libraries(solver ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(solver PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(solver PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

set (both MPI_C_LIBRARIES)
set(MPI_C_INCLUDE_PATH)

set (${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 3)
set (${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS)
