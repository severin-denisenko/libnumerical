//
// Created by Severin on 17.09.2022.
//
#include "table.h"

numerical::Table::Table() {
    rows = 0;
    columns = 0;
    naming = TableNaming::UNNAMED;
};

numerical::Table::Table(int64_t rows, int64_t columns, numerical::Table::TableNaming naming) {
    this->rows = rows;
    this-> columns = columns;
    table = _allocate_table(rows, columns);
    this->naming = naming;
}

numerical::Table::Table(int64_t rows, int64_t columns, numerical::Table::TableNaming naming, std::vector<std::string> &names) {
    this->rows = rows;
    this-> columns = columns;
    table = _allocate_table(rows, columns);
    this->naming = naming;

    if (naming == TableNaming::NAMED_COLUMNS) {
        this->columnNames = &names;
    }
    if (naming == TableNaming::NAMED_ROWS) {
        this->rowNames = &names;
    }
    if (naming == TableNaming::NAMED_ROWS_AND_COLUMNS) {
        FATAL("Can't make table with rows and columns in this class constructor.")
    }
    if (naming == TableNaming::UNNAMED) {
        FATAL("Can't make unnamed table with this constructor.")
    }
}

numerical::Table::Table(int64_t rows, int64_t columns, std::vector<std::string> &columnNames, std::vector<std::string> &rowNames) {
    this->rows = rows;
    this->columns = columns;
    this->naming = TableNaming::NAMED_ROWS_AND_COLUMNS;
    this->table = _allocate_table(rows, columns);

    this->columnNames = &columnNames;
    this->rowNames = &rowNames;
}

numerical::Table::~Table() {
    for (int i = 0; i < rows; ++i) {
        free(table[i]);
    }
    free(table);
    INFO("Table deleted.")
}

void numerical::Table::Read(numerical::Table::TableType type,  const std::string& filename) {
    if (isTableAllocated){
        ERROR("Can't read already created table.")
    }
    //TODO

}

void numerical::Table::Write(numerical::Table::TableType type, const std::string& filename) {
    if (!isTableAllocated){
        ERROR("Can't write don't created table.")
        return;
    }

    std::fstream file(filename, std::ios::out);

    if (type == TableType::GNUPLOT_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS){
            WARNING("GNUplot table format isn't supporting rows naming. Skipping row names.")
        }
        if (naming == TableNaming::NAMED_ROWS){
            WARNING("GNUplot table format isn't supporting rows naming. Writing table without column names.")
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            file << "# ";
            for (int i = 0; i < columns; ++i) {
                file << (*columnNames)[i];
                if (i != columns - 1){
                    file << "\t";
                }
            }
            file << std::endl;
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                file << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                if (j != columns - 1){
                    file << "\t";
                }
            }
            file << std::endl;
        }
    }

    if (type == TableType::TSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < columns; ++i) {
                file << (*columnNames)[i];
                if (i != columns - 1){
                    file << "\t";
                }
            }
            file << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                file << (*rowNames)[i] << "\t";
                for (int j = 0; j < columns; ++j) {
                     file << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        file << "\t";
                    }
                }
                file << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    file << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        file << "\t";
                    }
                }
                file << std::endl;
            }
        }
    }

    if (type == TableType::CSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < columns; ++i) {
                file << (*columnNames)[i];
                if (i != columns - 1){
                    file << ",";
                }
            }
            file << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                file << (*rowNames)[i] << ",";
                for (int j = 0; j < columns; ++j) {
                     file << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        file << ",";
                    }
                }
                file << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    file << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        file << ",";
                    }
                }
                file << std::endl;
            }
        }
    }
}

void numerical::Table::AddRow() {
    if (naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
        ERROR("For row-named table require row name to add new row.")
        return;
    }

    _add_row();
}

void numerical::Table::AddColumn() {
    if (naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
        ERROR("For column-named table require column name to add new column.")
        return;
    }

    _add_column();
}

void numerical::Table::Sort(int64_t columnNumber) {
    if (!isTableAllocated){
        ERROR("Can't write don't created table.")
    }

    //TODO
}

