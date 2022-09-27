//
// Created by Severin on 18.09.2022.
//

#ifndef LIBNUMERICAL_INTERPOLATOR_H
#define LIBNUMERICAL_INTERPOLATOR_H

#include <cstdint>
#include <cmath>

namespace numerical{
    class Interpolator{
    public:
        Interpolator();
        void Uniform();
        void Chebyshev();
    private:
        static double uniform_x(int32_t k, int32_t n, double a, double b);
        static double chebyshev_x(int32_t k, int32_t n, double a, double b);
    };
}

#endif //LIBNUMERICAL_INTERPOLATOR_H
