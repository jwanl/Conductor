project(SuperConductor)

add_executable(${PROJECT_NAME} main.cpp)

# Set C++17 as standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} raylib)