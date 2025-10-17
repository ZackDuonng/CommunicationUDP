# 1. Chi dinh phien ban CMake toi thieu
cmake_minimum_required(VERSION 3.12)

# 2. Dat ten du an va ngon ngu (C va C++)
project(MyProject LANGUAGES C CXX)

# 3. Yeu cau su dung tieu chuan C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Tim goi thu vien luong
find_package(Threads REQUIRED)


# 5. Tu dong tim tat ca cac file nguon (.c, .cpp) trong thu muc `src`
file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")

set(MAIN_SRC        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# 6. Tao mot THU VIEN ten la "my_shared_lib" tu cac file nguon da tim thay
add_library(my_shared_lib SHARED ${LIB_SOURCES})

# 7. Cung cap duong dan "include" cho thu vien
# PUBLIC: Bat ky chuong trinh nao dung thu vien nay se tu dong biet duong dan nay
target_include_directories(my_shared_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)



# 8. Tao mot FILE THUC THI ten la "server_app" chi tu file main.cpp
add_executable(server_app ${MAIN_SRC})


# 9. Lien ket file thuc thi "server_app" voi thu vien "my_shared_lib"
# Day la buoc quan trong nhat!
target_link_libraries(server_app PRIVATE my_shared_lib Threads::Threads)



# 10. Tao quy tac de cai dat thu vien (neu can)
# install(TARGETS my_shared_lib DESTINATION /usr/local/lib)