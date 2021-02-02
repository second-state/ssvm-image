# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.11)
project(SSVM-Image)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(BUILD_TOOLS "Generate ssvm and ssvmc tools." OFF)

find_package(Boost "1.68.0" REQUIRED)

# libjpeg and libpng path
set(JPEG_LIB
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libjpeg.a
)
set(PNG_LIB
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libpng16.a
)
set(JPEG_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/jpeg
)
set(PNG_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/png
)

# Clone ssvm-core
if(NOT SSVM_CORE_PATH)
  include(FetchContent)
  FetchContent_Declare(
    ssvm
    GIT_REPOSITORY https://github.com/second-state/SSVM.git
    GIT_TAG 0.7.3
  )

  FetchContent_GetProperties(ssvm)
  if (NOT ssvm_POPULATED)
    message(STATUS "Fetching ssvm repository")
    FetchContent_Populate(ssvm)
    message(STATUS "Fetching ssvm repository - done")
  endif ()
  add_subdirectory(${ssvm_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  set(SSVM_CORE_SRC_DIR ${ssvm_SOURCE_DIR})
else()
  get_filename_component(
    SSVM_CORE_PATH "${SSVM_CORE_PATH}"
    REALPATH
    BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  add_subdirectory(${SSVM_CORE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/utils/ssvm-core)
  set(SSVM_CORE_SRC_DIR ${SSVM_CORE_PATH})
endif()

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include/host
  ${CMAKE_CURRENT_SOURCE_DIR}/include/host
)
add_subdirectory(include)
add_subdirectory(lib)