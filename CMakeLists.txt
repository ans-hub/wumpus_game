cmake_minimum_required (VERSION 3.1)

# Prepare applocation environment

project(wumpus_game)

set(bin_game wump_game) 
set(bin_test wump_test)
set(wump_VERSION_MAJOR 0)
set(wump_VERSION_MINOR 9)

# Add source files for game binary

file(GLOB_RECURSE ${bin_game}_headers "src/*.h")
file(GLOB_RECURSE ${bin_game}_sources "src/*.cc")
file(GLOB_RECURSE ${bin_test}_headers "test/*.h")
file(GLOB_RECURSE ${bin_test}_sources "src/*.cc")
file(GLOB_RECURSE ${bin_test}_befores "test/*.cc")
list(FILTER ${bin_test}_sources EXCLUDE REGEX ".*/main.cc$")

# Recursively add include dirs

set(INCLUDE_DIRS "")
foreach (HDR_FILE ${${bin_game}_headers})
    get_filename_component(DIR ${HDR_FILE} PATH)
    list (APPEND INCLUDE_DIRS ${DIR})
endforeach()
foreach (HDR_FILE ${${bin_test}_headers})
    get_filename_component(DIR ${HDR_FILE} PATH)
    list (APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

set(INCLUDE_DIRS "src")
include_directories(${INCLUDE_DIRS})

# Prepare compiler flags

if (!WIN32)
  set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -std=c++14")
  set(CMAKE_CXX_FLAGS_DEBUG
	 "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -DDEBUG -O0")
  set(CMAKE_CXX_FLAGS_RELEASE
	 "${CMAKE_CXX_FLAGS_RELEASE} -O2")
else()
	set (CMAKE_CXX_STANDARD 14)
endif()

# Choose build type

if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
  set(CMAKE_BUILD_TYPE "Release")
else()
  set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Building ${CMAKE_BUILD_TYPE}")
message("Build into ${CMAKE_BINARY_DIR}")

# Prepare FLTK library (we need to set FLTK_DIR variable"
#  either:  cmake ../ -DFLTK_DIR:PATH=~/projects/cpp/_libs/fltk-1.3/build/
#  or just: set(FLTK_DIR "~/projects/cpp/_libs/fltk-1.3/build/")

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})

# Prepare audio library

add_subdirectory(src/3rdparty/audio/)

# Install

add_executable(${bin_game} ${${bin_game}_sources})
add_executable(${bin_test} ${${bin_test}_sources} ${${bin_test}_befores})
target_include_directories(${bin_game} PUBLIC .)
target_include_directories(${bin_test} PUBLIC .)

# Linker`s work

target_link_libraries(${bin_game} fltk fltk_images fltk_png)
target_link_libraries(${bin_game} bass audio)
target_link_libraries(${bin_test} fltk fltk_images fltk_png)
target_link_libraries(${bin_test} bass audio)