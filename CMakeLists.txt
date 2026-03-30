cmake_minimum_required(VERSION 3.10)
project(bmssp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bmssp src/main.cpp)

# Optionally install the target
install(TARGETS bmssp RUNTIME DESTINATION bin)

