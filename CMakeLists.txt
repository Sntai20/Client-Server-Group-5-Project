# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.16)

# Set the project name.
project ("Client-Server-Group-5-Project")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
IF (WIN32)
    link_libraries(ws2_32 wsock32)
ENDIF()

# Add source to this project's executable.
add_subdirectory ("Server-Project")
add_subdirectory ("Client-Project")
add_subdirectory ("Test-Project")

# Tests and install targets if needed.
include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)
