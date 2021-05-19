cmake_minimum_required(VERSION 3.14)

project(CiglaGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(src PROJECT_SOURCES)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(include)
include_directories(${GLFW_INCLUDEDIR})

string(TOLOWER ${PROJECT_NAME} EXECUTABLE_NAME)
add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCES})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})