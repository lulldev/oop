#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ParseURL

#include <boost/test/unit_test.hpp>

#include "urlparser.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParseURLSuite)

Protocol urlProtocol;
int urlPort;
string urlAddress, urlHost, urlDocument;
bool testURLFlag;

BOOST_AUTO_TEST_CASE(WrongData)
{
    testURLFlag = ParseURL("", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("http://", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("http://test.ru:d/", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("http://test.ru:", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("http://:", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("tttp://test.ru", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag != true);
    testURLFlag = ParseURL("HTTP://test.ru", urlProtocol, urlPort, urlHost, urlDocument);
    BOOST_CHECK(testURLFlag == true);
}

BOOST_AUTO_TEST_CASE(HttpAddressTesting)
{
    urlAddress = "http://vk.com/";
    
    testURLFlag = ParseURL(urlAddress, urlProtocol, urlPort, urlHost, urlDocument);

    BOOST_REQUIRE(testURLFlag == true);
    BOOST_CHECK(urlProtocol == Protocol::HTTP);
    BOOST_CHECK(urlPort == 80);
    BOOST_CHECK(urlHost == "vk.com");
}

BOOST_AUTO_TEST_CASE(HttpsAddressTesting)
{
    urlAddress = "https://vk.com/document";
    
    testURLFlag = ParseURL(urlAddress, urlProtocol, urlPort, urlHost, urlDocument);
    
    BOOST_REQUIRE(testURLFlag == true);
    BOOST_CHECK(urlProtocol == Protocol::HTTPS);
    BOOST_CHECK(urlPort == 443);
    BOOST_CHECK(urlHost == "vk.com");
    BOOST_CHECK(urlDocument == "/document");
}

BOOST_AUTO_TEST_CASE(FtpAddressTesting)
{
    urlAddress = "ftp://yandex.ru";
    
    testURLFlag = ParseURL(urlAddress, urlProtocol, urlPort, urlHost, urlDocument);
    
    BOOST_REQUIRE(testURLFlag == true);
    BOOST_CHECK(urlProtocol == Protocol::FTP);
    BOOST_CHECK(urlPort == 21);
    BOOST_CHECK(urlHost == "yandex.ru");
}

BOOST_AUTO_TEST_CASE(AnyPortTesting)
{
    urlAddress = "http://yandex.ru:8080/document1/#title";
    
    testURLFlag = ParseURL(urlAddress, urlProtocol, urlPort, urlHost, urlDocument);
    
    BOOST_REQUIRE(testURLFlag == true);
    BOOST_CHECK(urlProtocol == Protocol::HTTP);
    BOOST_CHECK(urlPort == 8080);
    BOOST_CHECK(urlHost == "yandex.ru");
    BOOST_CHECK(urlDocument == "/document1/#title");
}

BOOST_AUTO_TEST_SUITE_END()
