//
// Created by Severin on 16.09.2022.
//

#ifndef LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H
#define LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H

#include <cstdint>
#include <string>
#include <fstream>
#include "logger.h"

namespace numerical{
    class ThreeDiagonalMatrix{
    public:
        explicit ThreeDiagonalMatrix(int64_t size);
        explicit ThreeDiagonalMatrix(const std::string& filename);
        ~ThreeDiagonalMatrix();
        void Write(const std::string &filename);

        // Returns elements of the matrix
        double& operator() (int64_t i, int64_t j);
        const double& operator () (int64_t i, int64_t j) const;

        // Copy operator
        ThreeDiagonalMatrix& operator =(const ThreeDiagonalMatrix& other);

        // Arithmetics
        ThreeDiagonalMatrix& operator +=(const ThreeDiagonalMatrix& other);
        ThreeDiagonalMatrix& operator -=(const ThreeDiagonalMatrix& other);

        // returns matrix dimension
        int64_t Size() const;

    private:
        static double** _allocate_matrix(int64_t size);
        int64_t size;
        double **matrix;
    };
}

#endif //LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H
