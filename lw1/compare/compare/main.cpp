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

bool OpenStream(ifstream & fileStream)
{
    if (!fileStream.is_open())
    {
        return false;
    }
    return true;
}

// возвращает номер строки
int isFilesEqual(ifstream & file1, ifstream & file2)
{
    char ch1, ch2;
    int lineCounter = 1;
    
    while (!file1.eof() && !file2.eof())
    {
        file1.get(ch1);
        file2.get(ch2);
        
        if (ch1 != ch2)
        {
            return lineCounter;
        }

        if (ch1 == '\n')
        {
            lineCounter++;
        }
    
    }
    
    if (!file1.eof() || !file2.eof())
    {
        return lineCounter;
    }
    
    return 0;

}

int main(int argc, char * argv[])
{
    
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
        << "Usage: program <input file1> <input file2>\n";
        return 1;
    }
    
    ifstream file1(argv[1]), file2(argv[2]);
    
    if (!OpenStream(file1))
    {
        cout << "Error reading file " << argv[1] << endl;
        return 1;
    }
    
    if (!OpenStream(file2))
    {
        cout << "Error reading file " << argv[2] << endl;
        return 1;
    }

    int isEqual = isFilesEqual(file1, file2);
    if (isEqual != 0)
    {
        cout << "Files are different. Line number is " << isEqual << endl;
        return 1;
    }
    
    cout << "Files are equal" << endl;
    
    return 0;
}