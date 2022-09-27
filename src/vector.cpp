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

    double &Vector::operator()(int64_t i)
    {
        if (i > size || i < 1){
            FATAL("Vector out of borders.");
        }

        return vector->at(i - 1);
    }

    const double &Vector::operator()(int64_t i) const
    {
        if (i > size || i < 1){
            FATAL("Vector out of borders.");
        }

        return vector->at(i - 1);
    }

    uint64_t Vector::Size() const
    {
        return size;
    }

    double Vector::operator*(const Vector &other)
    {
        if (this->size != other.size){
            FATAL("Can't multiply vectors different length");
        }

        double res = 0;

        for (int i = 1; i <= size; ++i)
        {
            res += (*this)(i) * other(i);
        }

        return res;
    }

    Vector &Vector::operator+=(const Vector &other)
    {
        if (this->size != other.size){
            FATAL("Can't add vectors different length");
        }

        for (int i = 0; i < size; ++i)
        {
            (*this)(i) += other(i);
        }

        return (*this);
    }

    Vector &Vector::operator-=(const Vector &other)
    {
        if (this->size != other.size){
            FATAL("Can't subtract vectors different length");
        }

        for (int i = 0; i < size; ++i)
        {
            (*this)(i) -= other(i);
        }

        return (*this);
    }

    Vector &Vector::operator+(const Vector &other)
    {
        if (this->size != other.size){
            FATAL("Can't add vectors different length");
        }

        auto *res = new Vector(size);

        for (int i = 0; i < size; ++i)
        {
            (*res)(i) = (*this)(i) + other(i);
        }

        return (*res);
    }

    Vector &Vector::operator-(const Vector &other)
    {
        if (this->size != other.size){
            FATAL("Can't subtract vectors different length");
        }

        auto *res = new Vector(size);

        for (int i = 0; i < size; ++i)
        {
            (*res)(i) = (*this)(i) - other(i);
        }

        return (*res);
    }

    Vector &Vector::operator/(const Vector &other)
    {
        auto *res = new Vector(size);

        if (this->size != other.size){
            FATAL("Can't multiply vectors different length");
        }

        switch (size)
        {
            case 3:
                (*res)(1) = (*this)(2) * other(3) - (*this)(3) * other(2);
                (*res)(2) = - (*this)(1) * other(3) + (*this)(3) * other(1);
                (*res)(2) = (*this)(1) * other(2) - (*this)(2) * other(1);
                break;
            case 7:
                //TODO
                FATAL("Not yet implemented.");
                break;
            default:
                FATAL("Can't perform cross product in other then 3 and 7 dimensions.");
        }

        return *res;
    }

}
