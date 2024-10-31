cmake_minimum_required(VERSION 3.1...3.29)

project(SuperConductor)

add_subdirectory(src)
add_subdirectory(raylib)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SuperConductor)
