cmake_minimum_required(VERSION 3.9)
project(solver C)

set(CMAKE_C_STANDARD 11)

add_executable(solver main.c include/Structures.h src/Structures.c src/Files.c include/Files.h src/Logic.c include/Logic.h src/SingularPoints.c include/SingularPoints.h)

#target_link_libraries(solver /usr/lib/libmpi.so)

find_package(MPI)
set (${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 2)
set (${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS)