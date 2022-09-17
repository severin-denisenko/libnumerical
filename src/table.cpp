//
// Created by Severin on 17.09.2022.
//
#include "table.h"

numerical::Table::Table() {
    this->rowNames = new std::vector<std::string>();
    this->columnNames = new std::vector<std::string>();
    this->rows = 0;
    this->columns = 0;
    this->naming = TableNaming::UNNAMED;
}

numerical::Table::Table(uint64_t rows, uint64_t columns, numerical::Table::TableNaming naming) {
    this->rowNames = new std::vector<std::string>();
    this->columnNames = new std::vector<std::string>();
    this->rows = rows;
    this-> columns = columns;
    table = _allocate_table();
    this->naming = naming;
}

numerical::Table::Table(uint64_t rows, uint64_t columns, numerical::Table::TableNaming naming, std::vector<std::string> &names) {
    this->rows = rows;
    this-> columns = columns;
    table = _allocate_table();
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

numerical::Table::Table(uint64_t rows, uint64_t columns, std::vector<std::string> &columnNames, std::vector<std::string> &rowNames) {
    this->rows = rows;
    this->columns = columns;
    this->naming = TableNaming::NAMED_ROWS_AND_COLUMNS;
    this->table = _allocate_table();

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

void numerical::Table::Read(numerical::Table::TableType type, numerical::Table::TableNaming naming,  const std::string& filename) {
    if (isTableAllocated){
        ERROR("Can't read already created table.")
        return;
    }

    this->naming = naming;

    std::fstream file(filename);

    std::string delimiter;
    if (type == TableType::GNUPLOT_TABLE){
        delimiter = "\t";
    }
    if (type == TableType::CSV_TABLE){
        delimiter = ",";
    }
    if (type == TableType::TSV_TABLE){
        delimiter = "\t";
    }

    // parse column names
    if (naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
        std::string names;
        std::getline(file, names);

        // Deleting "# " from first row from GNUPlot table
        if (type == TableType::GNUPLOT_TABLE){
            if(names.substr(0, 2) == "# "){
                names.erase(0, 2);
            } else {
                ERROR("Invalid GNUPlot table format.")
            }
        }

        size_t pos;
        std::string name;
        while ((pos = names.find(delimiter)) != std::string::npos) {
            name = names.substr(0, pos);
            columnNames->push_back(name);
            names.erase(0, pos + delimiter.length());
        }
        columnNames->push_back(names);
    }

    while (file.good()){
        std::string row;
        std::getline(file, row);

        if(naming == TableNaming::NAMED_ROWS || naming == TableNaming::NAMED_ROWS_AND_COLUMNS){
            std::string name = row.substr(0, row.find(delimiter));
            rowNames->push_back(name);
            row.erase(0, row.find(delimiter) + delimiter.length());
        }

        if(row.empty()){
            break;
        }

        _add_row();

        size_t pos;
        for (uint64_t i = 0; (pos = row.find(delimiter)) != std::string::npos; ++i) {
            double number;
            number = stod(row.substr(0, pos));
            row.erase(0, pos + delimiter.length());

            if (i + 1 > columns){
                _add_column();
            }

            table[rows-1][i] = number;
        }
    }
}

void numerical::Table::Write(numerical::Table::TableType type, const std::string& filename) {
    if (!isTableAllocated){
        ERROR("Can't write don't created table.")
        return;
    }

    std::streambuf * buf;
    std::ofstream of;
    of.open(filename);
    buf = of.rdbuf();
    std::ostream out(buf);

    Out(out , type);
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

    ERROR("Isn't implemented function")
    //TODO
}

double **numerical::Table::_allocate_table() {
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

    std::streambuf * buf;
    std::ofstream of;
    buf = std::cout.rdbuf();
    std::ostream out(buf);

    Out(out , type);
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

    (*columnNames).push_back(newColumnName);

    _add_column();

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
            table = _allocate_table();
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
            table = _allocate_table();
        }
    }
}

numerical::Table::Table(numerical::Table::TableNaming naming) {
    this->rowNames = new std::vector<std::string>();
    this->columnNames = new std::vector<std::string>();
    this->rows = 0;
    this->columns = 0;
    this->naming = naming;
}

void numerical::Table::Out(std::ostream &stream, TableType type) {
    if (type == TableType::GNUPLOT_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS){
            WARNING("GNUplot table format isn't supporting rows naming. Skipping row names.")
        }
        if (naming == TableNaming::NAMED_ROWS){
            WARNING("GNUplot table format isn't supporting rows naming. Writing table without column names.")
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            stream << "# ";
            for (int i = 0; i < (*columnNames).size(); ++i) {
                stream << (*columnNames)[i];
                if (i != (*columnNames).size() - 1){
                    stream << "\t";
                }
            }
            stream << std::endl;
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                stream << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                if (j != columns - 1){
                    stream << "\t";
                }
            }
            stream << std::endl;
        }
    }

    if (type == TableType::TSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < (*columnNames).size(); ++i) {
                stream << (*columnNames)[i];
                if (i != (*columnNames).size() - 1){
                    stream << "\t";
                }
            }
            stream << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                stream << (*rowNames)[i] << "\t";
                for (int j = 0; j < columns; ++j) {
                    stream << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        stream << "\t";
                    }
                }
                stream << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    stream << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        stream << "\t";
                    }
                }
                stream << std::endl;
            }
        }
    }

    if (type == TableType::CSV_TABLE){
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_COLUMNS){
            for (int i = 0; i < (*columnNames).size(); ++i) {
                stream << (*columnNames)[i];
                if (i != (*columnNames).size() - 1){
                    stream << ",";
                }
            }
            stream << std::endl;
        }
        if(naming == TableNaming::NAMED_ROWS_AND_COLUMNS || naming == TableNaming::NAMED_ROWS){
            for (int i = 0; i < rows; ++i) {
                stream << (*rowNames)[i] << ",";
                for (int j = 0; j < columns; ++j) {
                    std::cout << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        std::cout << ",";
                    }
                }
                stream << std::endl;
            }
        } else {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    stream << std::fixed << std::setprecision(outputPrecision) << table[i][j];
                    if (j != columns - 1){
                        stream << ",";
                    }
                }
                stream << std::endl;
            }
        }
    }
    stream << std::endl;
}
