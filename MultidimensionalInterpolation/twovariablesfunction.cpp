#include "twovariablesfunction.h"
#include <math.h>

TwoVariablesFunction::TwoVariablesFunction(double downX, double downY, double upX, double upY, double step, double func(double, double))
{
    mSizeX = 0;
    mSizeY = 0;
    mSizeZ = 0;
    for (double i = downX; i <= upX; i += step)
    {
        mX.push_back(i);
        mSizeX++;
    }

    for (double i = downY; i <= upY; i += step)
    {
        mY.push_back(i);
        mSizeY++;
    }

    for (double i = downX; i <= upX; i += step)
    {
        vector<double> tmp;
        for (double j = downY; j <= upY; j += step)
        {
            tmp.push_back(func(i, j));
        }
        mZ.push_back(tmp);
        mSizeZ++;
    }

}

double TwoVariablesFunction::sequentialInterpolation(double x, double y, int nx, int ny)
{
    vector<int> pos;
    int ix_beg, ix_end, iy_beg, iy_end;

    pos = choseDots(mX, nx + 1, x);
    ix_beg = pos.at(0);
    ix_end = pos.at(1);

    pos = choseDots(mY, ny + 1, y);
    iy_beg = pos.at(0);
    iy_end = pos.at(1);

    vector<double> newX = cut(mX, ix_beg, ix_end);
    vector<double> newY = cut(mY, iy_beg, iy_end);
    vector<vector<double>> newZ = cut(mZ, iy_beg, iy_end);

    for (size_t i = 0; i < ny + 1; ++i)
        newZ.at(i) = cut(newZ.at(i), ix_beg, ix_end);

    vector<double> answer;

    for (size_t i = 0; i < newY.size(); ++i)
    {
        answer.push_back(newtonInterpolation(newX, newZ[i], x));
    }

    return newtonInterpolation(newY, answer, y);

    //    int i_x = searchBinary(mX, 0, mSizeX, x);
//    int i_y = searchBinary(mY, 0, mSizeY, y);

//    vector<double> sampleX, sampleY;
//    vector<vector<double>> sampleZ;

//    if (i_y - (ny + 1) / 2.0 <= 0) // х в начале
//    {
//        sampleY = cut(mY, 0, i_y + ceil((ny + 1) / 2) + 1);
//        sampleZ = cut(mZ, 0, i_y + ceil((ny + 1) / 2) + 1);
//    }
//    else if (mSizeY <= i_y + (ny + 1) / 2.0) // х вконце
//    {
//        sampleY = cut(mY, i_y - ceil((ny + 1) / 2), mSizeY);
//        sampleZ = cut(mZ, i_y - ceil((ny + 1) / 2), mSizeZ);
//    }
//    else
//    {
//        if (ny % 2 != 0)
//        {
////            cout << i_y - ceil((ny + 1) / 2) << "  " << i_y + ceil((ny + 1) / 2) << endl;
//            sampleY = cut(mY, i_y - ceil((ny + 1) / 2), i_y + ceil((ny + 1) / 2));
//            sampleZ = cut(mZ, i_y - ceil((ny + 1) / 2), i_y + ceil((ny + 1) / 2));
//        }
//        else
//        {
//            sampleY = cut(mY, i_y - ceil((ny + 1) / 2) - 1, i_y + ceil((ny + 1) / 2));
//            sampleZ = cut(mZ, i_y - ceil((ny + 1) / 2) - 1, i_y + ceil((ny + 1) / 2));
//        }
//    }

//    size_t left = 0, right = 0;

//    if (i_x - (nx + 1) / 2 < 0) // х вначале
//    {
//        sampleX = cut(mX, 0, i_x + ceil((nx + 1) / 2) + 1);
//        right = static_cast<size_t>(i_x + ceil((nx + 1) / 2) + 1);
//    }
//    else if (mSizeX < i_x + (nx + 1) / 2) // х вконце
//    {
//        sampleX = cut(mX, i_x - ceil((nx + 1) / 2), mSizeX);
//        left = static_cast<size_t>(i_x - ceil((nx + 1) / 2));
//    }
//    else
//    {
//        if (nx % 2 != 0)
//        {
//            sampleX = cut(mX, i_x - ceil((nx + 1) / 2), i_x + ceil((nx + 1) / 2));
//            left = static_cast<size_t>(i_x - ceil((nx + 1) / 2));
//            right = static_cast<size_t>(i_x + ceil((nx + 1) / 2));
//        }
//        else
//        {
//            sampleX = cut(mX, i_x - ceil((nx + 1) / 2) - 1, i_x + ceil((nx + 1) / 2));
//            left = static_cast<size_t>(i_x - ceil((nx + 1) / 2) - 1);
//            right = static_cast<size_t>(i_x + ceil((nx + 1) / 2));
//        }
//    }

//    for (size_t i = 0; i < sampleZ.size(); ++i)
//    {
//        sampleZ[i] = cut(sampleZ[i], left, right);
//    }

//    vector<double> answer;

//    for (size_t i = 0; i < sampleY.size(); ++i)
//    {
//        answer.push_back(newtonInterpolation(sampleX, sampleZ[i], x));
//    }

//    return newtonInterpolation(sampleY, answer, y);
}

