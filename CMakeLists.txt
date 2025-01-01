cmake_minimum_required(VERSION 3.10)

project(DoublePendulum)

set(CMAKE_CXX_STANDARD 17)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(doublePendulum src/Main.cpp)

target_link_libraries(doublePendulum sfml-graphics sfml-window sfml-system)
