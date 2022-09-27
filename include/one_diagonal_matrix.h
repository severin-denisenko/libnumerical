//
// Created by Severin on 21.09.2022.
//

#ifndef NUMERICAL_TASK_5_ONE_DIAGONAL_MATRIX_H
#define NUMERICAL_TASK_5_ONE_DIAGONAL_MATRIX_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "vector.h"

namespace numerical {

    class OneDiagonalMatrix {
    public:
        explicit OneDiagonalMatrix(int64_t size);
        ~OneDiagonalMatrix();

        // Returns elements of the matrix
        double& operator() (int64_t i);
        const double& operator () (int64_t i) const;

        void DebugOut();

        // Copy operator
        OneDiagonalMatrix& operator =(const OneDiagonalMatrix& other);
        Vector& operator *(const Vector& other);
    private:
        double *matrix;
        int64_t size;

        static double *_allocate_matrix(int64_t size);
    };

} // numerical

#endif //NUMERICAL_TASK_5_ONE_DIAGONAL_MATRIX_H
