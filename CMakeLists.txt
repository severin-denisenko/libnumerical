cmake_minimum_required(VERSION 3.22)
project(libnumerical)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DDEBUG_BUILD=1)

add_library(libnumerical src/square_matrix.cpp include/sqare_matrix.h include/logger.h src/logger.cpp include/three_diagonal_matrix.h src/three_diagonal_matrix.cpp include/five_diagonal_matrix.h src/five_diagonal_matrix.cpp)
target_include_directories(libnumerical PRIVATE include)

# Tests

add_executable(test_three_diagonal_multiplication tests/three_diagonal_multiplication.cpp)
target_include_directories(test_three_diagonal_multiplication PRIVATE include)
target_link_libraries(test_three_diagonal_multiplication libnumerical)

add_executable(test_matrix_operations tests/matrix_operations.cpp)
target_include_directories(test_matrix_operations PRIVATE include)
target_link_libraries(test_matrix_operations libnumerical)

add_executable(test_interpolation tests/interpolation.cpp)
target_include_directories(test_interpolation PRIVATE include)
target_link_libraries(test_interpolation libnumerical)


