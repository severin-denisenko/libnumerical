//
// Created by Severin on 15.09.2022.
//

#ifndef LIBNUMERICAL_SQARE_MATRIX_H
#define LIBNUMERICAL_SQARE_MATRIX_H

#include <cstdlib>
#include <fstream>
#include "logger.h"

namespace numerical{
    class SquareMatrix{
    public:
        // Creates matrix full of zeros
        explicit SquareMatrix(int32_t size);

        // Loads matrix from file
        explicit SquareMatrix(const std::string& filename);
        ~SquareMatrix();

        // Writes matrix to file
        void Write(const std::string& filename);

        // Returns elements of the matrix
        double& operator() (int32_t i, int32_t j);
        const double& operator () (int32_t i, int32_t j) const;

        // Return row of the matrix
        double*& operator () (int32_t i) const;

        // Copy operator
        SquareMatrix& operator =(const SquareMatrix& other);

        // Arithmetics
        SquareMatrix& operator +=(const SquareMatrix& other);
        SquareMatrix& operator *=(const SquareMatrix& other);
        SquareMatrix& operator -=(const SquareMatrix& other);

        // returns matrix dimension
        int32_t Size() const;
    private:
        static double** _allocate_matrix(int32_t size);

        int32_t size;
        double **matrix;
    };
}

#endif //LIBNUMERICAL_SQARE_MATRIX_H
