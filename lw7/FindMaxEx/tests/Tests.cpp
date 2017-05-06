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

TEST_F(CFindMaxExNumberFixture, FindMaxInEmptyVectorNoThrow)
{
    ASSERT_FALSE(FindMaxEx(numbersVector, maxNumber, less<int>()));
}

TEST_F(CFindMaxExNumberFixture, FindMaxInEmptyVectorReturnZero)
{
    FindMaxEx(numbersVector, maxNumber, less<int>());
    ASSERT_EQ(maxNumber, 0);
}

TEST_F(CFindMaxExNumberFixture, FindMaxInVectorWithOneValuesReturnThisElement)
{
    numbersVector.push_back(2);
    ASSERT_TRUE(FindMaxEx(numbersVector, maxNumber, less<int>()));
    ASSERT_EQ(maxNumber, 2);
}

TEST_F(CFindMaxExNumberFixture, FindMaxWithManyValuesInVectorReturnValidMax)
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

TEST_F(CFindMaxExStringFixture, FindMaxInEmptyVectorNoThrow)
{
    ASSERT_FALSE(FindMaxEx(stringVector, maxString, less<string>()));
}

TEST_F(CFindMaxExStringFixture, FindMaxInEmptyVectorReturnZero)
{
    FindMaxEx(stringVector, maxString, less<string>());
    ASSERT_TRUE(maxString.empty());
}

TEST_F(CFindMaxExStringFixture, FindMaxInVectorWithOneElementReturnThisElement)
{
    stringVector.push_back("one");
    ASSERT_TRUE(FindMaxEx(stringVector, maxString, less<string>()));
    ASSERT_EQ(maxString, "one");
}

TEST_F(CFindMaxExStringFixture, FindMaxInVectorWithManyElementsReturnValidMaxLexicElement)
{
    stringVector.push_back("one");
    stringVector.push_back("two");
    stringVector.push_back("wou");

    ASSERT_TRUE(FindMaxEx(stringVector, maxString, less<string>()));
    ASSERT_EQ(maxString, "wou");
}

/* Для массива обьектов типа CAthlete */

struct CFindMaxExAthleteFixture: public ::testing::Test
{
    std::vector<CAthlete> athleteVector;
    CAthlete athlete;
    std::function<bool(CAthlete, CAthlete)> LessByHeight
            = [&](const CAthlete& athlete1, const CAthlete& athlete2)
            { return athlete1.GetHeight() < athlete2.GetHeight(); };
    std::function<bool(CAthlete, CAthlete)> LessByWeight
            = [&](const CAthlete& athlete1, const CAthlete& athlete2)
            { return athlete1.GetWeight() < athlete2.GetWeight(); };
};

/* Тестирование класса атлета */

TEST_F(CFindMaxExAthleteFixture, InitConstructorWithoutArgsCreateAgreedObject)
{
    ASSERT_EQ(athlete.GetFullname(), "");
    ASSERT_EQ(athlete.GetHeight(), "");
    ASSERT_EQ(athlete.GetWeight(), "");
}

TEST_F(CFindMaxExAthleteFixture, GetFullnameReturnValidValue)
{
    CAthlete testAthlete("Ivanov Ivan Ivanovich", 180, 80);
    ASSERT_EQ(testAthlete.GetFullname(), "Ivanov Ivan Ivanovich");
}

TEST_F(CFindMaxExAthleteFixture, GetHeightReturnValidValue)
{
    CAthlete testAthlete("Ivanov Ivan Ivanovich", 180, 80);
    ASSERT_EQ(testAthlete.GetHeight(), 180);
}

TEST_F(CFindMaxExAthleteFixture, GetWeightReturnValidValue)
{
    CAthlete testAthlete("Ivanov Ivan Ivanovich", 180, 80);
    ASSERT_EQ(testAthlete.GetWeight(), 80);
}

/* Тестирование FindMaxEx на атлетах */

TEST_F(CFindMaxExAthleteFixture, FindMaxInEmptyVectorNoThrow)
{
    ASSERT_FALSE(FindMaxEx(athleteVector, athlete, LessByHeight));
}

TEST_F(CFindMaxExAthleteFixture, FindMaxWithOneElementInVectorReturnThisElement)
{
    athleteVector.push_back({"Romanov", 160, 60});
    ASSERT_TRUE(FindMaxEx(athleteVector, athlete, LessByHeight));
    ASSERT_EQ(athlete.GetFullname(), "Romanov");
    ASSERT_TRUE(FindMaxEx(athleteVector, athlete, LessByWeight));
    ASSERT_EQ(athlete.GetFullname(), "Romanov");
}

TEST_F( CFindMaxExAthleteFixture, FindMaxHeightWithManyValuesInVectorReturnValidMaxByHeightElement)
{
    athleteVector.push_back({"Romanov", 160, 60});
    athleteVector.push_back({"Ivanov", 160, 80});
    athleteVector.push_back({"Petrov", 180, 79});

    ASSERT_TRUE(FindMaxEx(athleteVector, athlete, LessByHeight));
    ASSERT_EQ(athlete.GetFullname(), "Petrov");
}

TEST_F( CFindMaxExAthleteFixture, FindMaxWeightWithManyValuesInVectorReturnValidMaxByWeightElement)
{
    athleteVector.push_back({"Romanov", 160, 60});
    athleteVector.push_back({"Petrov", 180, 79});
    athleteVector.push_back({"Ivanov", 160, 80});

    ASSERT_TRUE(FindMaxEx(athleteVector, athlete, LessByWeight));
    ASSERT_EQ(athlete.GetFullname(), "Ivanov");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}