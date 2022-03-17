cmake_minimum_required(VERSION 3.0.0)
project(sem7padp_openmp VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)

add_executable(10 src/10/main.cpp)


add_executable(20 src/20/main.cpp)


add_executable(30 src/30/main.cpp)
add_executable(30o src/30/old.cpp)

add_executable(60 src/60/main.cpp)


project(sem7padp_openmp_gd VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)
link_libraries(gd)


add_executable(40 src/40/grayscale.cpp)


project(sem7padp_ocl VERSION 0.1.0)

find_package(OpenCL REQUIRED)
link_directories(${OpenCL_LIBRARY})

add_executable (70 src/70/main.cpp)
target_link_libraries (70 ${OpenCL_LIBRARY})


