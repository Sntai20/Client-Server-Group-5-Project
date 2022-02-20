# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.22)

# Set the project name.
project ("Client-Server-Group-5-Project")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_subdirectory ("Server-Project")
add_subdirectory ("Client-Project")
add_subdirectory ("Test-Project")
add_subdirectory ("Thread-Project")