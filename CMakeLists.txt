cmake_minimum_required(VERSION 3.10)
project(CodeIntegration_Ch4)

set(CMAKE_CXX_STANDARD 14)

include_directories(header)
include_directories(header/dzn)

file(GLOB src_folder
        "src/*.cc" )

add_executable(CodeIntegration_Ch4 ${src_folder} src/main.cpp)

target_link_libraries(CodeIntegration_Ch4 pthread)