size_t TwoVariablesFunction::searchBinary(vector<double> vec, size_t left, size_t right, double x)
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

vector<double> TwoVariablesFunction::cut(vector<double> vec, size_t start, size_t end)
{
    vector<double> result;
    for (size_t i = start; i < end; ++i)
        result.push_back(vec.at(i));
    return result;
}

vector<vector<double> > TwoVariablesFunction::cut(vector<vector<double>> vec, size_t start, size_t end)
{
    vector<vector<double>> result;
    for (size_t i = start; i < end; ++i)
        result.push_back(vec.at(i));
    return result;
}

double TwoVariablesFunction::newtonInterpolation(vector<double> listX, vector<double> listZ, double x)
{
//    for (size_t i = 0; i < listX.size(); ++i)
//        cout << listX.at(i) << "  ";
    size_t i = searchBinary(listX, 0, listX.size(), x);
    double zX = listZ.at(0);
    for (size_t i = 1; i < listX.size(); ++i)
    {
        double k = 1;
        for (size_t j = 0; j < i; ++j)
            k *= (x - listX[j]);
//        cout << k << endl;
//        vector<double> c = cut(listX, 0, i + 1);
//        for (size_t i = 0; i < c.size(); ++i)
//            cout << c.at(i) << "  ";
        double dd = dividedDifference(cut(listX, 0, i + 1),
                                      cut(listZ, 0, i + 1));
//        cout << dd << endl;
        zX += (k * dd);
    }
    return zX;
}

double TwoVariablesFunction::dividedDifference(vector<double> xs, vector<double> ys)
{
    size_t l = xs.size();

    if (l == 1)
        return ys.at(0);
    else
        return (dividedDifference(cut(xs, 0, xs.size() - 1), cut(ys, 0, ys.size() - 1)) -
                dividedDifference(cut(xs, 1, xs.size()),
                                  cut(ys, 1, ys.size()))) /
                (xs[0] - xs[l - 1]);
}

vector<int> TwoVariablesFunction::choseDots(vector<double> a, int n, double x)
{
    vector<int> res;
    int a_len = a.size();
    int i_near = searchBinary(a, 0, a_len, x);
    //if (x - a.at(i_near - 1) < 0.5)
      //  i_near--;

    int space_needed = ceil(n / 2);
    int i_end, i_start;

    if (i_near + space_needed +  1 > a_len)
    {
        i_end = a_len;
        i_start = a_len - n;
    }
    else if (i_near < space_needed)
    {
        i_start = 0;
        i_end = n;
    }
    else
    {
        i_start = i_near - space_needed;
        i_end = i_start + n + 1;
    }
    res.push_back(i_start);
    res.push_back(i_end);
    return res;
}

void TwoVariablesFunction::print()
{
    //cout << "X" << "\t\t" << "Y" << "\t\t" << "Z" << endl;
    //size_t iz = 0, jz = 0;
    for (size_t i = 0; i < mSizeZ; ++i)
    {
        for (size_t j = 0; j < mZ.at(i).size(); ++j)
        {
            cout << mZ.at(i).at(j) << "\t\t";
        }
        cout << endl;
    }
}
