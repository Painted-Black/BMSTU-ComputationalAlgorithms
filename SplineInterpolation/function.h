#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <vector>

using namespace std;

class Function
{
    vector<double> mX;
    vector<double> mY;
    size_t mSize;
public:
    Function(double xStart, double xEnd, double step, double (func) (double x));
    void print();
    double splineInterpolation(double x);

private:
    size_t searchBinary(vector<double> vec, size_t left, size_t right, double x);
    vector<double> zeros(size_t size);
};

#endif // FUNCTION_H
