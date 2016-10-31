#include <iostream>
#include <sstream>
#include <string>

#include "urlparser.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    Protocol urlProtocol;
    int urlPort;
    string urlHost, urlDocument;
    string inputURL;
    
    cout << "Input URL string's> ";
    
    while (cin >> inputURL)
    {
        if (ParseURL(inputURL, urlProtocol, urlPort, urlHost, urlDocument))
        {
            cout << inputURL << endl;
            cout << "HOST: " << urlHost << endl;
            cout << "PORT: " << urlPort << endl;
            cout << "DOC: " << urlDocument << endl;
        }
        else
        {
            cout << inputURL << " is wrong URL address!" << endl;
        }
    }

    return 0;
}

