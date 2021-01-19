cmake_minimum_required(VERSION 2.8)

project(DDA-2020)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCES src/DDA-2020.cpp src/Error.cpp src/FST.cpp src/Generation.cpp src/GRB.cpp src/In.cpp src/IT.cpp src/Log.cpp src/LT.cpp src/MFST.cpp src/Parm.cpp src/Semantic.cpp)
set(HEADERS src/Error.h src/FST.h src/Generation.h src/GRB.h src/In.h src/IT.h src/Log.h src/LT.h src/MFST.h src/Parm.h src/Semantic.h)

add_executable(DDA-2020 ${SOURCES} ${HEADERS})