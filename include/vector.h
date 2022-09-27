//
// Created by Severin on 18.09.2022.
//

#ifndef LIBNUMERICAL_VECTOR_H
#define LIBNUMERICAL_VECTOR_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>
#include "logger.h"

namespace numerical{
    class Vector{
    public:

        // Create new vector for read
        Vector();

        // Create new empty vector
        explicit Vector(uint64_t size);

        // Read from file
        explicit Vector(const std::string& filename);

        // Read from file skipping rows
        Vector(const std::string& filename, uint64_t skip);
        ~Vector();

        void Read(const std::string& filename);
        void Read(const std::string& filename, uint64_t skip);

        void Write(const std::string& filename);
        void Print();
        void Out(std::ostream &stream);

        // Basic arithmetics
        Vector& operator +=(const Vector& other);
        Vector& operator -=(const Vector& other);
        Vector& operator +(const Vector& other);
        Vector& operator -(const Vector& other);

        // Dot product
        double operator *(const Vector& other);

        // Cross product
        Vector& operator /(const Vector& other);

        double& operator() (int64_t i);
        const double& operator () (int64_t i) const;

        uint64_t Size() const;
    private:
        std::vector<double> *vector;
        uint64_t size;
        bool isAllocated = false;
    };
}

#endif //LIBNUMERICAL_VECTOR_H
