
cmake_minimum_required(VERSION 3.15)
project(breaking_the_sorting_barrier CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(bmssp src/main.cpp)

# Optionally install the target
install(TARGETS bmssp RUNTIME DESTINATION bin)

