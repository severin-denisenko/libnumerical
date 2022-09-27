//
// Created by Severin on 16.09.2022.
//

#include "five_diagonal_matrix.h"
namespace numerical{

numerical::FiveDiagonalMatrix::FiveDiagonalMatrix(int64_t size) {
    this->size = size;
    matrix = _allocate_matrix(size);
    INFO("Matrix allocated.");
}

numerical::FiveDiagonalMatrix::FiveDiagonalMatrix(const std::string &filename) {
    std::fstream file(filename, std::ios::in);
    if (!file.good()) {
        FATAL("Can't open file.");
    }

    char a;
    file >> a;
    if (a != '#') {
        FATAL("Can't read file: wrong format.");
    }
    file >> size;

    matrix = _allocate_matrix(size);

    for (int j = 0; j < 3; ++j) {
        file >> matrix[0][j];
    }
    for (int j = 0; j < 4; ++j) {
        file >> matrix[1][j];
    }
    for (int i = 2; i < size - 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            file >> matrix[i][j];
        }
    }
    for (int j = 0; j < 4; ++j) {
        file >> matrix[size - 2][j];
    }
    for (int j = 0; j < 3; ++j) {
        file >> matrix[size - 1][j];
    }

    file.close();

    INFO("Matrix allocated and red.");
}

numerical::FiveDiagonalMatrix::~FiveDiagonalMatrix() {
    for (int i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    INFO("Matrix deleted.");
}

double **numerical::FiveDiagonalMatrix::_allocate_matrix(int64_t size) {
    auto** _matrix = static_cast<double **>(malloc(sizeof(double *) * size));
    if (_matrix == nullptr) {
        FATAL("Can't allocate so much memory.");
    }

    _matrix[0] = static_cast<double *>(malloc(sizeof(double) * 3));
    if (_matrix[0] == nullptr) {
        FATAL("Can't allocate so much memory.");
    }

    _matrix[1] = static_cast<double *>(malloc(sizeof(double) * 4));
    if (_matrix[1] == nullptr) {
        FATAL("Can't allocate so much memory.");
    }

    for (int i = 2; i < size - 2; ++i) {
        _matrix[i] = static_cast<double *>(malloc(sizeof(double) * 5));
        if (_matrix[i] == nullptr) {
            FATAL("Can't allocate so much memory.");
        }
    }

    _matrix[size - 2] = static_cast<double *>(malloc(sizeof(double) * 4));
    if (_matrix[size - 2] == nullptr) {
        FATAL("Can't allocate so much memory.");
    }

    _matrix[size - 1] = static_cast<double *>(malloc(sizeof(double) * 3));
    if (_matrix[size - 1] == nullptr) {
        FATAL("Can't allocate so much memory.");
    }

    INFO("Matrix allocated.");

    return _matrix;
}

void numerical::FiveDiagonalMatrix::Write(const std::string &filename) {
    std::fstream file(filename, std::ios::out);

    file << "# " << size << std::endl;

    for (int j = 0; j < 3; ++j) {
        file << matrix[0][j] << " ";
    }
    file << std::endl;

    for (int j = 0; j < 4; ++j) {
        file << matrix[1][j] << " ";
    }
    file << std::endl;

    for (int i = 2; i < size - 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            file << matrix[i][j] << " ";
        }
        file << std::endl;
    }

    for (int j = 0; j < 4; ++j) {
        file << matrix[size - 2][j] << " ";
    }
    file << std::endl;

    for (int j = 0; j < 3; ++j) {
        file << matrix[size - 1][j] << " ";
    }
    file << std::endl;

    file.close();
}

int64_t numerical::FiveDiagonalMatrix::Size() const {
    return size;
}

double &numerical::FiveDiagonalMatrix::operator()(int64_t i, int64_t j) {
    if (!((i == 1 && (j == 3 || j == 2 || j == 1)) ||
          (i == 2 && (j == 4 || j == 3 || j == 2 || j == 1)) ||
          (i == size && (j == 3 || j == 2 || j == 1)) ||
          (i == size - 1 && (j == 4 || j == 3 || j == 2 || j == 1)) ||
          (2 < i < size - 1 && (j == 1 || j == 2 || j == 3 || j == 4 || j == 5))))
    {
        FATAL("Matrix out of borders.");
    }
    return matrix[i-1][j-1];
}

