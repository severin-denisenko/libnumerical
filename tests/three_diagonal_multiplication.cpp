//
// Created by Severin on 15.09.2022.
//

#include "libnumerical.h"

int main(int argc, char *argv[]){

    numerical::ThreeDiagonalMatrix a = numerical::ThreeDiagonalMatrix("../tests/data1.dat");
    numerical::ThreeDiagonalMatrix b = numerical::ThreeDiagonalMatrix("../tests/data2.dat");

    numerical::FiveDiagonalMatrix c = numerical::FiveDiagonalMatrix(a, b);
    c.Write("../tests/result.dat");


    return 0;
}
