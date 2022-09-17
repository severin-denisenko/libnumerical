//
// Created by Severin on 17.09.2022.
//

#ifndef LIBNUMERICAL_TABLE_H
#define LIBNUMERICAL_TABLE_H

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include "logger.h"

namespace numerical{
    class Table{
    public:
        enum TableType{
            CSV_TABLE = 0,
            TSV_TABLE = 1,
            GNUPLOT_TABLE = 3
        };
        typedef TableType TableType;

        enum TableNaming{
            NAMED_COLUMNS = 0,
            NAMED_ROWS = 1,
            NAMED_ROWS_AND_COLUMNS = 2
        };
        typedef TableNaming TableNaming;

        Table();
        Table(int64_t rows, int64_t columns, TableNaming naming);
        Table(int64_t rows, int64_t columns, TableNaming naming, std::vector<std::string> &names);
        Table(int64_t rows, int64_t columns, std::vector<std::string> &columnNames, std::vector<std::string> &rowNames);

        ~Table();

        void Read(TableType type, const std::string& filename);
        void Write(TableType type, const std::string& filename);
        void Print(TableType type);

        void AddRow();
        void AddColumn();

        void Sort(int64_t columnNumber);

        // Returns elements of the matrix
        double& operator() (int64_t i, int64_t j);
        const double& operator () (int64_t i, int64_t j) const;

        int16_t outputPrecision = 3;
    private:
        int64_t rows;
        int64_t columns;
        bool isTableAllocated = false;
        double **table;
        std::vector<std::string> *columnNames;
        std::vector<std::string> *rowNames;
        TableNaming naming;

        double **_allocate_table(int64_t rows, int64_t columns);
    };
}

#endif //LIBNUMERICAL_TABLE_H
