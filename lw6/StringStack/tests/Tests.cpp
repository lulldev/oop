#include "Tests.h"

using testing::Eq;
using namespace std;

class CStringEmptyStackFixture: public ::testing::Test
{
public:
    CStringStack stringStack;
};

TEST_F(CStringEmptyStackFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CStringEmptyStackFixture, GetTopMustThrow)
{
    ASSERT_THROW(stringStack.Top(), std::underflow_error);
}

TEST_F(CStringEmptyStackFixture, CanPushInStackReturnLasRecentlyAddedElement)
{
    stringStack.Push("test");
    ASSERT_EQ(stringStack.Top(), "test");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}


TEST_F(CStringEmptyStackFixture, PopFromStackMustThrow)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_THROW(stringStack.Pop(), std::underflow_error);
}

TEST_F(CStringEmptyStackFixture, CanGetValidGetStackSize)
{
    ASSERT_EQ(stringStack.GetSize(), 0);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 1);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 2);
    stringStack.Pop();
    ASSERT_EQ(stringStack.GetSize(), 1);
}

TEST_F(CStringEmptyStackFixture, ClearStackAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.ClearStack());
    ASSERT_TRUE(stringStack.IsEmpty());
}


TEST_F(CStringEmptyStackFixture, CopyStackWithConstructorAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    CStringStack copyStringStack = stringStack;
    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
}

TEST_F(CStringEmptyStackFixture, CopyStackWithAssignmentOperatorAndStackWillEmpty)
{
    CStringStack copyStringStack;
    copyStringStack = stringStack;
    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CStringEmptyStackFixture, CopyStackWithPushModifyOnlySelfAndReturnLastRecentlyElement)
{
    CStringStack copyStringStack;
    copyStringStack = stringStack;
    copyStringStack.Push("test3");

    ASSERT_NE(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CStringEmptyStackFixture, CopyingObjectToItselfAndStackWillEmpty)
{
    stringStack = stringStack;
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringEmptyStackFixture, MoveStackWithConstructorAndStackWillEmpty)
{
    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack = std::move(stringStack);
    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}

TEST_F(CStringEmptyStackFixture, MoveStackWithAssignmentOperatorAndStackWillEmpty)
{

    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack;

    movedStringStack = std::move(copyStringStack);
    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}


TEST_F(CStringEmptyStackFixture, MovingObjectToItselfAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack = std::move(stringStack);
    ASSERT_TRUE(stringStack.IsEmpty());
}


class CStringFilledStackFixture: public ::testing::Test
{
public:
    CStringStack stringStack;
    CStringFilledStackFixture()
    {
        stringStack.Push("test1");
        stringStack.Push("test2");
        stringStack.Push("test3");
    }
};

TEST_F(CStringFilledStackFixture, StackIsNotEmpty)
{
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CStringFilledStackFixture, GetTopMustNoThrow)
{
    ASSERT_NO_THROW(stringStack.Top());
}


TEST_F(CStringFilledStackFixture, GetTopOnFilledStackMustReturnRecentlyAddedElement)
{
    ASSERT_NO_THROW(stringStack.Top());
    ASSERT_EQ(stringStack.Top(), "test3");
    stringStack.Push("hello");
    ASSERT_NO_THROW(stringStack.Top());
    ASSERT_EQ(stringStack.Top(), "hello");
}


TEST_F(CStringFilledStackFixture, PushInStackMustReturnTheRecentlyAddedElement)
{
    ASSERT_EQ(stringStack.Top(), "test3");
    stringStack.Push("test4");
    ASSERT_EQ(stringStack.Top(), "test4");
}


TEST_F(CStringFilledStackFixture, PopFromFilledStackWillNoThrow)
{
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.Pop());
    ASSERT_EQ(stringStack.GetSize(), 2);
}

TEST_F(CStringFilledStackFixture, ManyPushesAndPopsMustBeClearStack)
{
    stringStack.ClearStack();
    int c = 0;
    while (c < 200)
    {
        stringStack.Push(to_string(c));
        ASSERT_EQ(stringStack.Top(), to_string(c));
        stringStack.Pop();
        c++;
    }
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringFilledStackFixture, GetStackSize)
{
    ASSERT_EQ(stringStack.GetSize(), 3);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 4);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 5);
    stringStack.Pop();
    ASSERT_EQ(stringStack.GetSize(), 4);
}

TEST_F(CStringFilledStackFixture, ClearStackMustRemoveAllElement)
{
    ASSERT_NO_THROW(stringStack.ClearStack());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CStringFilledStackFixture, CopyStackWithConstructorMustEqualStacks)
{
    CStringStack copyStringStack = stringStack;

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
        stringStack.Pop();
        copyStringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
}

TEST_F(CStringFilledStackFixture, CopyStackWithAssignmentOperatorWithManyCalls)
{
    int c = 0;
    while (c < 100000)
    {
        stringStack.Push(to_string(c));
        c++;
    }

    CStringStack copyStringStack;
    copyStringStack = stringStack;
    CStringStack emptyStack;
    copyStringStack = emptyStack;

    copyStringStack = stringStack;
    copyStringStack = (CStringStack());

    copyStringStack = stringStack;

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
        copyStringStack.Pop();
        stringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CStringFilledStackFixture, CopyStackWithPushModifyOnlySelfMustReturnThePushingElement)
{
    CStringStack copyStringStack;
    copyStringStack = stringStack;
    copyStringStack.Push("test4");
    ASSERT_NE(copyStringStack.Top(), stringStack.Top());
}


TEST_F(CStringFilledStackFixture, CopyingObjectToItselfMustReturnTheRecentlyAddedElement)
{
    stringStack = stringStack;
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test3");
}

TEST_F(CStringFilledStackFixture, MoveStackWithConstructorMustEqualStasks)
{
    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack = std::move(stringStack);

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), movedStringStack.Top());
        copyStringStack.Pop();
        movedStringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}


TEST_F(CStringFilledStackFixture, MoveStackWithAssignmentOperator)
{
    CStringStack copyStringStack = stringStack;
    CStringStack movedStringStack;
    movedStringStack = std::move(stringStack);

    while (!stringStack.IsEmpty())
    {
        ASSERT_EQ(stringStack.Top(), movedStringStack.Top());
        stringStack.Pop();
        movedStringStack.Pop();
    }

    ASSERT_NE(stringStack.GetSize(), movedStringStack.GetSize());
}

TEST_F(CStringFilledStackFixture, MovingObjectToItselfMustReturnTheRecentlyAddedElement)
{
    stringStack = std::move(stringStack);
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test3");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}