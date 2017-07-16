cmake_minimum_required (VERSION 2.6)
project (grotto)

file(GLOB SOURCES "src/*.cpp")
add_executable(grotto ${SOURCES})

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(grotto ${GLFW_STATIC_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(grotto ${OPENGL_gl_LIBRARY})
