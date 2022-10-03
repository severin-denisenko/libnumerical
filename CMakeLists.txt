cmake_minimum_required(VERSION 3.22)
project(libnumerical)

#set(CMAKE_CXX_COMPILER g++-11)
add_compile_options(-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wlogical-op -Wredundant-decls -Woverloaded-virtual -pedantic)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DDEBUG_BUILD=1)

add_library(libnumerical
        include/square_matrix.h src/square_matrix.cpp
        include/logger.h src/logger.cpp
        include/three_diagonal_matrix.h src/three_diagonal_matrix.cpp
        include/five_diagonal_matrix.h src/five_diagonal_matrix.cpp
        include/table.h src/table.cpp
        include/interpolator.h src/interpolator.cpp
        include/vector.h src/vector.cpp
        include/one_diagonal_matrix.h src/one_diagonal_matrix.cpp
        include/linear_solver.h src/linear_solver.cpp
        )
target_include_directories(libnumerical PRIVATE include)

# Tests

add_executable(test_three_diagonal_multiplication tests/three_diagonal_multiplication.cpp)
target_include_directories(test_three_diagonal_multiplication PRIVATE include)
target_link_libraries(test_three_diagonal_multiplication libnumerical)

add_executable(test_matrix_operations tests/matrix_operations.cpp)
target_include_directories(test_matrix_operations PRIVATE include)
target_link_libraries(test_matrix_operations libnumerical)

add_executable(test_table tests/table_test.cpp)
target_include_directories(test_table PRIVATE include)
target_link_libraries(test_table libnumerical)

add_executable(test_table_read tests/table_read_test.cpp)
target_include_directories(test_table_read PRIVATE include)
target_link_libraries(test_table_read libnumerical)
