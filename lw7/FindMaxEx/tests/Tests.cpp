#include "Tests.h"

using testing::Eq;
using namespace std;

template <typename T, typename Less>
void VerifyFindMaxEx (std::vector<T> const& elementsVector, T const& expectedMaxElement,
                      Less const& less, bool expectetFindValue)
{
    T maxElement;
    ASSERT_EQ(FindMaxEx(elementsVector, maxElement, less), expectetFindValue);
    ASSERT_EQ(maxElement, expectedMaxElement);
}

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
    VerifyFindMaxEx(numbersVector, 0, less<int>(), false);
}

TEST_F(CFindMaxExNumberFixture, FindMaxInVectorWithOneValuesReturnThisElement)
{
    numbersVector.push_back(2);
    VerifyFindMaxEx(numbersVector, 2, less<int>(), true);
}

TEST_F(CFindMaxExNumberFixture, FindMaxWithManyValuesInVectorReturnValidMax)
{
    numbersVector.push_back(3);
    numbersVector.push_back(-2);
    numbersVector.push_back(1);

    VerifyFindMaxEx(numbersVector, 3, less<int>(), true);
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
    VerifyFindMaxEx(stringVector, std::string("one"), less<string>(), true);
}

TEST_F(CFindMaxExStringFixture, FindMaxInVectorWithManyElementsReturnValidMaxLexicElement)
{
    stringVector.push_back("one");
    stringVector.push_back("two");
    stringVector.push_back("wou");

    VerifyFindMaxEx(stringVector, std::string("wou"), less<string>(), true);
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
    ASSERT_EQ(athlete.GetFullname(), std::string(""));
    ASSERT_EQ(athlete.GetHeight(), 0);
    ASSERT_EQ(athlete.GetWeight(), 0);
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

//    VerifyFindMaxEx(athleteVector, "wou", LessByHeight, true);
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

/*
class ObjectWithException
{
public:
    ObjectWithException() = default;
    ObjectWithException(bool mustThrow)
            : mustThrow(mustThrow)
    {};
    bool mustThrow;
};

bool operator==(const ObjectWithException& lhs, const ObjectWithException& rhs)
{
    if (mustThrow)
    {
        throw runtime_error("Error obect with exception");
    }
    return false;
}

struct CFindMaxExTestObjectsFixture: public ::testing::Test
{
    std::vector<ObjectWithException> vectorOfTestObjects;
    std::function<bool(ObjectWithException, ObjectWithException)> less
            = [](const ObjectWithException& obj1, const ObjectWithException& obj2)
            { return obj1 == obj2; };
};


TEST_F(CFindMaxExTestObjectsFixture, LessWillThrowException)
{
    vectorOfTestObjects.push_back(ObjectWithException(true));
    vectorOfTestObjects.push_back(ObjectWithException(false));
    vectorOfTestObjects.push_back(ObjectWithException(false));

    vector<ObjectWithException> vectorOfTestObjects2 = vectorOfTestObjects;

    ObjectWithException testObject;
    ObjectWithException testObject2 = testObject;

    ASSERT_THROW(FindMaxEx(vectorOfTestObjects, testObject, less), runtime_error);
    ASSERT_EQ(testObject, testObject2);
}
*/

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}