cmake_minimum_required(VERSION 3.23)
project(DA2324_Proj1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(DA2324_Proj1
        src/Data.cpp
        src/Data.h
        src/Graph.cpp
        src/Graph.h
        src/Menu.cpp
        src/Menu.h
        src/Node.cpp
        src/Node.h
        src/Edge.h
        src/Edge.cpp
        main.cpp
)
