cmake_minimum_required(VERSION 3.21)
project(MazeGame)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(MazeGame main.cpp)
#add_executable(MazeGame ${SOURCE_FILES})
include_directories(/usr/local/lib)
include_directories(/usr/local/include)

# Find SFML installed by Homebrew or another method
find_package(SFML 2.5.1 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MazeGame sfml-graphics sfml-window sfml-system)
endif()