double **numerical::Table::_allocate_table(int64_t rows, int64_t columns) {
    auto **_table = static_cast<double **>(malloc(sizeof(double *) * rows));

    if (_table == nullptr) {
        FATAL("Can't allocate so much memory.")
    }

    for (int i = 0; i < rows; ++i) {
        _table[i] = static_cast<double *>(malloc(sizeof(double) * columns));
        if (_table[i] == nullptr) {
            FATAL("Can't allocate so much memory.")
        }
    }

    isTableAllocated = true;
    INFO("Table allocated.")

    return _table;
}

const double &numerical::Table::operator()(int64_t i, int64_t j) const {
#if DEBUG_BUILD == 1
    if (0 < i <= rows && 0 < j <= columns){
        return table[i-1][j-1];
    } else {
        FATAL("Matrix out of borders.")
        return table[0][0];
    }
#else
    return matrix[i-1][j-1];
#endif
}

double &numerical::Table::operator()(int64_t i, int64_t j) {
#if DEBUG_BUILD == 1
    if (0 < i <= rows && 0 < j <= columns){
        return table[i-1][j-1];
    } else {
        FATAL("Matrix out of borders.")
        return table[0][0];
    }
#else
    return matrix[i-1][j-1];
#endif
}

void numerical::Table::Print(TableType type) {
    if (!isTableAllocated){
        ERROR("Can't print don't created table.")
        return;
    }

    if (type == TableType::GNUPLOT_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS){
            WARNING("GNUplot table format isn't supporting rows naming. Skipping row names.")
        }
        if (naming == TableNaming::NAMED_ROWS){
            WARNING("GNUplot table format isn't supporting rows naming. Writing table without column names.")
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            std::cout << "# ";
            for (int i = 0; i < columns; ++i) {
                std::cout << (*columnNames)[i];
                if (i != columns - 1){
                    std::cout << "\t";
                }
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                if (j != columns - 1){
                    std::cout << "\t";
                }
            }
            std::cout << std::endl;
        }
    }

    if (type == TableType::TSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < columns; ++i) {
                std::cout << (*columnNames)[i];
                if (i != columns - 1){
                    std::cout << "\t";
                }
            }
            std::cout << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                std::cout << (*rowNames)[i] << "\t";
                for (int j = 0; j < columns; ++j) {
                    std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        std::cout << "\t";
                    }
                }
                std::cout << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        std::cout << "\t";
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    if (type == TableType::CSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < columns; ++i) {
                std::cout << (*columnNames)[i];
                if (i != columns - 1){
                    std::cout << ",";
                }
            }
            std::cout << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                std::cout << (*rowNames)[i] << ",";
                for (int j = 0; j < columns; ++j) {
                    std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        std::cout << ",";
                    }
                }
                std::cout << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        std::cout << ",";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void numerical::Table::AddRow(const std::string &newRowName) {
    if(naming == TableNaming::NAMED_COLUMNS || naming == TableNaming::UNNAMED){
        ERROR("Can't add new row name to table without row names")
    }

    (*rowNames).push_back(newRowName);

    _add_row();
}

void numerical::Table::AddColumn(const std::string &newColumnName) {
    if(naming == TableNaming::NAMED_ROWS || naming == TableNaming::UNNAMED){
        ERROR("Can't add new column name to table without column names")
    }

    (*rowNames).push_back(newColumnName);

    _add_row();

}

void numerical::Table::_add_row() {
    if (rows != 0){
        rows += 1;
        table = static_cast<double **>(realloc(table, sizeof(double *) * rows));
        if (table == nullptr){
            ERROR("Can't add new row.")
        }
        table[rows-1] = static_cast<double *>(malloc(sizeof(double) * columns));
        if (table[rows-1] == nullptr){
            ERROR("Can't allocate new row.")
        }
    } else {
        rows += 1;
        if (columns != 0){
            _allocate_table(rows, columns);
        } else {
            WARNING("Adding row to empty table.")
        }
    }

}

void numerical::Table::_add_column() {
    if (columns != 0){
        columns += 1;
        for (int i = 0; i < rows; ++i) {
            table[i] = static_cast<double *>(realloc(table[i], sizeof(double) * columns));
            if(table[i] == nullptr){
                ERROR("Can't allocate new column.")
            }
        }
    } else {
        columns += 1;
        if (rows != 0){
            _allocate_table(rows, columns);
        } else {
            WARNING("Adding column to empty table.")
        }
    }
}
