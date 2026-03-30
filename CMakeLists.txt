
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

# Find dependencies
include(FetchContent)

# Catch2 for unit testing
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Google Benchmark
FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.8.3
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

add_executable(bmssp src/main.cpp)

# Optionally install the target
install(TARGETS bmssp RUNTIME DESTINATION bin)

