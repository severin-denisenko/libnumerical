//
// Created by Severin on 17.09.2022.
//

#include "libnumerical.h"

int main(int argc, char *argv[]){

    numerical::SquareMatrix a = numerical::SquareMatrix("../tests/matrix1.dat");
    numerical::SquareMatrix b = numerical::SquareMatrix("../tests/matrix2.dat");

    numerical::SquareMatrix c = numerical::SquareMatrix(a.Size());

    c+=a;
    c*=c;

    c.Write("../tests/matrix3.dat");

    return 0;
}

