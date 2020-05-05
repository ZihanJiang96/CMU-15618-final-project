cmake_minimum_required ( VERSION 2.8 )

project ( CMU-15618-final-project )

# set to match your path
set(OptiX_INSTALL_DIR "/afs/andrew.cmu.edu/usr19/jinqingx/private/15618/CMU-15618-final-project/GPU-BVH-version/NVIDIA-OptiX-SDK-6.5.0-linux64"
    CACHE PATH "Path to OptiX installed location.")

# enable c++11
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	message(STATUS "c++11 enabled")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)
use_cxx11()

# CUDA package
find_package(CUDA)

# nvcc flags
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-O3 -arch compute_61)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Defines OptiX utilities and variables
INCLUDE(CMake/configure_optix.cmake)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

ADD_SUBDIRECTORY( OptiX/InOneWeekend )
ADD_SUBDIRECTORY( OptiX/RestOfLife )
