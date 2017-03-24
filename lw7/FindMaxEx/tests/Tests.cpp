#include "Tests.h"

using testing::Eq;
using namespace std;

/* Для чисел */

struct CFindMaxExNumberFixture: public ::testing::Test
{
public:
    std::vector<int> numbersVector;
    int maxNumber = 0;
};

TEST_F(CFindMaxExNumberFixture, FindMaxInEmptyVector)
{
    ASSERT_FALSE(FindMaxEx(numbersVector, maxNumber, less<int>()));
    ASSERT_EQ(maxNumber, 0);
}

TEST_F(CFindMaxExNumberFixture, FindMaxWithOneValuesInVector)
{
    numbersVector.push_back(2);
    ASSERT_TRUE(FindMaxEx(numbersVector, maxNumber, less<int>()));
    ASSERT_EQ(maxNumber, 2);
}

TEST_F(CFindMaxExNumberFixture, FindMaxWithManyValuesInVector)
{
    numbersVector.push_back(3);
    numbersVector.push_back(-2);
    numbersVector.push_back(1);

    ASSERT_TRUE(FindMaxEx(numbersVector, maxNumber, less<int>()));
    ASSERT_EQ(maxNumber, 3);
}

/* Для строк */

struct CFindMaxExStringFixture: public ::testing::Test
{
public:
    std::vector<string> stringVector;
    std::string maxString;
};

TEST_F(CFindMaxExStringFixture, FindMaxInEmptyVector)
{
    ASSERT_FALSE(FindMaxEx(stringVector, maxString, less<string>()));
    ASSERT_TRUE(maxString.empty());
}

TEST_F(CFindMaxExStringFixture, FindMaxWithOneValuesInVector)
{
    stringVector.push_back("one");
    ASSERT_TRUE(FindMaxEx(stringVector, maxString, less<string>()));
    ASSERT_EQ(maxString, "one");
}

TEST_F(CFindMaxExStringFixture, FindMaxWithManyValuesInVector)
{
    stringVector.push_back("one");
    stringVector.push_back("two");
    stringVector.push_back("wou");

    ASSERT_TRUE(FindMaxEx(stringVector, maxString, less<string>()));
    ASSERT_EQ(maxString, "wou");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}