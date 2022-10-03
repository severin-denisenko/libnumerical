//
// Created by Severin on 18.09.2022.
//
#include "interpolator.h"

namespace numerical
{

    Interpolator::Interpolator(Vector &data, double a, double b, int q)
    {
        this->data = &data;
        this->a = a;
        this->b = b;
        this->q = q;
    }

    double Interpolator::uniform_x(int32_t k, int32_t n, double a, double b)
    {
        return a + (b - a) / n * k;
    }

    double Interpolator::chebyshev_x(int32_t k, int32_t n, double a, double b)
    {
        return (a + b) / 2.0 + (a - b) / 2.0 * cos((2.0 * k + 1.0) / (2.0 * n + 2.0) * M_PI);
    }

    void Interpolator::_uniform(Vector &data, Vector &result, double a, double b, int q)
    {
        uint64_t n = data.Size();

        for (int k = 0; k < n * q + 1; ++k)
        {
            double x = uniform_x(k, n * q, a, b);
            double basics_polynomial = 1;
            double lagrange_polynomial = 0;

            for (int i = 0; i < n + 1; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    if (j == i)
                    {
                        continue;
                    }
                    basics_polynomial *= (x - uniform_x(j, n, a, b)) / (uniform_x(i, n, a, b) - uniform_x(j, n, a, b));
                }
                lagrange_polynomial += basics_polynomial * data(i + 1);
                basics_polynomial = 1;
            }

            result(k + 1) = lagrange_polynomial;
        }
    }
}
