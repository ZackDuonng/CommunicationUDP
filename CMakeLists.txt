# Chi dinh phien ban CMake toi thieu
cmake_minimum_required(VERSION 3.10)

# Dat ten cho du an va chi dinh ngon ngu la C++
project(UDPServer LANGUAGES CXX)

# Yeu cau su dung tieu chuan C++11 hoac moi hon
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Tim goi thu vien
find_package(Threads REQUIRED)

#Tao file thuc thi tu tat ca cac file .cpp can thiet
add_executable(server_app main.cpp src/UDPServer.cpp)

target_include_directories(server_app PRIVATE ${PROJECT_SOURCE_DIR}/include)

#Lien ket file thuc thi voi thu vien pthread cua he thong
target_link_libraries(server_app PRIVATE Threads::Threads)
