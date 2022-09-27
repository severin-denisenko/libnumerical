//
// Created by Severin on 27.09.2022.
//

#include <cmath>
#include "linear_solver.h"

namespace numerical{
    LinearSolver::LinearSolver(SquareMatrix &Left, Vector &Rith) {
        if (Left.Size() != Left.Size()){
            FATAL("Can't solve equation with matrix and vector different dimensions.");
        }

        this->n = Left.Size();

        // Allocate memory
        A = (double **)malloc(sizeof(double *) * n);

        if (A == nullptr){
            FATAL("Can't allocate so mush memory.");
        }

        for (int i = 0; i < n; ++i)
        {
            A[i] = (double *)malloc(sizeof(double) * (n + 1));

            if (A[i] == nullptr){
                FATAL("Can't allocate so mush memory.");
            }
        }

        // Copy matrices

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                A[i][j] = Left(i + 1, j + 1);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            A[i][n] = Rith(i + 1);
        }

        // Duplicate matrix for use in LinearSolver::GetResidual()

        A_duplicate = static_cast<double **>(malloc(sizeof(double *) * n));

        if (A_duplicate == nullptr){
            FATAL("Can't allocate so mush memory.");
        }

        for (int i = 0; i < n; ++i)
        {
            A_duplicate[i] = static_cast<double *>(malloc(sizeof(double) * (n + 1)));

            if (A_duplicate[i] == nullptr){
                FATAL("Can't allocate so mush memory.");
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                A_duplicate[i][j] = A[i][j];
            }
        }

        // Allocate result

        X = (double *)malloc(sizeof(double) * n);

        if (X == nullptr){
            FATAL("Can't allocate so mush memory.");
        }

        // Allocate product

        AX = (double *)malloc(sizeof(double) * n);

        if (AX == nullptr){
            FATAL("Can't allocate so mush memory.");
        }
    }

    LinearSolver::~LinearSolver()
    {
        for (int i = 0; i < n; ++i)
        {
            delete[] A[i];
        }
        delete[] X;
        delete[] AX;
    }

    void LinearSolver::SolveGauss()
    {
        for (int j = 0; j < n; j++)
        {
            if (A[j][j] == 0)
            {
                printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
                exit(1);
            }

            if (abs(A[j][j]) < 10e-5L)
            {
                printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
            }

            for (int i = j + 1; i < n; i++)
            {
                double div = A[i][j] / A[j][j];

                for (int k = 0; k < n + 1; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }

        X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < n; j++)
            {
                sum = sum + A[i][j] * X[j];
            }
            X[i] = (A[i][n] - sum) / A[i][i];
        }
    }

    void LinearSolver::SolveJordan()
    {
        for (int j = 0; j < n; j++)
        {
            if (A[j][j] == 0)
            {
                printf("Element (%d, %d) is 0.\n", j + 1, j + 1);
                exit(1);
            }

            if (abs(A[j][j]) < 10e-5L)
            {
                printf("Element (%d, %d) is too close to 0.\n", j + 1, j + 1);
            }

            for (int i = 0; i < n; i++)
            {
                if (i != j)
                {
                    double div = A[i][j] / A[j][j];
                    for (int k = 0; k < n + 1; k++)
                    {
                        A[i][k] = A[i][k] - div * A[j][k];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            X[i] = A[i][n] / A[i][i];
        }
    }

    void LinearSolver::SolveLeadElement()
    {
        int *x_order = (int *) malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++)
        {
            x_order[i] = i;
        }

        for (int j = 0; j < n; j++)
        {
            // Serch for biggest element and change order //

            int max_i = 0;
            int max_j = 0;
            double max = 0;

            for (int z = j; z < n; z++)
            {
                for (int t = j; t < n; t++)
                {
                    if (fabs(A[z][t]) > max)
                    {
                        max = fabs(A[z][t]);
                        max_i = z;
                        max_j = t;
                    }
                }
            }

            //for (int i = 0; i < n; i++)
            //{
            //    std::swap(A[i][max_j], A[i][j]);
            //}
            //std::swap(A[max_i], A[j]);
            //std::swap(x_order[j], x_order[max_j]);

            for (int i = 0; i < n; i++)
            {
                double tmp = A[i][max_j];
                A[i][max_j] = A[i][j];
                A[i][j] = tmp;
            }

            double *tmp = A[j];
            A[j] = A[max_i];
            A[max_i] = tmp;

            int tmp1 = x_order[j];
            x_order[j] = x_order[max_j];
            x_order[max_j] = tmp1;


            ////////////////////////////////////////////////

            for (int i = j + 1; i < n; i++)
            {
                double div = A[i][j] / A[j][j];

                for (int k = 0; k < n + 1; k++)
                {
                    A[i][k] = A[i][k] - div * A[j][k];
                }
            }
        }

        X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < n; j++)
            {
                sum = sum + A[i][j] * X[j];
            }
            X[i] = (A[i][n] - sum) / A[i][i];
        }

        // Restore the order of X //

        for (int i = 0; i < n; i++) {
            int next = i;

            while (x_order[next] >= 0) {

                //std::swap(X[i], X[x_order[next]]);
                double tmp = X[i];
                X[i] = X[x_order[next]];
                X[x_order[next]] = tmp;

                int temp = x_order[next];

                x_order[next] -= n;
                next = temp;
            }
        }

        ////////////////////////////
    }

    double LinearSolver::GetResidual()
    {
        double residual = 0;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                AX[i] += X[j] * A_duplicate[i][j];
            }
        }

        for (int i = 0; i < n; ++i)
        {
            AX[i] -= A_duplicate[i][n];
        }

        for (int i = 0; i < n; ++i)
        {
            residual += AX[i] * AX[i];
        }

        residual = sqrt(residual);

        return residual;
    }

    Vector &LinearSolver::GetResult()
    {
        auto *res = new Vector(n);

        for (int i = 0; i < n; ++i)
        {
            (*res)(i + 1) = X[i];
        }

        return *res;
    }
}
