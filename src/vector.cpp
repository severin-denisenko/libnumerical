//
// Created by Severin on 18.09.2022.
//
#include "vector.h"

namespace numerical
{

    Vector::Vector() = default;

    Vector::Vector(uint64_t size)
    {
        this->size = size;
        vector = new std::vector<double>(size);
        isAllocated = true;
    }

    Vector::Vector(const std::string &filename)
    {
        Read(filename);
        isAllocated = true;
    }

    Vector::Vector(const std::string &filename, uint64_t skip)
    {
        Read(filename, skip);
        isAllocated = true;
    }

    Vector::~Vector()
    {
        delete[] vector;
    }

    void Vector::Out(std::ostream &stream)
    {
        for (double d: *vector)
        {
            stream << d << std::endl;
        }
    }

    void Vector::Write(const std::string &filename)
    {
        std::streambuf *buf;
        std::ofstream of;
        of.open(filename);
        buf = of.rdbuf();
        std::ostream out(buf);

        Out(out);
    }

    void Vector::Print()
    {
        std::streambuf *buf;
        std::ofstream of;
        buf = std::cout.rdbuf();
        std::ostream out(buf);

        Out(out);
    }

    void Vector::Read(const std::string &filename)
    {
        std::ifstream file(filename);

        while (file.good())
        {
            double num;
            file >> num;
            vector->push_back(num);
        }

        file.close();
    }

    void Vector::Read(const std::string &filename, uint64_t skip)
    {
        std::ifstream file(filename);

        for (int i = 0; i < skip; ++i)
        {
            std::string line;
            std::getline(file, line);
        }

        for (double num; file >> num;)
        {
            vector->push_back(num);
        }

        file.close();
    }

}
