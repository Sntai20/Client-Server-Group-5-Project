cmake_minimum_required(VERSION 3.21)
project(Client_Server_Group_5_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Server_Project server.cpp)
add_executable(Client_Project client.cpp)