# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(smart_pointer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include_directories(smart_pointer/unique_pointer/)
# include_directories(smart_pointer/shared_pointer/)
include_directories(smart_pointer/weak_pointer/)

# Add an executable
# add_executable(unique_pointer smart_pointer/unique_pointer/unique_pointer.cpp)
# add_executable(shared_pointer smart_pointer/shared_pointer/shared_pointer.cpp)

add_executable(weak_pointer smart_pointer/weak_pointer/weak_pointer.cpp)

