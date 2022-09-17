//
// Created by Severin on 16.09.2022.
//

#include "three_diagonal_matrix.h"

numerical::ThreeDiagonalMatrix::ThreeDiagonalMatrix(int64_t size) {
    this->size = size;
    matrix = _allocate_matrix(size);
    INFO("Matrix allocated.")
}

numerical::ThreeDiagonalMatrix::ThreeDiagonalMatrix(const std::string &filename) {
    std::fstream file(filename, std::ios::in);
    if (!file.good()) {
        FATAL("Can't open file.")
    }

    char a;
    file >> a;
    if (a != '#') {
        FATAL("Can't read file: wrong format.")
    }
    file >> size;

    matrix = _allocate_matrix(size);

    for (int j = 0; j < 2; ++j) {
        file >> matrix[0][j];
    }
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 0; j < 3; ++j) {
            file >> matrix[i][j];
        }
    }
    for (int j = 0; j < 2; ++j) {
        file >> matrix[size - 1][j];
    }

    file.close();

    INFO("Matrix allocated and red.")
}

numerical::ThreeDiagonalMatrix::~ThreeDiagonalMatrix() {
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    INFO("Matrix deleted.")
}

double **numerical::ThreeDiagonalMatrix::_allocate_matrix(int64_t size) {
    auto** _matrix = static_cast<double **>(malloc(sizeof(double *) * size));
    if (_matrix == nullptr) {
        FATAL("Can't allocate so much memory.")
    }

    _matrix[0] = static_cast<double *>(malloc(sizeof(double) * 2));

    for (int i = 1; i < size - 1; ++i) {
        _matrix[i] = static_cast<double *>(malloc(sizeof(double) * 3));
        if (_matrix[i] == nullptr) {
            FATAL("Can't allocate so much memory.")
        }
    }

    _matrix[size - 1] = static_cast<double *>(malloc(sizeof(double) * 2));

    return _matrix;
}

void numerical::ThreeDiagonalMatrix::Write(const std::string &filename) {
    std::fstream file(filename, std::ios::out);

    file << "# " << size << std::endl;

    for (int j = 0; j < 2; ++j) {
        file << matrix[0][j] << " ";
    }

    file << std::endl;

    for (int i = 1; i < size - 1; ++i) {
        for (int j = 0; j < 3; ++j) {
            file << matrix[i][j] << " ";
        }

        file << std::endl;
    }

    for (int j = 0; j < 2; ++j) {
        file << matrix[size - 1][j] << " ";
    }

    file << std::endl;

    file.close();
}

int64_t numerical::ThreeDiagonalMatrix::Size() const {
    return size;
}

numerical::ThreeDiagonalMatrix &
numerical::ThreeDiagonalMatrix::operator+=(const numerical::ThreeDiagonalMatrix &other) {
    if (size != other.Size())
    {
        ERROR("= operator to tho non-equal sizes matrices.")
    }

    for (int j = 1; j <= 2; ++j) {
        (*this)(1, j) = (*this)(1, j) + other(1, j);
    }
    for (int i = 2; i <= size - 1; ++i) {
        for (int j = 1; j <= 3; ++j) {
            (*this)(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    for (int j = 1; j <= 2; ++j) {
        (*this)(size, j) = (*this)(size, j) + other(size, j);
    }

    return *this;
}

numerical::ThreeDiagonalMatrix &
numerical::ThreeDiagonalMatrix::operator=(const numerical::ThreeDiagonalMatrix &other) {
    // Guard self assignment
    if (this == &other){
        return *this;
    }

    if (size != other.Size())
    {
        ERROR("= operator to tho non-equal sizes matrices.")
    }

    for (int j = 1; j <= 2; ++j) {
        (*this)(1, j) = other(1, j);
    }
    for (int i = 2; i <= size - 1; ++i) {
        for (int j = 1; j <= 3; ++j) {
            (*this)(i, j) = other(i, j);
        }
    }
    for (int j = 1; j <= 2; ++j) {
        (*this)(size, j) = other(size, j);
    }

    return *this;
}

numerical::ThreeDiagonalMatrix &
numerical::ThreeDiagonalMatrix::operator-=(const numerical::ThreeDiagonalMatrix &other) {
    if (size != other.Size())
    {
        ERROR("= operator to tho non-equal sizes matrices.")
    }

    for (int j = 1; j <= 2; ++j) {
        (*this)(1, j) = (*this)(1, j) - other(1, j);
    }
    for (int i = 2; i <= size - 1; ++i) {
        for (int j = 1; j <= 3; ++j) {
            (*this)(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    for (int j = 1; j <= 2; ++j) {
        (*this)(size, j) = (*this)(size, j) - other(size, j);
    }

    return *this;
}

double &numerical::ThreeDiagonalMatrix::operator()(int64_t i, int64_t j) {
#if DEBUG_BUILD == 1
    if ((i == 1 && (j == 2 || j == 1)) || (i == size && (j == 2 || j == 1)) || (1 < i < size && (j == 1 || j == 2 || j == 3))){
        return matrix[i-1][j-1];
    } else {
        FATAL("Matrix out of borders.")
        return matrix[0][0];
    }
#else
    return matrix[i-1][j-1];
#endif
}

const double &numerical::ThreeDiagonalMatrix::operator()(int64_t i, int64_t j) const {
#if DEBUG_BUILD == 1
    if ((i == 1 && (j == 2 || j == 1)) || (i == size && (j == 2 || j == 1)) || (1 < i < size && (j == 1 || j == 2 || j == 3))){
        return matrix[i-1][j-1];
    } else {
        FATAL("Matrix out of borders.")
        return matrix[0][0];
    }
#else
    return matrix[i-1][j-1];
#endif
}
