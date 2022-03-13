# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.16)

# Set the project name.
project ("Server-Project" CXX)

# CPP Only
enable_language(CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

# Add source to this project's executable.
add_executable (Server "main.cpp")
add_executable (WindowsServer "windowsserver.cpp")

# Add pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries("Server" PRIVATE Threads::Threads)
