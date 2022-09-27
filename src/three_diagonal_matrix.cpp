//
// Created by Severin on 16.09.2022.
//

#include "three_diagonal_matrix.h"

namespace numerical
{

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(int64_t size)
    {
        this->size = size;
        matrix = _allocate_matrix(size);
        INFO("Matrix allocated.")
    }

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(const std::string &filename)
    {
        std::fstream file(filename, std::ios::in);
        if (!file.good())
        {
            FATAL("Can't open file.")
        }

        char a;
        file >> a;
        if (a != '#')
        {
            FATAL("Can't read file: wrong format.")
        }
        file >> size;

        matrix = _allocate_matrix(size);

        for (int j = 0; j < 2; ++j)
        {
            file >> matrix[0][j];
        }
        for (int i = 1; i < size - 1; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                file >> matrix[i][j];
            }
        }
        for (int j = 0; j < 2; ++j)
        {
            file >> matrix[size - 1][j];
        }

        file.close();

        INFO("Matrix allocated and red.")
    }

    ThreeDiagonalMatrix::~ThreeDiagonalMatrix()
    {
        for (int i = 0; i < size; ++i)
        {
            free(matrix[i]);
        }
        free(matrix);

        INFO("Matrix deleted.")
    }

    double **ThreeDiagonalMatrix::_allocate_matrix(int64_t size)
    {
        auto **_matrix = static_cast<double **>(malloc(sizeof(double *) * size));
        if (_matrix == nullptr)
        {
            FATAL("Can't allocate so much memory.")
        }

        _matrix[0] = static_cast<double *>(malloc(sizeof(double) * 2));

        for (int i = 1; i < size - 1; ++i)
        {
            _matrix[i] = static_cast<double *>(malloc(sizeof(double) * 3));
            if (_matrix[i] == nullptr)
            {
                FATAL("Can't allocate so much memory.")
            }
        }

        _matrix[size - 1] = static_cast<double *>(malloc(sizeof(double) * 2));

        return _matrix;
    }

    void ThreeDiagonalMatrix::Write(const std::string &filename)
    {
        std::fstream file(filename, std::ios::out);

        file << "# " << size << std::endl;

        for (int j = 0; j < 2; ++j)
        {
            file << matrix[0][j] << " ";
        }

        file << std::endl;

        for (int i = 1; i < size - 1; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                file << matrix[i][j] << " ";
            }

            file << std::endl;
        }

        for (int j = 0; j < 2; ++j)
        {
            file << matrix[size - 1][j] << " ";
        }

        file << std::endl;

        file.close();
    }

    int64_t ThreeDiagonalMatrix::Size() const
    {
        return size;
    }

    ThreeDiagonalMatrix &
    ThreeDiagonalMatrix::operator+=(const ThreeDiagonalMatrix &other)
    {
        if (size != other.Size())
        {
            ERROR("= operator to tho non-equal sizes matrices.")
        }

        for (int j = 1; j <= 2; ++j)
        {
            (*this)(1, j) = (*this)(1, j) + other(1, j);
        }
        for (int i = 2; i <= size - 1; ++i)
        {
            for (int j = 1; j <= 3; ++j)
            {
                (*this)(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        for (int j = 1; j <= 2; ++j)
        {
            (*this)(size, j) = (*this)(size, j) + other(size, j);
        }

        return *this;
    }

    ThreeDiagonalMatrix &
    ThreeDiagonalMatrix::operator=(const ThreeDiagonalMatrix &other)
    {
        // Guard self assignment
        if (this == &other)
        {
            return *this;
        }

        if (size != other.Size())
        {
            ERROR("= operator to tho non-equal sizes matrices.")
        }

        for (int j = 1; j <= 2; ++j)
        {
            (*this)(1, j) = other(1, j);
        }
        for (int i = 2; i <= size - 1; ++i)
        {
            for (int j = 1; j <= 3; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
        for (int j = 1; j <= 2; ++j)
        {
            (*this)(size, j) = other(size, j);
        }

        return *this;
    }

    ThreeDiagonalMatrix &
    ThreeDiagonalMatrix::operator-=(const ThreeDiagonalMatrix &other)
    {
        if (size != other.Size())
        {
            ERROR("= operator to tho non-equal sizes matrices.")
        }

        for (int j = 1; j <= 2; ++j)
        {
            (*this)(1, j) = (*this)(1, j) - other(1, j);
        }
        for (int i = 2; i <= size - 1; ++i)
        {
            for (int j = 1; j <= 3; ++j)
            {
                (*this)(i, j) = (*this)(i, j) - other(i, j);
            }
        }
        for (int j = 1; j <= 2; ++j)
        {
            (*this)(size, j) = (*this)(size, j) - other(size, j);
        }

        return *this;
    }

    double &ThreeDiagonalMatrix::operator()(int64_t i, int64_t j)
    {
        if (!((i == 1 && (j == 2 || j == 1)) ||
              (i == size && (j == 2 || j == 1)) ||
              (1 < i < size && (j == 1 || j == 2 || j == 3))))
        {
            FATAL("Matrix out of borders.")
        }
        return matrix[i - 1][j - 1];
    }

    const double &ThreeDiagonalMatrix::operator()(int64_t i, int64_t j) const
    {
        if (!((i == 1 && (j == 2 || j == 1)) ||
              (i == size && (j == 2 || j == 1)) ||
              (1 < i < size && (j == 1 || j == 2 || j == 3))))
        {
            FATAL("Matrix out of borders.")
        }
        return matrix[i - 1][j - 1];
    }

    Vector &ThreeDiagonalMatrix::operator*(const Vector &vector) {
        auto *res = new Vector(size);

        (*res)(1) = (*this)(1, 1) * vector(1) + (*this)(1, 2) * vector(2);

        for (int i = 2; i <= size - 1; ++i) {
            (*res)(i) = (*this)(i, 1) * vector(i - 1) + (*this)(i, 2) * vector(i) + (*this)(i, 3) * vector(i + 1);
        }

        (*res)(size) = (*this)(size, 1) * vector(size - 1) + (*this)(size, 2) * vector(size);

        return *res;
    }

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(const ThreeDiagonalMatrix &other)
    {
        this->size = other.size;
        this->matrix = _allocate_matrix(size);

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

    }

    void ThreeDiagonalMatrix::DebugOut()
    {
        for (int j = 1; j <= 2; ++j) {
            std::cout << std::setprecision(3) << std::fixed  << (*this)(1, j) << " ";
        }
        std::cout << std::endl;
        for (int i = 2; i <= size - 1; ++i) {
            for (int j = 1; j <= 3; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
        for (int j = 1; j <= 2; ++j) {
            std::cout << (*this)(size, j) << " ";
        }
        std::cout << std::endl;
    }

    ThreeDiagonalMatrix &ThreeDiagonalMatrix::operator*=(const OneDiagonalMatrix &other) {

        for (int j = 1; j <= 2; ++j) {
            (*this)(1, j) *= other(j);
        }
        for (int i = 2; i <= size - 1; ++i) {
            for (int j = 1; j <= 3; ++j) {
                (*this)(i, j) *= other(j);
            }
        }
        for (int j = 1; j <= 2; ++j) {
            (*this)(size, j) *= other(j);
        }

        return *this;
    }

    void ThreeDiagonalMatrix::Transpose() {
        double tmp = (*this)(1, 2);
        (*this)(1, 2) = (*this)(2, 1);
        (*this)(2, 1) = tmp;

        for (int i = 3; i <= size - 1; ++i) {
            tmp = (*this)(i, 1);
            (*this)(i, 1) = (*this)(i - 1, 3);
            (*this)(i - 1, 3) = tmp;
        }

        tmp = (*this)(size, 1);
        (*this)(size, 1) = (*this)(size - 1, 3);
        (*this)(size - 1, 3) = tmp;
    }
}