const double &numerical::FiveDiagonalMatrix::operator()(int64_t i, int64_t j) const {
    if (!((i == 1 && (j == 3 || j == 2 || j == 1)) ||
        (i == 2 && (j == 4 || j == 3 || j == 2 || j == 1)) ||
        (i == size && (j == 3 || j == 2 || j == 1)) ||
        (i == size - 1 && (j == 4 || j == 3 || j == 2 || j == 1)) ||
        (2 < i < size - 1 && (j == 1 || j == 2 || j == 3 || j == 4 || j == 5))))
    {
        FATAL("Matrix out of borders.");
    }
    return matrix[i-1][j-1];
}

numerical::FiveDiagonalMatrix::FiveDiagonalMatrix(numerical::ThreeDiagonalMatrix &a, numerical::ThreeDiagonalMatrix &b) {
    if (a.Size() != b.Size()){
        FATAL("Can't multiply matrices different dimensions.");
    }

    size = a.Size();
    matrix = _allocate_matrix(size);

    // For first row

    (*this)(1, 1) = a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1);
    (*this)(1, 2) = a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2);
    (*this)(1, 3) = a(1, 2) * b(2, 3);

    // For second row

    (*this)(2, 1) = a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1);
    (*this)(2, 2) = a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 1);
    (*this)(2, 3) = a(2, 2) * b(2, 3) + a(2, 3) * b(3, 2);
    (*this)(2, 4) = a(2, 3) * b(3, 3);

    // For others rows

    for (int i = 3; i < size-1; ++i) {
        (*this)(i, 1) = a(i, 1) * b(i - 1, 1);
        (*this)(i, 2) = a(i, 1) * b(i - 1, 2) + a(i, 2) * b(i, 1);
        (*this)(i, 3) = a(i, 1) * b(i - 1, 3) + a(i, 2) * b(i, 2) + a(i, 3) * b(i + 1, 1);
        (*this)(i, 4) = a(i, 2) * b(i, 3) + a(i, 3) * b(i + 1, 2);
        (*this)(i, 5) = a(i, 3) * b(i + 1, 3);
    }

    // For pre-last row

    (*this)(size - 1, 1) = a(size - 1, 1) * b(size - 2, 1);
    (*this)(size - 1, 2) = a(size - 1, 1) * b(size - 2, 2) + a(size - 1, 2) * b(size - 1, 1);
    (*this)(size - 1, 3) = a(size - 1, 1) * b(size - 2, 3) + a(size - 1, 2) * b(size - 1, 2) + a(size - 1, 3) * b(size, 1);
    (*this)(size - 1, 4) = a(size - 1, 2) * b(size - 1, 3) + a(size - 1, 3) * b(size, 2);

    // For last row

    (*this)(size, 1) = a(size, 1) * b(size - 1, 1);
    (*this)(size, 2) = a(size, 1) * b(size - 1, 2) + a(size, 2) * b(size, 1);
    (*this)(size, 3) = a(size, 1) * b(size - 1, 3) + a(size, 2) * b(size, 2);
}

FiveDiagonalMatrix &FiveDiagonalMatrix::operator=(const FiveDiagonalMatrix &other) {
    // Guard self assignment
    if (this == &other) {
        return *this;
    }

    (*this).size = other.size;
    (*this).matrix = _allocate_matrix(size);

    for (int j = 1; j <= 3; ++j) {
        (*this)(1, j) = other(1, j);
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(2, j) = other(2, j);
    }
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            (*this)(i, j) = other(i, j);
        }
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(size - 1, j) = other(size - 1, j);
    }
    for (int j = 1; j <= 3; ++j) {
        (*this)(size, j) = other(size, j);
    }

    return *this;
}

FiveDiagonalMatrix &FiveDiagonalMatrix::operator*=(double num) {
    for (int j = 1; j <= 3; ++j) {
        (*this)(1, j) = (*this)(1, j) * num;
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(2, j) = (*this)(2, j) * num;
    }
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            (*this)(i, j) = (*this)(i, j) * num;
        }
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(size - 1, j) = (*this)(size - 1, j) * num;
    }
    for (int j = 1; j <= 3; ++j) {
        (*this)(size, j) = (*this)(size, j) * num;
    }

    return *this;
}

FiveDiagonalMatrix &FiveDiagonalMatrix::operator+=(const FiveDiagonalMatrix &other) {
    for (int j = 1; j <= 3; ++j) {
        (*this)(1, j) += other(1, j);
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(2, j) += other(2, j);
    }
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            (*this)(i, j) += other(i, j);
        }
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(size - 1, j) += other(size - 1, j);
    }
    for (int j = 1; j <= 3; ++j) {
        (*this)(size, j) += other(size, j);
    }

    return *this;
}

