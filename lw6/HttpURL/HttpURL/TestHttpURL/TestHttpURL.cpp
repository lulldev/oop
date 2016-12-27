#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHttpURL

#include <boost/test/unit_test.hpp>

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

BOOST_AUTO_TEST_SUITE(http_url_suite)

    BOOST_AUTO_TEST_SUITE(test_init_by_link)

        BOOST_AUTO_TEST_CASE(no_valid_link)
        {
            BOOST_CHECK_THROW(CHttpUrl httpUrl(""), CUrlParsingError);
            
            BOOST_CHECK_THROW(CHttpUrl("httrp://vk"), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("httrp://vk"), ErrorInvalidProtocol);

            BOOST_CHECK_THROW(CHttpUrl("http://vk..."), CUrlParsingError);
            
        }

        BOOST_AUTO_TEST_CASE(valid_link)
        {
            BOOST_CHECK(VerifyURL(CHttpUrl("http://vk1.com/"), "http://vk1.com/", Protocol::UNKNOW, "", "", 0));
            BOOST_CHECK(VerifyURL(CHttpUrl("http://vk1.com/some/document.php"), "http://vk1.com/some/document.php", Protocol::UNKNOW, "", "", 0));
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(test_init_by_params)

        BOOST_AUTO_TEST_CASE(no_valid_link)
        {
            BOOST_CHECK_THROW(CHttpUrl("", "", Protocol::HTTP, 0), CUrlParsingError);
            BOOST_CHECK_THROW(CHttpUrl("", "", Protocol::HTTP, 0), ErrorInvalidDomain);

            BOOST_CHECK_THROW(CHttpUrl("-site.ru", "", Protocol::HTTP, 0), ErrorInvalidDomain);
            
            BOOST_CHECK_THROW(CHttpUrl("test", "some_document", Protocol::UNKNOW, 0), ErrorInvalidProtocol);
            BOOST_CHECK_THROW(CHttpUrl("test", "some_document", Protocol::HTTP, 80000), ErrorInvalidPort);
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
            BOOST_CHECK_THROW(CHttpUrl("domain.ru", "", Protocol::UNKNOW, 0), ErrorInvalidProtocol);
            BOOST_CHECK_THROW(CHttpUrl("ftp://domain.ru"), ErrorInvalidProtocol);
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
            BOOST_CHECK_THROW(CHttpUrl("http://"), CUrlParsingError);
            
            BOOST_CHECK_THROW(CHttpUrl("", "", Protocol::HTTP, 0), ErrorInvalidDomain);
            BOOST_CHECK_THROW(CHttpUrl("string-", "", Protocol::HTTP, 0), ErrorInvalidDomain);
            BOOST_CHECK_THROW(CHttpUrl("string domain", "test", Protocol::HTTP, 0), ErrorInvalidDomain);
            BOOST_CHECK_THROW(CHttpUrl("string,domain", "test", Protocol::HTTP, 0), ErrorInvalidDomain);
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
            BOOST_CHECK_THROW(CHttpUrl("http://test:8e0/"), ErrorInvalidPort);
            BOOST_CHECK_THROW(CHttpUrl("vk.com", "", Protocol::HTTP, 70000), ErrorInvalidPort);
            //todo add more
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
