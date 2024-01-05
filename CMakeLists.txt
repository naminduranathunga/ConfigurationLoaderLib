cmake_minimum_required(VERSION 3.6)

# build options
option(CONFIG_LIST_BUILD_EXAMPLES "Build examples" ON)
option(CONFIG_LIST_BUILD_SHARED "Build shared library" ON)

set (CMAKE_GENERATOR "MinGW Makefiles")

# output directories
set(CONFIG_LIST_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/output")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CONFIG_LIST_OUTPUT_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CONFIG_LIST_OUTPUT_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CONFIG_LIST_OUTPUT_DIR}/bin")

project(configuration-loader)

# Source files
file(GLOB SOURCE_FILES "src/*.cpp")

# include directories
include_directories("include")

if (CONFIG_LIST_BUILD_SHARED)
    add_library(configuration-loader SHARED ${SOURCE_FILES})
else()
    add_library(configuration-loader STATIC ${SOURCE_FILES})
endif()


if(CONFIG_LIST_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()