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
        explicit SquareMatrix(int64_t size);

        // Loads matrix from file
        explicit SquareMatrix(const std::string& filename);
        ~SquareMatrix();

        // Writes matrix to file
        void Write(const std::string& filename);

        // Returns elements of the matrix
        double& operator() (int64_t i, int64_t j);
        const double& operator () (int64_t i, int64_t j) const;

        // Return row of the matrix
        double*& operator () (int64_t i) const;

        // Copy operator
        SquareMatrix& operator =(const SquareMatrix& other);

        // Arithmetics
        SquareMatrix& operator +=(const SquareMatrix& other);
        SquareMatrix& operator *=(const SquareMatrix& other);
        SquareMatrix& operator -=(const SquareMatrix& other);

        // returns matrix dimension
        int64_t Size() const;
    private:
        static double** _allocate_matrix(int64_t size);

        int64_t size;
        double **matrix;
    };
}

#endif //LIBNUMERICAL_SQARE_MATRIX_H
