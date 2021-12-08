cmake_minimum_required(VERSION 3.0.0)

project(padp_cg VERSION 0.1.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
link_libraries( ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

add_executable(p01 src/01/main.cpp)
add_executable(p02 src/02/main.cpp)
add_executable(p04 src/04/main.cpp)
add_executable(p06 src/06/main.cpp)