#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <iostream>
#include <vector>

using namespace std;

class FunctionTable
{
    vector<double> mArguments; // x
    vector<double> mValues;    // y
    unsigned int mSize;
public:
    FunctionTable() { mSize = 0; }

    void add(double arg, double val);

    void print();
    double interpolate(unsigned int n, double x, bool *flag, bool *errror);
    vector<double> getArguments() const;
    void setArguments(const vector<double> &value);
    vector<double> getValues() const;
    void setValues(const vector<double> &value);
    unsigned int getSize() const;
    vector<vector<double>> getDivDiff(FunctionTable table);
    double getValue(size_t idx);
    double getArgument(size_t idx);

private:
    FunctionTable getInterval(unsigned int l, double x, bool *extrpltFlag);
    size_t searchBinary(vector<double> vec, size_t left, size_t right, double x);
};

#endif // FUNCTIONTABLE_H
