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
        explicit OneDiagonalMatrix(int32_t size);
        ~OneDiagonalMatrix();

        // Returns elements of the matrix
        double& operator() (int32_t i);
        const double& operator () (int32_t i) const;

        void DebugOut();

        // Copy operator
        OneDiagonalMatrix& operator =(const OneDiagonalMatrix& other);
        Vector& operator *(const Vector& other);
    private:
        double *matrix;
        int32_t size;

        static double *_allocate_matrix(int32_t size);
    };

} // numerical

#endif //NUMERICAL_TASK_5_ONE_DIAGONAL_MATRIX_H
