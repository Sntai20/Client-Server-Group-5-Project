# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Client-Server-Group-5-Project")

# Add source to this project's executable.
add_subdirectory ("Server-Project")
add_subdirectory ("Client-Project")
add_subdirectory ("Test-Project")