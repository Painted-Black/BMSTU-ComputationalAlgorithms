#ifndef TWOVARIABLESFUNCTION_H
#define TWOVARIABLESFUNCTION_H

#include <iostream>
#include <vector>

using namespace std;

class TwoVariablesFunction
{
private:
    vector<double> mX;
    vector<double> mY;
    vector<vector<double>> mZ;
    size_t mSizeX;
    size_t mSizeY;
    size_t mSizeZ;
public:
    void print();
    TwoVariablesFunction(double downX, double downY, double upX, double upY, double step, double (func)(double x, double y));
    double sequentialInterpolation(double x, double y, int nx, int ny);
private:
    size_t searchBinary(vector<double> vec, size_t left, size_t right, double x);
    vector<double> cut(vector<double> vec, size_t start, size_t end);
    vector<vector<double>> cut(vector<vector<double>> vec, size_t start, size_t end);
    double newtonInterpolation(vector<double> listX, vector<double> listZ, double x);
    double dividedDifference(vector<double> xs, vector<double> ys);
    vector<int> choseDots(vector<double> a, int n, double x);
};

#endif // TWOVARIABLESFUNCTION_H
