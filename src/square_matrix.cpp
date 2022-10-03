//
// Created by Severin on 15.09.2022.
//

#include "square_matrix.h"

namespace numerical
{

    SquareMatrix::SquareMatrix(int32_t size)
    {
        this->size = size;

        matrix = _allocate_matrix(size);

        INFO("Matrix allocated.");
    }

    SquareMatrix::~SquareMatrix()
    {
        for (int i = 0; i < size; ++i)
        {
            free(matrix[i]);
        }

        free(matrix);

        INFO("Matrix deleted.");
    }

    SquareMatrix::SquareMatrix(const std::string &filename)
    {
        std::fstream file(filename, std::ios::in);
        if (!file.good())
        {
            FATAL("Can't open file.");
        }

        char a;
        file >> a;
        if (a != '#')
        {
            FATAL("Can't read file: wrong format.");
        }
        file >> size;

        matrix = _allocate_matrix(size);

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                file >> matrix[i][j];
            }
        }

        file.close();

        INFO("Matrix allocated and red.");
    }

    double **SquareMatrix::_allocate_matrix(int32_t size)
    {
        auto **_matrix = static_cast<double **>(malloc(sizeof(double *) * size));

        if (_matrix == nullptr)
        {
            FATAL("Can't allocate so much memory.");
        }

        for (int i = 0; i < size; ++i)
        {
            _matrix[i] = static_cast<double *>(malloc(sizeof(double) * size));
            if (_matrix[i] == nullptr)
            {
                FATAL("Can't allocate so much memory.");
            }
        }

        return _matrix;
    }

    void SquareMatrix::Write(const std::string &filename)
    {
        std::fstream file(filename, std::ios::out);

        file << "# " << size << std::endl;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }
    }

    const double &SquareMatrix::operator()(int32_t i, int32_t j) const
    {
        if (!(0 < i && i <= size && 0 < j && j <= size))
        {
            FATAL("Matrix out of borders.");
        }

        return matrix[i - 1][j - 1];
    }

    double &SquareMatrix::operator()(int32_t i, int32_t j)
    {
        if (!(0 < i && i <= size && 0 < j && j <= size))
        {
            FATAL("Matrix out of borders.");
        }

        return matrix[i - 1][j - 1];
    }

    SquareMatrix &SquareMatrix::operator=(const SquareMatrix &other)
    {
        // Guard self assignment
        if (this == &other)
        {
            return *this;
        }

        if (size != other.Size())
        {
            ERROR("= operator to tho non-equal sizes matrices.");
        }

        for (int i = 1; i <= std::min(size, other.Size()); ++i)
        {
            for (int j = 1; j <= std::min(size, other.Size()); ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }

        INFO("Matrix copied");

        return *this;
    }

    int32_t SquareMatrix::Size() const
    {
        return size;
    }

    SquareMatrix &SquareMatrix::operator+=(const SquareMatrix &other)
    {
        if (size != other.Size())
        {
            ERROR("+ operator to tho non-equal sizes matrices.");
        }

        for (int i = 1; i <= std::min(size, other.Size()); ++i)
        {
            for (int j = 1; j <= std::min(size, other.Size()); ++j)
            {
                (*this)(i, j) = (*this)(i, j) + other(i, j);
            }
        }

        return *this;
    }

    SquareMatrix &SquareMatrix::operator*=(const SquareMatrix &other)
    {
        if (size != other.Size())
        {
            FATAL("* operator to tho non-equal sizes matrices.");
        }

        SquareMatrix res = SquareMatrix(size);

        for (int i = 1; i <= size; ++i)
        {
            double *resRowPointer = res(i);

            for (int k = 1; k <= size; ++k)
            {
                double tmpVal = (*this)(i, k);
                double *rigthRowPointer = other(k);

                for (int j = 0; j < size; ++j)
                {
                    resRowPointer[j] += tmpVal * rigthRowPointer[j];
                }
            }
        }

        (*this) = res;

        return *this;
    }

    double *&SquareMatrix::operator()(int32_t i) const
    {
        if (!(0 > i || i > size))
        {
            FATAL("Matrix out of borders.");
        }
        return matrix[i-1];
    }

    SquareMatrix &SquareMatrix::operator-=(const SquareMatrix &other)
    {
        if (size != other.Size())
        {
            WARNING("+ operator to tho non-equal sizes matrices.");
        }

        for (int i = 1; i <= std::min(size, other.Size()); ++i)
        {
            for (int j = 1; j <= std::min(size, other.Size()); ++j)
            {
                (*this)(i, j) = (*this)(i, j) - other(i, j);
            }
        }

        return *this;
    }

}
