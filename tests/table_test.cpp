//
// Created by Severin on 17.09.2022.
//

#include <cmath>
#include "libnumerical.h"

int main(int argc, char *argv[]){

    std::vector<std::string> columnNames = {"name1", "name2", "name3", "name4"};
    std::vector<std::string> rowNames = {"Blue", "Red", "Orange", "Yellow"};

    numerical::Table a = numerical::Table(4, 4, columnNames, rowNames);

    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 4; ++j) {
            a(i, j) = sqrt(i + j);
        }
    }

    a.outputPrecision = 5;

    a.Write(numerical::Table::CSV_TABLE, "../tests/table.csv");
    a.Write(numerical::Table::GNUPLOT_TABLE, "../tests/table.plotdata");
    a.Write(numerical::Table::TSV_TABLE, "../tests/table.tsv");

    a.outputPrecision = 1;
    a.Print(numerical::Table::CSV_TABLE);
    a.AddColumn("blablabla");
    a.AddRow("blablabla");
    a.Print(numerical::Table::CSV_TABLE);

    return 0;
}
