#include "inputhelper.h"

InputHelper::InputHelper()
{

}

unsigned int InputHelper::getUnsignedInt(string message)
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

double InputHelper::getDouble(string message)
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

int InputHelper::getInt(string message)
{
    int result = 0;
    string strRes;
    bool flag = false;

    cout << message;
    cin >> strRes;
    while (!flag) {
        try {
            result =  static_cast<int>(stoul(strRes, nullptr, 10));
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
