/*
 Лабораторная работа №1
 Задание №2., Вариант №1 - Программа calcbits (20 баллов)
 Работу выполнил: студент группы ПС-22 Калагин И.В.
*/

#include <iostream>

using namespace std;

int calcbits(int byte)
{
    int bitsCount = 0;
    int i = 0;
    
    while (i < 32)
    {
        bitsCount += byte & 1;
        byte = byte >> 1;
        i++;
    }

    return bitsCount;
}

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\nUsage: calcbits <number>\n";
        return 1;
    }

    if (!isdigit(*argv[1]))
    {
        cout << "Parameter must be integer!" << endl;
        return 1;
    }

    int number = atoi(argv[1]);

    cout << calcbits(number) << endl;
    
    return 0;
}