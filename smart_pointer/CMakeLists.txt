# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(unique_pointer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable
add_executable(unique_pointer unique_pointer.cpp)

# Link against libraries (if any)
# target_link_libraries(MyExecutable PRIVATE SomeLibrary)
