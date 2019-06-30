#include <iostream>
#include <math.h>
#include <string>
#include "filehelper.h"
#include "functiontable.h"
#include "menu.h"

using namespace std;

void createUpperMenu();
void interpolate();
void findRoots();
unsigned int getUnsignedInt(string message);
double getDouble(string message);
[[noreturn]] void exit();
double func(double x);

const double PI = 3.14;

int main()
{
    createUpperMenu();

    return 0;
}

void exit()
{
    exit(0);
}

void createUpperMenu()
{
    Menu menu;
    menu.addTitle("Аппроксимация функций");
    menu.addAction(Action(interpolate, "Восстановление функции по ее дискретному ряду"));
//    menu.addAction(Action("Нахождение корней функции"));
    menu.addAction(Action(exit, "Выход"));
    menu.create();
    menu.inputAction();
}


double func(double x)
{
//    return cos(PI / 2.0 * x);
//    return x * x;
    return cos(x) - x;
}

void interpolate()
{
    const string tablePath = "/home/syzygy/NewtonsPolynomialInterpolation/Database/cosx_table";

    filehelper f;

    FunctionTable table = f.readTable(tablePath);
    unsigned int n = getUnsignedInt("Введите степень полинома: ");
    double x = getDouble("Введите x: ");
    bool extrapolationFlag = false;
    bool error = false;
//    table.print();

    double result = table.interpolate(n, x, &extrapolationFlag, &error);
    if (error == true)
        cout << "Невозможно провести интерполяцию!" << endl;
    else
    {
        if (extrapolationFlag)
            cout << "Произошла экстраполяция!" << endl;
        cout << "Результат: " << result << endl;

        cout << "Точный результат: " << func(x) << endl;
    }


    createUpperMenu();
}

double getDouble(string message)
{
    double result = 0;
    bool flag = false;

    string buff;

    while (!flag) {
        cout << message;
        cin >> buff;
        try {
            result = stod(buff);
            flag = true;
        } catch (...) {
            cout << "Некорректный ввод!" << endl;
        }
    }
    return result;
}

void findRoots()
{

}

unsigned int getUnsignedInt(string message)
{
    unsigned int result = 0;
    string strRes;
    bool flag = false;

    cout << message;
    cin >> strRes;
    while (!flag) {
        try {
            result =  static_cast<unsigned int>(stoul(strRes, nullptr, 10));
            if (result == 0)
            {
                cout << "Нельзя ввести 0!" << endl;
                cout << message;
                cin >> strRes;
            }
            else
                flag = true;
        } catch (invalid_argument) {
            cout << "Некорректный ввод! Введите целое число." << endl;
            cout << message;
            cin >> strRes;
        }
    }
    return result;
}
