cmake_minimum_required(VERSION 3.6)

project(configuration-loader-examples)

message(STATUS "Configuring ${PROJECT_NAME}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} configuration-loader)
endforeach(EXAMPLE)


