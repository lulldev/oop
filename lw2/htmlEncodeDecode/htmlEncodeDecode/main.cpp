#include <algorithm>
#include <iostream>
#include <stdio.h>

#define ESC_KEY_CODE 27

using namespace std;

string HtmlEncode(const string & text)
{
    string encodeText;
    for (char ch : text)
    {
        switch (ch)
        {
            case '\"':
                encodeText += "&quot;";
                break;
            case '\'':
                encodeText += "&apos;";
                break;
            case '<':
                encodeText += "&lt;";
                break;
            case '>':
                encodeText += "&gt;";
                break;
            case '&':
                encodeText += "&amp;";
                break;
            default:
                encodeText += ch;
                break;
        }
    }
    return encodeText;
}

// todo
string HtmlDecode(const string & text)
{
    return "";
}

int main(int argc, const char * argv[])
{
    string fileLine, encodeText;
    char ch = NULL;
    size_t i;

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