# CMakeList.txt : CMake project for Server-Project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Server-Project")

# Add source to this project's executable.
add_executable (server "server.cpp")

# TODO: Add tests and install targets if needed.
# GoogleTest requires at least C++11

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  basic_test
  "basic_test.cpp"
)
target_link_libraries(
  basic_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(basic_test)