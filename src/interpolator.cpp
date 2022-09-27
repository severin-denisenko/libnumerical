//
// Created by Severin on 18.09.2022.
//
#include "interpolator.h"

numerical::Interpolator::Interpolator() {

}

void numerical::Interpolator::Uniform() {
    //for (int k = 0; k < n * q + 1; ++k)
    //{
    //    double x = uniform_x(k, n * q, a, b);
    //    double basics_polynomial = 1;
    //    double lagrange_polynomial = 0;
//
    //    for (int i = 0; i < n + 1; i++)
    //    {
    //        for (int j = 0; j < n + 1; j++)
    //        {
    //            if (j == i)
    //            {
    //                continue;
    //            }
    //            basics_polynomial *= (x - uniform_x(j, n, a, b)) / (uniform_x(i, n, a, b) - uniform_x(j, n, a, b));
    //        }
    //        lagrange_polynomial += basics_polynomial * data[i];
    //        basics_polynomial = 1;
    //    }
//
    //    result[k] = lagrange_polynomial;
    //}
}

void numerical::Interpolator::Chebyshev() {
    //double *chebyshev_nodes = (double *)malloc(sizeof(double) * (n + 1));
    //for (int k = 0; k < n + 1; k++)
    //{
    //    chebyshev_nodes[k] = chebyshev_x(k, n, a, b);
    //}
//
    //double *basics_polynomial = (double *)malloc(sizeof(double) * (n + 1));
//
    //for (int k = 0; k < n * q + 1; ++k)
    //{
    //    double x = uniform_x(k, n * q, a, b);
    //    double lagrange_polynomial = 0;
//
    //    for (int i = 0; i < n + 1; i++)
    //    {
    //        for (int k = 0; k < n + 1; k++)
    //        {
    //            basics_polynomial[k] = 1;
    //        }
//
    //        for (int j = 0; j < n + 1; j++)
    //        {
    //            for (int l = 0; l < n + 1; l++)
    //            {
    //                if (j == l)
    //                {
    //                    continue;
    //                }
    //                basics_polynomial[j] *= (x - chebyshev_nodes[l]) / (chebyshev_nodes[j] - chebyshev_nodes[l]);
    //            }
    //        }
//
    //        lagrange_polynomial += basics_polynomial[i] * data[i];
    //    }
//
    //    result[k] = lagrange_polynomial;
    //}
//
    //free(chebyshev_nodes);
    //free(basics_polynomial);
}

double numerical::Interpolator::uniform_x(int32_t k, int32_t n, double a, double b)
{
    return a + (b - a) / n * k;
}

double numerical::Interpolator::chebyshev_x(int32_t k, int32_t n, double a, double b)
{
    return (a + b) / 2.0 + (a - b) / 2.0 * cos((2.0 * k + 1.0) / (2.0 * n + 2.0) * M_PI);
}

