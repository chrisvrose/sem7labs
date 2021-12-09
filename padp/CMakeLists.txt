cmake_minimum_required(VERSION 3.0.0)
project(sem7padp_openmp VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)



# now add executables as we keep needing
add_executable(padp00 src/00/main.cpp)
add_executable(padp00_reductionism src/00/reductionism.cpp)
add_executable(padp20_matmul src/20/main.cpp)
add_executable(padp10_area src/10/area.cpp)
# this is the measurement version
add_executable(padp10_area_measure src/10/areameasure.cpp)


add_executable(padp_30_cfe src/30/cfe.cpp)
add_executable(padp_30_cnfe src/30/cnfe.cpp)
add_executable(padp_30_combined src/30/main.cpp)


add_executable(padp_60_ws src/60/main.cpp)


project(sem7padp_openmp_gd VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)
link_libraries(gd)


add_executable(padp_40_gray src/40/grayscale.cpp)


project(sem7padp_ocl_comp VERSION 0.1.0)

find_package(OpenMP REQUIRED)

link_libraries(OpenMP::OpenMP_CXX)

add_executable(padp_70_ocl_cmp_test src/70/test.cpp)


project(sem7padp_ocl VERSION 0.1.0)

find_package(OpenCL REQUIRED)
link_directories(${OpenCL_LIBRARY})

add_executable (padp_ocl src/70/ocl.cpp)
target_link_libraries (padp_ocl ${OpenCL_LIBRARY})
# target_include_directories(padp_ocl ${OpenCL_INCLUDE_DIRS})
