cmake_minimum_required(VERSION 3.20)
project(Final_Task_CMake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(nlohmann_json)

add_subdirectory(src)

target_link_libraries(Final_Task_CMake PRIVATE nlohmann_json::nlohmann_json)


project(Google_tests)
enable_testing()
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(${PROJECT_NAME}/lib)
add_executable(
        ${PROJECT_NAME}
        Google_tests/InverterIndexTest.cpp
        Google_tests/SearchServerTest.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(${PROJECT_NAME} gtest gtest_main)