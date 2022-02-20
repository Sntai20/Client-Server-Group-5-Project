# CMakeList.txt : CMake project for ClientProject, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.22)

# Set the project name.
project ("Thread-Project")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable (ThreadProject "main.cpp")