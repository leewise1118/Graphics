cmake_minimum_required(VERSION 3.2)
project(hello_mingw)
set(CMAKE_AR  C:/msys64/mingw64/bin/ar.exe)
set(CMAKE_C_COMPILER  C:/msys64/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER  C:/msys64/mingw64/bin/g++.exe)

add_executable(main main.cpp)
