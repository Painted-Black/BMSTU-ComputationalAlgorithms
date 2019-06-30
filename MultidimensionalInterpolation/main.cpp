#include <iostream>
#include "twovariablesfunction.h"
#include "menu.h"
#include "inputhelper.h"

using namespace std;

void createUpperMenu();
void interpolate();
double func(double x, double y);
[[noreturn]] void finish();

int main()
{
    int a = 0;
    createUpperMenu();

    return 0;
}

double func(double x, double y)
{
    return x * x + y * y;
}

void finish()
{
    exit(0);
}

void createUpperMenu()
{
    Menu menu;
    menu.addTitle("Аппроксимация функций");
    menu.addAction(Action(interpolate, "Восстановление функции по ее дискретному ряду"));
    menu.addAction(Action(finish, "Выход"));
    menu.create();
    menu.inputAction();
}

void interpolate()
{
    //const string FILENAME = "/home/syzygy/MultidimensionalInterpolation/Database/xyz_table";

    InputHelper ih;

    double downX = ih.getDouble("Введите начальное значение x: ");
    double downY = ih.getDouble("Введите начальное значение y: ");
    double upX = ih.getDouble("Введите конечное значение x: ");
    double upY = ih.getDouble("Введите конечное значение y: ");
    double step = ih.getDouble("Введите шаг: ");

    //printf("RRR");
    TwoVariablesFunction table = TwoVariablesFunction(downX, downY, upX, upY, step, func);
    table.print();
    //cout << "RRR";

    double x = ih.getDouble("Введите значение x в пределах ["
                            + to_string(downX) + ", "
                            + to_string(upX)   + "]: ");
    double y = ih.getDouble("Введите значение y в пределах ["
                            + to_string(downY) + ", "
                            + to_string(upY)   + "]: ");

    int nx = ih.getInt("Введите nx: ");
    int ny = ih.getInt("Введите ny: ");


    double result = table.sequentialInterpolation(x, y, nx, ny);

    cout << "Результат: " << result << endl;
    cout << "Фактический результат: " << func(x, y) << endl;

    createUpperMenu();
}
