//
// Created by Severin on 18.09.2022.
//

#ifndef LIBNUMERICAL_INTERPOLATOR_H
#define LIBNUMERICAL_INTERPOLATOR_H

#include <cstdint>
#include <cmath>
#include "vector.h"

namespace numerical{
    class Interpolator{
    public:
        Interpolator(Vector &data, double a, double b, int q);
        Vector &Uniform();
        Vector &Chebyshev();
    private:
        static double uniform_x(int32_t k, int32_t n, double a, double b);
        static double chebyshev_x(int32_t k, int32_t n, double a, double b);
        static void _uniform(Vector &data, Vector &result, double a, double b, int q);

        Vector *data;
        Vector *result;
        double a;
        double b;
        int q;
    };
}

#endif //LIBNUMERICAL_INTERPOLATOR_H
