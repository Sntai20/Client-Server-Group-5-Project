# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.22)

# Set the project name.
project ("Server-Project" CXX)

# CPP Only
enable_language(CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add pthread
set(CMAKE_CXX_FLAGS_INIT "-pthread")

# Add source to this project's executable.
add_executable (Server "main.cpp")