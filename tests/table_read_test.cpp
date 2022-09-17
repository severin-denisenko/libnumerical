//
// Created by Severin on 18.09.2022.
//

#include "libnumerical.h"

int main(int argc, char *argv[]){
    numerical::Table a = numerical::Table();

    a.Read(numerical::Table::TableType::CSV_TABLE,
           numerical::Table::TableNaming::NAMED_ROWS_AND_COLUMNS,
           "../tests/solar_system.csv");

    a.Print(numerical::Table::TableType::CSV_TABLE);

    return 0;
}

