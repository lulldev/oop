#include <iostream>

#include "CHttpUrl.hpp"
#include "CUrlParsingError.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    string inputURL;
    
    cout << "Введите адреса URL:";
    while(getline(cin, inputURL))
    {
        try
        {
            CHttpUrl httpURL(inputURL);
            cout << "[+] " << inputURL << endl;
        }
        catch (CUrlParsingError &e)
        {
            cout << "Ошибка ввода адреса URL: ";
            e.PrintInfo();
        }
    }
    
    return 0;
}
