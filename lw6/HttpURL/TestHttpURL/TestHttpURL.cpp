#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHttpURL

#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp>

#include "CHttpUrl.hpp"
#include "CUrlParsingError.hpp"

using namespace std;

bool VerifyURL(CHttpUrl url, string const& urlLink, Protocol protocol, string const& domain,
               std::string const& document, unsigned short port)
{
    if (urlLink.size() == 0)
    {
        BOOST_REQUIRE(url.GetProtocol() == protocol);
        BOOST_REQUIRE_EQUAL(url.GetDomain(), domain);
        BOOST_REQUIRE_EQUAL(url.GetDocument(), document);
        BOOST_REQUIRE_EQUAL(url.GetPort(), port);
    }
    else
    {
        BOOST_REQUIRE_EQUAL(url.GetURL(), urlLink);
    }

    return true;
}

bool VerifyExceptionMessage(std::string exceptionMessage, const boost::optional<std::string>& url,
                            const boost::optional<std::string>& domain, const boost::optional<std::string>& document,
                            const boost::optional<Protocol>& protocol, const boost::optional<unsigned>& port)
{
    try
    {
        if (url.is_initialized())
        {
            CHttpUrl httpUrl(*url);
        }
        else
        {
            CHttpUrl httpUrl(*domain, *document, *protocol, *port);
        }
    }
    catch(const CUrlParsingError& urlParsingError)
    {
        BOOST_REQUIRE_EQUAL(urlParsingError.what(), exceptionMessage);
        return true;
    }
    
    return false;
}

BOOST_AUTO_TEST_SUITE(http_url_suite)

    BOOST_AUTO_TEST_SUITE(test_init_by_link)

        BOOST_AUTO_TEST_CASE(no_valid_link)
        {
            /*
            BOOST_CHECK_THROW(CHttpUrl httpUrl(""), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("httrp://vk"), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("httrp://vk"), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("http://vk..."), CUrlParsingError);
             */
            
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_URL, std::string(""), {}, {}, {}, {}));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PROTOCOL, std::string("httpr://ya.ru"), {}, {}, {}, {}));
        }

        BOOST_AUTO_TEST_CASE(valid_link)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("http://vk1.com/"), "http://vk1.com/", Protocol::UNKNOWN, "", "", 0));
            BOOST_CHECK(VerifyURL(CHttpUrl("http://vk1.com/some/document.php"), "http://vk1.com/some/document.php", Protocol::UNKNOWN, "", "", 0));
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(test_init_by_params)

        BOOST_AUTO_TEST_CASE(no_valid_link)
        {
            /*
            BOOST_CHECK_THROW(CHttpUrl("", "", Protocol::HTTP, 0), CUrlParsingError);

            BOOST_CHECK_THROW(CHttpUrl("-site.ru", "", Protocol::HTTP, 0), CUrlParsingError);
            
            BOOST_CHECK_THROW(CHttpUrl("test", "some_document", Protocol::UNKNOWN, 0), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("test", "some_document", Protocol::HTTP, 80000), CUrlParsingError);
             */
            
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_DOMAIN, {}, std::string("si te.ru"), std::string(""), Protocol::HTTP, 0));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PROTOCOL, {}, std::string("site.ru"), std::string(""), Protocol::UNKNOWN, 0));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PORT, {}, std::string("site.ru"), std::string(""), Protocol::HTTP, 80000));
        }

        BOOST_AUTO_TEST_CASE(valid_link)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("vk.com", "feed", Protocol::HTTP, 80), "", Protocol::HTTP, "vk.com", "feed", 80));
            BOOST_CHECK(VerifyURL(CHttpUrl("yandex.ru", "", Protocol::HTTPS, 0), "", Protocol::HTTPS, "yandex.ru", "", 443));
        }

    BOOST_AUTO_TEST_SUITE_END()


    BOOST_AUTO_TEST_SUITE(test_url_protocol)

        BOOST_AUTO_TEST_CASE(no_valid_protocol)
        {
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PROTOCOL, {}, std::string("domain.ru"), std::string(""), Protocol::UNKNOWN, 0));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PROTOCOL, std::string("ftp://domain.ru"), {}, {}, {}, {}));
        }

        BOOST_AUTO_TEST_CASE(valid_protocol)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("vk.com", "feed", Protocol::HTTP, 80), "", Protocol::HTTP, "vk.com", "feed", 80));
            BOOST_CHECK(VerifyURL(CHttpUrl("yandex.ru", "", Protocol::HTTPS, 0), "", Protocol::HTTPS, "yandex.ru", "", 443));
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(test_url_domain)

        BOOST_AUTO_TEST_CASE(no_valid_domain)
        {
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_DOMAIN, std::string("http://string-"), {}, {}, {}, {}));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_DOMAIN, std::string("https://string test"), {}, {}, {}, {}));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_DOMAIN, std::string("https://string,test"), {}, {}, {}, {}));
        }

        BOOST_AUTO_TEST_CASE(valid_domain)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("site.ru", "", Protocol::HTTPS, 0), "", Protocol::HTTPS, "site.ru", "", 443));
            BOOST_CHECK(VerifyURL(CHttpUrl("localhost", "", Protocol::HTTP, 0), "", Protocol::HTTP, "localhost", "", 80));
            BOOST_CHECK(VerifyURL(CHttpUrl("localhost-site.com", "doc", Protocol::HTTP, 0), "", Protocol::HTTP, "localhost-site.com", "doc", 80));
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(test_url_port)

        BOOST_AUTO_TEST_CASE(no_valid_port)
        {
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PORT, std::string("http://test:8e0/"), {}, {}, {}, {}));
            BOOST_CHECK(VerifyExceptionMessage(ERROR_MESSAGE_INVALID_PORT, {}, std::string("ya.ru"), std::string(""), Protocol::HTTP, 70000));
        }

        BOOST_AUTO_TEST_CASE(valid_port)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("site.ru", "", Protocol::HTTP, 0), "", Protocol::HTTP, "site.ru", "", 80));
            BOOST_CHECK(VerifyURL(CHttpUrl("site.ru", "", Protocol::HTTPS, 0), "", Protocol::HTTPS, "site.ru", "", 443));
            BOOST_CHECK(VerifyURL(CHttpUrl("https://site.ru"), "", Protocol::HTTPS, "site.ru", "", 443));
            BOOST_CHECK(VerifyURL(CHttpUrl("http://site.ru:100/"), "", Protocol::HTTP, "site.ru", "", 100));
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
