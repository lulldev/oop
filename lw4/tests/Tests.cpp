#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../VolumeBodies/CBody.h"

using testing::Eq;

namespace
{
    class VolumeBodiesTestFixture : public testing::Test
    {
    public:
        CBody *body;
        VolumeBodiesTestFixture()
        {
            body;
        }
    };
}

TEST_F(VolumeBodiesTestFixture, EmptyString)
{
    ASSERT_EQ("", "");
}

TEST_F(VolumeBodiesTestFixture, EmptyString1)
{
    ASSERT_EQ("", "");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}