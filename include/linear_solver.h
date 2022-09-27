//
// Created by Severin on 27.09.2022.
//

#ifndef LIBNUMERICAL_LINEAR_SOLVER_H
#define LIBNUMERICAL_LINEAR_SOLVER_H

#include "square_matrix.h"
#include "vector.h"

namespace numerical{
    class LinearSolver{
    public:
        LinearSolver(SquareMatrix &Left, Vector &Rith);
        ~LinearSolver();
        void SolveGauss();
        void SolveJordan();
        void SolveLeadElement();
        double GetResidual();
        Vector &GetResult();

    private:
        double **A;
        double **A_duplicate;
        double *X;
        double *AX;
        int n;
    };
}

#endif //LIBNUMERICAL_LINEAR_SOLVER_H
