//
// Created by Severin on 21.09.2022.
//

#include "one_diagonal_matrix.h"

namespace numerical {
    OneDiagonalMatrix::OneDiagonalMatrix(int64_t size) {
        this->size = size;
        matrix = _allocate_matrix(size);
    }

    double *OneDiagonalMatrix::_allocate_matrix(int64_t size) {
        auto *_matrix = static_cast<double *>(malloc(sizeof(double) * size));

        if (_matrix == nullptr){
            FATAL("Can't allocate so much memory.");
        }

        return _matrix;
    }

    OneDiagonalMatrix::~OneDiagonalMatrix() {
        free(matrix);
    }

    double &OneDiagonalMatrix::operator()(int64_t i) {
        if (i < 1 || i > size) {
            FATAL("Matrix out of borders.");
        }

        return matrix[i - 1];
    }

    const double &OneDiagonalMatrix::operator()(int64_t i) const {
        if (i < 1 || i > size) {
            FATAL("Matrix out of borders.");
        }

        return matrix[i - 1];
    }

    OneDiagonalMatrix &OneDiagonalMatrix::operator=(const OneDiagonalMatrix &other) {
        if (this == &other) {
            return *this;
        }

        (*this).size = other.size;
        (*this).matrix = _allocate_matrix(size);

        for (int i = 0; i < size; ++i) {
            (*this)(i) = other(i);
        }

        return *this;
    }

    Vector &OneDiagonalMatrix::operator*(const Vector &vector) {
        if (this->size != vector.Size()){
            FATAL("Can't multiply matrix on vector different dimension.");
        }

        auto *res = new Vector(size);

        for (int i = 1; i <= size; ++i) {
            (*res)(i) = (*this)(i) * vector(i);
        }

        return *res;
    }

    void OneDiagonalMatrix::DebugOut()
    {
        for (int i = 1; i <= size; ++i) {
             std::cout << (*this)(i) << std::endl;
        }
    }
} // numerical