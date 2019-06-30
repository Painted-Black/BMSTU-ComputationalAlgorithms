#include "functiontable.h"
#include <math.h>

vector<double> FunctionTable::getArguments() const
{
    return mArguments;
}

void FunctionTable::setArguments(const vector<double> &value)
{
    mArguments = value;
}

vector<double> FunctionTable::getValues() const
{
    return mValues;
}

void FunctionTable::setValues(const vector<double> &value)
{
    mValues = value;
}

unsigned int FunctionTable::getSize() const
{
    return mSize;
}

FunctionTable FunctionTable::getInterval(unsigned int l, double x, bool *extrpltFlag)
{
    FunctionTable result;
    *extrpltFlag = false;

    if (mSize >= l)
    {
        if (x <= mArguments.at(0))
        {
            *extrpltFlag = true;

            for (size_t i = 0; i < l; ++i)
                result.add(mArguments.at(i), mValues.at(i));
        }
        else if (x >= mArguments.at(mValues.size() - 1))
        {
            *extrpltFlag = true;

            for (size_t i = 0; i < l; ++i)
                result.add(mArguments.at(mArguments.size() - i - 1),
                           mValues.at(mArguments.size() - i - 1));
        }
        else
        {
            size_t idx = searchBinary(mArguments, 0, mSize, x);
            size_t up, down;
//            l--;
            if (l % 2 == 0)
            {
                up = l / 2;
                down = l / 2;
            }
            else
            {
                up = l / 2;
                down = l - up;
            }

            for (size_t i = idx; i < mSize; ++i)
            {
                result.add(mArguments.at(i), mValues.at(i));
                down--;
            }
            up += down;
            for (size_t i = idx - up; i < idx; i++)
            {
                result.add(mArguments.at(i), mValues.at(i));
                up--;
            }
        }
    }
    return result;
}

size_t FunctionTable::searchBinary(vector<double> vec, size_t left, size_t right, double x)
{
    size_t mid = 0;
    while (1) {
        mid = (left + right) / 2;
        if (x < vec.at(mid))
            right = mid - 1;
        else if (x > vec.at(mid))
            left = mid + 1;
        else
            return mid;
        if (left > right)
            return mid;
    }
}

void FunctionTable::add(double arg, double val)
{
    unsigned int i = 0;
    while (i < mArguments.size() && mArguments.size() > 0 && mArguments.at(i) < arg)
    {
        i++;
    }
    if (i != mArguments.size())
    {
        mArguments.insert(mArguments.begin() + i, arg);
        mValues.insert(mValues.begin() + i, val);
    }
    else
    {
        mArguments.push_back(arg);
        mValues.push_back(val);
    }
    mSize++;
}

void FunctionTable::print()
{
    for (size_t i = 0; i < mSize; ++i)
        cout << mArguments[i] << "\t\t" << mValues[i] << endl;
}

double FunctionTable::getValue(size_t idx)
{
    return mValues.at(idx);
}

double FunctionTable::getArgument(size_t idx)
{
    return mArguments.at(idx);
}

vector<vector<double>> FunctionTable::getDivDiff(FunctionTable table)
{
    vector<vector<double>> result;
    vector<double> newVec;
    for(size_t j = 1; j < table.getSize(); ++j)
    {
        double currentVal = (table.getValue(j - 1) - table.getValue(j)) /
                            (table.getArgument(j - 1) - table.getArgument(j));
        newVec.push_back(currentVal);
    }
    result.push_back(newVec);
    newVec.clear();

    for (size_t k = 0; k < table.getSize() - 2; k++)
    {
        for (size_t i = 1; i < result[k].size(); ++i)
        {
//            cout << result[k].at(i - 1)  << "  "
//                 << result[k].at(i) << "  "
//                 << table.getArgument(0) - table.getArgument(i) << endl;
            double currentVal = (result[k].at(i - 1) - result[k].at(i)) /
                                (table.getArgument(0) - table.getArgument(k + 2));
            newVec.push_back(currentVal);
        }
        result.push_back(newVec);
        newVec.clear();
    }
    return result;
}

double FunctionTable::interpolate(unsigned int n, double x, bool *flag, bool *error)
{
    bool extrpltFlag = false;
    FunctionTable interval = getInterval(n + 1, x, &extrpltFlag);
    *flag = extrpltFlag;
    double polynome = 0;

    if (interval.getSize() == 0)
    {
        *error = true;
    }
    else
    {
        polynome = interval.getValue(0);
        vector<vector<double>> divDiff = getDivDiff(interval);
        for (size_t k = 0; k < n; ++k)
        {
            double dec = divDiff.at(k).at(0);
            double factor = 1;
            for (size_t j = 0; j < k + 1; ++j)
            {
                factor *= (x - interval.getArgument(j));
            }
            dec *= factor;
            polynome += dec;
        }
    }
    return polynome;
}


