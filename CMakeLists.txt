cmake_minimum_required (VERSION 3.8)
project ("Cpp17MyTest")

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -Wall -O2)

include_directories(Cpp17MyTest)
file(GLOB Cpp17MyTestSrc Cpp17MyTest/*.cpp)
add_library(Cpp17MyTest ${Cpp17MyTestSrc})

add_executable(Cpp17Main main.cpp)

target_link_libraries(Cpp17Main Cpp17MyTest)