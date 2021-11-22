cmake_minimum_required(VERSION 3.0.0)
project(sem7padp VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)



# now add executables as we keep needing
add_executable(padp00 src/00/main.cpp)
add_executable(padp00_reductionism src/00/reductionism.cpp)
add_executable(padp20_matmul src/20/main.cpp)
add_executable(padp10_area src/10/area.cpp)
# this is the measurement version
add_executable(padp10_area_measure src/10/areameasure.cpp)


add_executable(padp_40_cfe src/40/cfe.cpp)
add_executable(padp_40_cnfe src/40/cnfe.cpp)

