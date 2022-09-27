//
// Created by Severin on 16.09.2022.
//

#ifndef LIBNUMERICAL_FIVE_DIAGONAL_MATRIX_H
#define LIBNUMERICAL_FIVE_DIAGONAL_MATRIX_H

#include <cstdint>
#include <string>
#include <fstream>
#include "logger.h"
#include "three_diagonal_matrix.h"
#include "vector.h"

namespace numerical
{
    class FiveDiagonalMatrix
    {
    public:
        explicit FiveDiagonalMatrix(int64_t size);

        // Read from file
        explicit FiveDiagonalMatrix(const std::string &filename);

        // Copy constructor
        FiveDiagonalMatrix(const FiveDiagonalMatrix &other);

        // From multiplication of tho ThreeDiagonalMatrix
        FiveDiagonalMatrix(ThreeDiagonalMatrix &a, ThreeDiagonalMatrix &b);

        ~FiveDiagonalMatrix();

        void Write(const std::string &filename);

        FiveDiagonalMatrix &operator=(const FiveDiagonalMatrix &other);

        // Arithmetics
        FiveDiagonalMatrix &operator*=(double num);

        FiveDiagonalMatrix &operator+=(const FiveDiagonalMatrix &other);

        FiveDiagonalMatrix &operator-=(const FiveDiagonalMatrix &other);

        FiveDiagonalMatrix &operator+=(const ThreeDiagonalMatrix &other);

        Vector &operator*(const Vector &vector);

        // Returns elements of the matrix
        double &operator()(int64_t i, int64_t j);

        const double &operator()(int64_t i, int64_t j) const;

        // returns matrix dimension
        int64_t Size() const;

    private:
        static double **_allocate_matrix(int64_t size);

        int64_t size;
        double **matrix;

        void DebugOut();
    };
}

#endif //LIBNUMERICAL_FIVE_DIAGONAL_MATRIX_H
