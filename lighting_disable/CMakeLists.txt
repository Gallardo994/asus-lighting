cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lighting_disable)
find_package(hidapi REQUIRED)

set(SRC_FILES main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lighting_controls)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC hidapi::hidapi)