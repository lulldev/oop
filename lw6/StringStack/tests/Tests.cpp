#include "Tests.h"

using testing::Eq;
using namespace std;

class CStringStackTestFixture: public ::testing::Test
{
public:
    CStringStack stringStack;
};

TEST_F(CStringStackTestFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, GetTopOnEmptyStack)
{
    ASSERT_THROW(stringStack.Top(), std::underflow_error);
}

TEST_F(CStringStackTestFixture, GetTopOnFilledStack)
{
    stringStack.Push("test");
    ASSERT_NO_THROW(stringStack.Top());
    ASSERT_EQ(stringStack.Top(), "test");
}

TEST_F(CStringStackTestFixture, PushInEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}

TEST_F(CStringStackTestFixture, PushInFilledStack)
{
    stringStack.Push("test1");
    stringStack.Push("test2");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test2");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}

TEST_F(CStringStackTestFixture, PopInEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_THROW(stringStack.Pop(), std::underflow_error);
}

TEST_F(CStringStackTestFixture, PopInFilledStack)
{
    stringStack.Push("test1");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.Pop());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, ClearEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.ClearStack());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, ClearFilledStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test1");
    stringStack.Push("test2");
    ASSERT_FALSE(stringStack.IsEmpty());
    stringStack.ClearStack();
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, CopyStackByConstructor)
{
    stringStack.Push("test1");
    stringStack.Push("test2");
    stringStack.Push("test3");
    stringStack.Push("test4");
    stringStack.Pop();
    stringStack.Push("test4");
    stringStack.Pop();
    stringStack.Push("test5");

    CStringStack copyStringStack = stringStack;

    stringStack.Push("original-str");
    ASSERT_NE(copyStringStack.Top(), stringStack.Top());
    stringStack.Pop();

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
        copyStringStack.Pop();
        stringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, CopyStackByCopyOperator)
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

TEST_F(CStringStackTestFixture, MoveStackByConstructor)
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

    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
}

TEST_F(CStringStackTestFixture, MoveStackByCopyOperator)
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
