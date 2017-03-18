#include "Tests.h"

using testing::Eq;
using namespace std;

class CStringStackTestFixture: public ::testing::Test
{
public:
    CStringStack stringStack;

    CStringStackTestFixture()
            : stringStack()
    {
    }
};

TEST_F(CStringStackTestFixture, TestIsEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, TestTopStack)
{
    ASSERT_THROW(stringStack.Top(), std::underflow_error);
    stringStack.Push("test");
    ASSERT_NO_THROW(stringStack.Top());
    ASSERT_EQ(stringStack.Top(), "test");
}

TEST_F(CStringStackTestFixture, TestPushInStack)
{
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test");

    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}

TEST_F(CStringStackTestFixture, TestPopStack)
{
    ASSERT_THROW(stringStack.Pop(), std::underflow_error);
    stringStack.Push("test1");
    ASSERT_NO_THROW(stringStack.Pop());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, TestClearStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test1");
    stringStack.Push("test2");
    ASSERT_TRUE(!stringStack.IsEmpty());
    stringStack.ClearStack();
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, TestCopyStackByConstructor)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CStringStack copyStringStack = stringStack;

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
}

TEST_F(CStringStackTestFixture, TestCopyStackByCopyOperator)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CStringStack copyStringStack;
    copyStringStack = stringStack;

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
        copyStringStack.Pop();
        stringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, TestMoveStackByConstructor)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack = std::move(stringStack);

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), movedStringStack.Top());
        copyStringStack.Pop();
        movedStringStack.Pop();
    }
}

TEST_F(CStringStackTestFixture, TestMoveStackByCopyOperator)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack;

    movedStringStack = copyStringStack;

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), movedStringStack.Top());
        copyStringStack.Pop();
        movedStringStack.Pop();
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
