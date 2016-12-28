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
            cout << "[+] " << httpURL.GetURL() << endl;
            cout << "Protocol: " << httpURL.GetStringProtocol() << endl;
            cout << "Domain: " << httpURL.GetDomain() << endl;
            cout << "Port: " << httpURL.GetPort() << endl;
            cout << "Document: " << httpURL.GetDocument() << endl;
        }
        catch (CUrlParsingError &e)
        {
            cout << "Ошибка ввода адреса URL: ";
            e.PrintInfo();
        }
    }
    
    return 0;
}
