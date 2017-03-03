#include "Tests.h"

using testing::Eq;
using namespace std;

TEST(TestHelpers, TestSimplePow)
{
    ASSERT_TRUE(1==1);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}