#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(size_t rows, size_t cols)
{
    mMatrix = new double [rows * cols];
    mRows = rows;
    mColumns = cols;
    for (size_t i = 0; i < mRows; ++i)
        for (size_t j = 0; j < mColumns; ++j)
            mMatrix[i * mRows + j] = 0;
}

Matrix::~Matrix()
{
//    delete [] mMatrix;
}

void Matrix::setValue(size_t row, size_t col, double value)
{/*
    cout << "IDX  " << row * mRows + col << endl;
    cout << mRows << "  " << mColumns << endl;*/
    mMatrix[row * mRows + col] = value;
}

double Matrix::getValue(size_t row, size_t col)
{
    return mMatrix[row * mRows + col];
}
