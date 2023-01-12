cmake_minimum_required(VERSION 3.20)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(Final_Task_CMake main.cpp ConverterJSON.cpp ${INCLUDE_DIR}/ConverterJSON.h InvertedIndex.cpp ${INCLUDE_DIR}/InvertedIndex.h SearchServer.cpp ${INCLUDE_DIR}/SearchServer.h)
target_include_directories(Final_Task_CMake PUBLIC ${INCLUDE_DIR})