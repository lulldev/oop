#include "Tests.h"

using testing::Eq;
using namespace std;

class CSCListTestFixture: public ::testing::Test
{
public:
    CSCList<int> sclist;

    CSCListTestFixture(): sclist()
    {
    }
};

TEST_F(CSCListTestFixture, Test)
{
    sclist.Push(1);
    sclist.Show();
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}