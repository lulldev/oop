#include "Tests.h"

using testing::Eq;
using namespace std;

/* Для чисел */

class CFindMaxExNumberFixture: public ::testing::Test
{
public:
    std::vector<int> numbersVector;
    int maxNumber;
};

TEST_F(CFindMaxExNumberFixture, FindMaxInEmptyVector)
{
    ASSERT_FALSE(FindMaxEx(numbersVector, maxNumber, less<int>()));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}