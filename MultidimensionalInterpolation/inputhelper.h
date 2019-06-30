#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <iostream>
#include <string>

using namespace std;

class InputHelper
{
public:
    InputHelper();

    unsigned int getUnsignedInt(string message);
    double getDouble(string message);
    int getInt(string message);
};

#endif // INPUTHELPER_H
