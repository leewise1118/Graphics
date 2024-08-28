cmake_minimum_required(VERSION 3.2)
project(hello_mingw)
set(CMAKE_AR  C:/msys64/mingw64/bin/ar.exe)
set(CMAKE_C_COMPILER  C:/msys64/mingw64/bin/clang.exe)
set(CMAKE_CXX_COMPILER  C:/msys64/mingw64/bin/clang++.exe)

add_executable(main main.cpp)

# 编译complie_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
