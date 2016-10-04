#include "catch.hpp"
#include "htmlEncode.h"

TEST_CASE("Тестирование функции htmlEncode")
{
	SECTION("Тестирование пустой строки")
	{
		INFO("На входе пустая строка");
		string testEmptyStr = "";
		CAPTURE(testEmptyStr);
		
		CHECK(HtmlEncode(testEmptyStr) == testEmptyStr);
	}
	
    SECTION("Тестирование без html символов")
    {
        INFO("Без html символов");
        string testStrWithoutHtml = "Cat says Meow. M and Ms";
        CAPTURE(testStrWithoutHtml);
        
        CHECK(HtmlEncode(testStrWithoutHtml) == testStrWithoutHtml);
    }
	
	SECTION("Тестирование html символов")
	{
		INFO("C html символами");
		string testStrWithHtml = "Cat <says> \"Meow\". M&M's";
		string testStrResult = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		CAPTURE(testStrResult);
		
		CHECK(HtmlEncode(testStrWithHtml) == testStrResult);
	}

}
