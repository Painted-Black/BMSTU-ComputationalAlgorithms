#include "function.h"

Function::Function(double xStart, double xEnd, double step, double func(double x))
    : mSize(0)
{
    for (double i = xStart; i < xEnd; i += step)
    {
        mX.push_back(i);
        mY.push_back(func(i));
        mSize++;
    }
}

void Function::print()
{
    for (size_t i = 0; i < mSize; ++i)
        cout << mX.at(i) << "\t" << mY.at(i) << endl;
}

double Function::splineInterpolation(double x)
{
    size_t i_near = searchBinary(mX, 0, mSize, x);

    vector<double> h = zeros(mSize);
    vector<double> A = zeros(mSize);
    vector<double> B = zeros(mSize);
    vector<double> D = zeros(mSize);
    vector<double> F = zeros(mSize);

    vector<double> a = zeros(mSize);
    vector<double> b = zeros(mSize);
    vector<double> c = zeros(mSize + 1);
    vector<double> d = zeros(mSize);

    vector<double> ksi = zeros(mSize + 1);
    vector<double> eta = zeros(mSize + 1);

    for (size_t i = 1; i < h.size(); ++i)
        h.at(i) = mX.at(i) - mX.at(i - 1);

    for (size_t i = 2; i < A.size(); ++i)
    {
        A.at(i) = h[i - 1];
        B.at(i) = -2 * (h[i - 1] + h[i]);
        D.at(i) = h[i];
        F.at(i) = -3 * ((mY.at(i) - mY.at(i - 1) / h.at(i) - (mY.at(i - 1) - mY.at(i - 2)) / h.at(i - 1)));
    }

    for (size_t i = 2; i < mSize; ++i)
    {
        ksi.at(i + 1) = D.at(i) / (B.at(i) - A.at(i) * ksi.at(i));
        eta.at(i + 1) = (A.at(i) * eta.at(i) + F.at(i)) / (B.at(i) - A.at(i) * ksi.at(i));
    }

    for (int i = mSize - 2; i > -1; --i)
        c.at(i) = ksi.at(i + 1) * c.at(i + 1) + eta.at(i + 1);

    for (size_t i = 1; i < mSize; ++i)
    {
        a.at(i) = mY.at(i - 1);
        b.at(i) = (mY.at(i) - mY.at(i - 1)) / h.at(i) - h.at(i) / 3 * (c.at(i + 1) + 2 * c.at(i));
        d.at(i) = (c.at(i + 1) - c.at(i)) / (3 * h.at(i));
    }

    double result;
    result = a.at(i_near) + b.at(i_near) * (x - mX.at(i_near - 1)) +
            c.at(i_near) * ((x - mX.at(i_near - 1)) * (x - mX.at(i_near - 1))) +
            d.at(i_near) * ((x - mX.at(i_near - 1)) * (x - mX.at(i_near - 1)) * (x - mX.at(i_near - 1)));
    return result;
}

size_t Function::searchBinary(vector<double> vec, size_t left, size_t right, double x)
{
    int a = 0;
    int b = vec.size() - 1;

    while (a < b)
    {
        int m = (a + b) / 2;
        if (x > vec.at(m))
            a = m + 1;
        else
            b = m;
    }
    return b;
}

vector<double> Function::zeros(size_t size)
{
    vector<double> result;
    for (size_t i = 0; i < size; ++i)
    {
        result.push_back(0.0);
    }
    return result;
}
