#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
    size_t  mRows;
    size_t  mColumns;
    double* mMatrix;
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    void setValue(size_t row, size_t col, double value);
    double getValue(size_t row, size_t col);
};

#endif // MATRIX_H
