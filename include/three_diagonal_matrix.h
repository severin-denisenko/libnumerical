//
// Created by Severin on 16.09.2022.
//

#ifndef LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H
#define LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H

#include <cstdint>
#include <string>
#include <fstream>
#include "logger.h"
#include "vector.h"
#include "one_diagonal_matrix.h"

namespace numerical{
    class ThreeDiagonalMatrix{
    public:
        explicit ThreeDiagonalMatrix(int32_t size);
        explicit ThreeDiagonalMatrix(const std::string& filename);
        ThreeDiagonalMatrix(const ThreeDiagonalMatrix &other);
        ~ThreeDiagonalMatrix();
        void Write(const std::string &filename);

        // Returns elements of the matrix
        double& operator() (int32_t i, int32_t j);
        const double& operator () (int32_t i, int32_t j) const;

        // Copy operator
        ThreeDiagonalMatrix& operator =(const ThreeDiagonalMatrix& other);

        // Arithmetics
        ThreeDiagonalMatrix& operator +=(const ThreeDiagonalMatrix& other);
        ThreeDiagonalMatrix& operator -=(const ThreeDiagonalMatrix& other);
        ThreeDiagonalMatrix& operator *=(const OneDiagonalMatrix& other);
        Vector& operator *(const Vector& vector);

        void DebugOut();

        void Transpose();

        // returns matrix dimension
        int32_t Size() const;

    private:
        static double** _allocate_matrix(int32_t size);
        int32_t size;
        double **matrix;
    };
}

#endif //LIBNUMERICAL_THREE_DIAGONAL_MATRIX_H
