cmake_minimum_required(VERSION 3.2)
project(OpenGL_demo)

set(CMAKE_AR  C:/msys64/mingw64/bin/ar.exe)
set(CMAKE_C_COMPILER  C:/msys64/mingw64/bin/clang.exe)
set(CMAKE_CXX_COMPILER  C:/msys64/mingw64/bin/clang++.exe)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# 设置生成compile_commands.json文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 将文件夹inc和src下的所有文件添加到可执行文件
file(GLOB_RECURSE HEADER_FILES "inc/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# 将inc文件夹下的头文件添加到项目中
include_directories(inc)

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED)

# 生成可执行文件
add_executable(OpenGL_demo main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(OpenGL_demo OpenGL::GL)
target_link_libraries(OpenGL_demo Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL )