#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include "twovariablesfunction.h"

class filehelper
{
public:
    filehelper();

    TwoVariablesFunction *readTable(const string filename);

private:
    vector<string> split(string text, char split);
};

#endif // FILEHELPER_H