FiveDiagonalMatrix &FiveDiagonalMatrix::operator-=(const FiveDiagonalMatrix &other) {
    for (int j = 1; j <= 3; ++j) {
        (*this)(1, j) -= other(1, j);
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(2, j) -= other(2, j);
    }
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            (*this)(i, j) -= other(i, j);
        }
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(size - 1, j) -= other(size - 1, j);
    }
    for (int j = 1; j <= 3; ++j) {
        (*this)(size, j) -= other(size, j);
    }

    return *this;
}

FiveDiagonalMatrix &FiveDiagonalMatrix::operator+=(const ThreeDiagonalMatrix &other) {
    (*this)(1, 1) += other(1, 1);
    (*this)(1, 2) += other(1, 2);

    (*this)(2, 1) += other(2, 1);
    (*this)(2, 2) += other(2, 2);
    (*this)(2, 3) += other(2, 3);

    for (int i = 3; i <= size - 2; ++i) {
        (*this)(i, 2) += other(i, 1);
        (*this)(i, 3) += other(i, 2);
        (*this)(i, 4) += other(i, 3);
    }

    (*this)(size, 2) += other(size, 1);
    (*this)(size, 3) += other(size, 2);

    (*this)(size - 1, 2) += other(size - 1, 1);
    (*this)(size - 1, 3) += other(size - 1, 2);
    (*this)(size - 1, 4) += other(size - 1, 3);

    return *this;
}

void FiveDiagonalMatrix::DebugOut() {
    for (int j = 1; j <= 3; ++j) {
        std::cout << std::setprecision(3) << std::fixed  << (*this)(1, j) << " ";
    }
    std::cout << std::endl;
    for (int j = 1; j <= 4; ++j) {
        std::cout << (*this)(2, j) << " ";
    }
    std::cout << std::endl;
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    for (int j = 1; j <= 4; ++j) {
        std::cout << (*this)(size - 1, j) << " ";
    }
    std::cout << std::endl;
    for (int j = 1; j <= 3; ++j) {
        std::cout << (*this)(size, j) << " ";
    }
    std::cout << std::endl;
}

Vector &FiveDiagonalMatrix::operator*(const Vector &vector) {
    auto *res = new Vector(size);

    (*res)(1) = (*this)(1, 1) * vector(1) +
                (*this)(1, 2) * vector(2) +
                (*this)(1, 3) * vector(3);

    (*res)(2) = (*this)(2, 1) * vector(1) +
                (*this)(2, 2) * vector(2) +
                (*this)(2, 3) * vector(3) +
                (*this)(2, 4) * vector(4);

    for (int i = 3; i <= size - 2; ++i) {
        (*res)(i) = (*this)(i, 1) * vector(i - 2) +
                        (*this)(i, 2) * vector(i - 1) +
                        (*this)(i, 3) * vector(i) +
                        (*this)(i, 4) * vector(i + 1) +
                        (*this)(i, 5) * vector(i + 2);
    }

    (*res)(size - 1) = (*this)(size - 1, 1) * vector(size - 3) +
                       (*this)(size - 1, 2) * vector(size - 2) +
                       (*this)(size - 1, 3) * vector(size - 1) +
                       (*this)(size - 1, 4) * vector(size);

    (*res)(size) = (*this)(size, 1) * vector(size - 2) +
                       (*this)(size, 2) * vector(size - 1) +
                       (*this)(size, 3) * vector(size);

    return *res;
}

FiveDiagonalMatrix::FiveDiagonalMatrix(const FiveDiagonalMatrix &other)
{
    this->size = other.size;
    this->matrix = _allocate_matrix(size);

    for (int j = 1; j <= 3; ++j) {
        (*this)(1, j) = other(1, j);
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(2, j) = other(2, j);
    }
    for (int i = 3; i <= size - 2; ++i) {
        for (int j = 1; j <= 5; ++j) {
            (*this)(i, j) = other(i, j);
        }
    }
    for (int j = 1; j <= 4; ++j) {
        (*this)(size - 1, j) = other(size - 1, j);
    }
    for (int j = 1; j <= 3; ++j) {
        (*this)(size, j) = other(size, j);
    }
}


}