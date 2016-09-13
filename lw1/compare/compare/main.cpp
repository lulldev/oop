/*
 Лабораторная работа №1
 Задание №1., Вариант №2 - Программа compare (40 баллов)
 Работу выполнил: студент группы ПС-22 Калагин И.В.
 
 Для тестирования программы используется утилита diff (mac os terminal)
 Usage on terminal: diff -u <input file1> <input file2>
 */

// Note: /Users/lull/Library/Developer/Xcode/DerivedData/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
        << "Usage: program <input file1> <input file2>\n";
        return 1;
    }
    
    ifstream file1(argv[1]);
    
    if (!file1.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }
    
    ifstream file2(argv[2]);
    
    if (!file2.is_open())
    {
        cout << "Failed to open " << argv[2] << " for reading\n";
        return 1;
    }
    
    char ch1, ch2;
    int lineCounter1 = 0, lineCounter2 = 0;
    
    while (!file1.eof())
    {
        file1.get(ch1);
        file2.get(ch2);
        
        if (ch1 != ch2)
        {
            if (lineCounter1 >= lineCounter2)
            {
                cout << "Files are different. Line number is " << lineCounter1 << "\n";
            }
            else
            {
                cout << "Files are different. Line number is " << lineCounter2 << "\n";
            }
            return 1;
        }
        
        if (ch1 == '\n')
        {
            lineCounter1++;
        }
        
        if (ch2 == '\n')
        {
            lineCounter2++;
        }
    }
    
    cout << "Files are equal" << endl;
    
    
    return 0;
}