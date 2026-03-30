
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

add_executable(bmssp src/main.cpp src/graph_generator.cpp src/benchmark/benchmark.cpp src/algorithms/dijkstra.cpp src/algorithms/bmssp.cpp)

# Optionally install the target
install(TARGETS bmssp RUNTIME DESTINATION bin)

# ==================== Unit Tests ====================
enable_testing()

set(TEST_SOURCES
	test/test_main.cpp
	test/test_graph.cpp
	test/test_dijkstra.cpp
	test/test_bmssp.cpp
	test/test_multi_source.cpp
)

add_executable(unit_tests ${TEST_SOURCES} src/algorithms/dijkstra.cpp src/algorithms/bmssp.cpp src/graph_generator.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2)

# Register tests with CTest
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(unit_tests)

