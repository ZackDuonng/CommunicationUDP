cmake_minimum_required(VERSION 3.10)
project(UDPProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_subdirectory(CommunicationUDP)
add_executable(udp_server main.cpp)

target_link_libraries(udp_server PRIVATE my_shared_lib Threads::Threads)
install(TARGETS udp_server DESTINATION bin)

# install(TARGETS my_shared_lib
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
#     RUNTIME DESTINATION bin
# )
