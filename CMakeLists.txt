cmake_minimum_required(VERSION 3.10)
project(UDPProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(client udp_client_update.cpp)
target_link_libraries(client PRIVATE Threads::Threads)
