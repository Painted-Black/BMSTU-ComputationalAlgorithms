#include <iostream>
#include <math.h>
#include "inputhelper.h"
#include "function.h"
#include "menu.h"

using namespace std;

const double PI = 3.14;

double func(double x);
void createUpperMenu();
void interpolate();
[[noreturn]] void finish();

int main()
{
    createUpperMenu();

    return 0;
}

double func(double x)
{
    return x * x;
}

void createUpperMenu()
{
    Menu menu;
    menu.addTitle("Интерполяция сплайнами");
    menu.addAction(Action(interpolate, "Интерполяция"));
    menu.addAction(Action(finish, "Выход"));
    menu.create();
    menu.inputAction();
}


void interpolate()
{
    InputHelper ih;
    double startX = ih.getDouble("Введите начальное значение x: ");
    double endX   = ih.getDouble("Введите конечное значение x: ");
    double step   = ih.getDouble("Введите шаг: ");

    Function function = Function(startX, endX, step, func);

    cout << "Сгенерированная таблица: " << endl;
    function.print();
    cout << endl;

    double x = ih.getDouble("Введите x в пределах [" +
                            to_string(startX) + ", " +
                            to_string(endX)   + "]: ");

    double result = function.splineInterpolation(x);

    cout << "Результат: " << result << endl;
    cout << "Точный результат: " << func(x) << endl;

    createUpperMenu();
}

void finish()
{
    exit(0);
}
