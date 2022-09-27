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

namespace numerical
{
    class Table
    {
    public:
        enum TableType
        {
            CSV_TABLE = 0,
            TSV_TABLE = 1,
            GNUPLOT_TABLE = 3
        };
        typedef TableType TableType;

        enum TableNaming
        {
            NAMED_COLUMNS = 0,
            NAMED_ROWS = 1,
            NAMED_ROWS_AND_COLUMNS = 2,
            UNNAMED = 3
        };
        typedef TableNaming TableNaming;

        // Create empty unnamed table
        Table();

        // Create empty table with set naming
        explicit Table(TableNaming naming);

        // Create table with rows and columns with set naming
        Table(int32_t rows, int32_t columns, TableNaming naming);

        // Create table with rows and columns with named only rows or columns
        Table(int32_t rows, int32_t columns, TableNaming naming, std::vector<std::string> &names);

        // Create table with rows and columns with named rows and columns
        Table(int32_t rows, int32_t columns, std::vector<std::string> &columnNames,
              std::vector<std::string> &rowNames);

        ~Table();

        // Read table from file
        void Read(TableType type, numerical::Table::TableNaming naming, const std::string &filename);

        // Write table to file
        void Write(TableType type, const std::string &filename);

        // Prints table to console
        void Print(TableType type);

        // Writes table to a stream
        void Out(std::ostream &stream, TableType type);

        void AddRow();

        void AddColumn();

        void AddRow(const std::string &newRowName);

        void AddColumn(const std::string &newColumnName);

        void Sort(int32_t columnNumber);

        // Returns elements of the table
        double &operator()(int32_t i, int32_t j);

        const double &operator()(int32_t i, int32_t j) const;

        // Number of digits after a coma
        int16_t outputPrecision = 3;
    private:
        int32_t rows;
        int32_t columns;
        bool isTableAllocated = false;
        double **table{};
        std::vector<std::string> *columnNames;
        std::vector<std::string> *rowNames;
        TableNaming naming;

        double **_allocate_table();

        void _add_row();

        void _add_column();
    };
}

#endif //LIBNUMERICAL_TABLE_H
