# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(UnifiedBFS)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable OpenMP
find_package(OpenMP REQUIRED)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main.cpp
    src/graph.cpp
    src/bfs.cpp
    src/performance.cpp
)

# Add the executable
add_executable(unified_bfs ${SOURCES})

# Link OpenMP
target_link_libraries(unified_bfs PRIVATE OpenMP::OpenMP_CXX)