#include <regex>
#include <string>

enum class Protocol {
    FTP,
    HTTP,
    HTTPS,
    Undifened
};

bool ParseURL(std::string const & url, Protocol & protocol, int & port, std::string & host, std::string & document);
