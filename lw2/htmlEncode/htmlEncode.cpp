#include "htmlEncode.h"

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
