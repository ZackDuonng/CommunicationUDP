# Chi dinh phien ban CMake toi thieu
cmake_minimum_required(VERSION 3.10)

# Dat ten cho du an va chi dinh ngon ngu la C++
project(UDPServer LANGUAGES CXX)

# Yeu cau su dung tieu chuan C++11 hoac moi hon
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Tim goi thu vien
find_package(Threads REQUIRED)

#Tao file thuc thi tu file nguon
add_executable(udp_server udp_server_update.cpp)

#Lien ket file thuc thi voi thu vien pthread cua he thong
target_link_libraries(udp_server PRIVATE Threads::Threads)

