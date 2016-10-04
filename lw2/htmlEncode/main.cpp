#include <iostream>
#include "htmlEncode.h"

#define ESC_KEY_CODE 27

using namespace std;

int main(int argc, const char * argv[])
{
    string fileLine, encodeText;
    char ch = NULL;

    cout << "Введите текст для кодирования тегов HTML: " << endl;
    while (ch != ESC_KEY_CODE)
    {
        ch = cin.get();
        fileLine += ch;
        if (ch == '\n')
        {
            encodeText += HtmlEncode(fileLine);
            fileLine = "";
        }
    }

    cout << "Закодированный текст:" << endl;
    cout << encodeText << endl;

    return 0;
}
