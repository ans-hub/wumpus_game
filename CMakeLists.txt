cmake_minimum_required (VERSION 2.8.11)

# Prepare applocation environment

project(wumpus_game)

set(bin_game wump_game) 
set(bin_test wump_test)
set(wump_VERSION_MAJOR 0)
set(wump_VERSION_MINOR 9)

# Prepare compiler flags

set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG
   "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -DDEBUG -O0")
set(CMAKE_CXX_FLAGS_RELEASE
   "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Choose build type

if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
  set(CMAKE_BUILD_TYPE "Release")
else()
  set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Building ${CMAKE_BUILD_TYPE}")

# Add source files for game binary

file(GLOB_RECURSE ${bin_game}_headers "src/*.h")
file(GLOB_RECURSE ${bin_game}_sources "src/*.cc")
file(GLOB_RECURSE ${bin_test}_headers "test/*.h")
file(GLOB_RECURSE ${bin_test}_sources "src/*.cc")
file(GLOB_RECURSE ${bin_test}_befores "test/*.cc")

# Exclude another one main from auto added

list(FILTER ${bin_test}_sources EXCLUDE REGEX ".*/main.cc$")

# Recursively add include dirs

set (INCLUDE_DIRS "")
foreach (HDR_FILE ${${bin_game}_headers})
    get_filename_component(DIR ${HDR_FILE} PATH)
    list (APPEND INCLUDE_DIRS ${DIR})
endforeach()
foreach (HDR_FILE ${${bin_test}_headers})
    get_filename_component(DIR ${HDR_FILE} PATH)
    list (APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Install

add_executable(${bin_game} ${${bin_game}_sources})
add_executable(${bin_test} ${${bin_test}_sources} ${${bin_test}_befores})
target_include_directories(${bin_game} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${bin_test} PUBLIC ${INCLUDE_DIRS})

# Link 3rdparty lib

add_subdirectory(src/3rdparty/audio/)

set(FLTK_DIR "~/projects/cpp/_libs/fltk-1.3/build")
find_package(FLTK REQUIRED NO_MODULE) # see note #1 below code
find_package(OpenGL REQUIRED)
# find lib bass and bass_fx
include_directories(${FLTK_INCLUDE_DIRS}) 


message(STATUS "FLTK_INCLUDE_DIRS = '${FLTK_INCLUDE_DIRS}'") 
message(STATUS "FLTK_LIBRARIES = '${FLTK_LIBRARIES}'") 
message(STATUS "FLTK_FLUID_EXECUTABLE = '${FLTK_FLUID_EXECUTABLE}'") 

link_directories(${FLTK_LIBRARY_DIRS}) 
add_definitions(${FLTK_DEFINITIONS}) 

# target_link_libraries(${app_name} ${FLTK_LIBRARIES})

target_link_libraries(${bin_game} fltk fltk_images fltk_png)
target_link_libraries(${bin_game} ${OPENGL_LIBRARIES})
target_link_libraries(${bin_game} audio bass bass_fx)

target_link_libraries(${bin_test} fltk fltk_images fltk_png)
target_link_libraries(${bin_test} ${OPENGL_LIBRARIES})
target_link_libraries(${bin_test} audio bass bass_fx)

# Note 1:
# ${FLTK_LIBRARIES} - will work only if we use FLTK with module
# otherwise if we use cmake - we need to use current rule. And FLTKCmake
# is appears only if fltk was built by CMake