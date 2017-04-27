#include "Tests.h"

using testing::Eq;
using namespace std;

class CMyStackOfStringsTestFixture: public ::testing::Test
{
public:
    CMyStack<string> stringStack;
};

TEST_F(CMyStackOfStringsTestFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CMyStackOfStringsTestFixture, GetTopMustThrow)
{
    ASSERT_THROW(stringStack.Top(), std::underflow_error);
}

TEST_F(CMyStackOfStringsTestFixture, CanPushInStackReturnLasRecentlyAddedElement)
{
    stringStack.Push("test");
    ASSERT_EQ(stringStack.Top(), "test");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}


TEST_F(CMyStackOfStringsTestFixture, PopFromStackMustThrow)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_THROW(stringStack.Pop(), std::underflow_error);
}

TEST_F(CMyStackOfStringsTestFixture, CanGetValidGetStackSize)
{
    ASSERT_EQ(stringStack.GetSize(), 0);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 1);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 2);
    stringStack.Pop();
    ASSERT_EQ(stringStack.GetSize(), 1);
}

TEST_F(CMyStackOfStringsTestFixture, ClearStackAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.ClearStack());
    ASSERT_TRUE(stringStack.IsEmpty());
}


TEST_F(CMyStackOfStringsTestFixture, CopyStackWithConstructorAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    CMyStack<string>copyStringStack = stringStack;
    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
}

TEST_F(CMyStackOfStringsTestFixture, CopyStackWithAssignmentOperatorAndStackWillEmpty)
{
    CMyStack<string>copyStringStack;
    copyStringStack = stringStack;
    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CMyStackOfStringsTestFixture, CopyStackWithPushModifyOnlySelfAndReturnLastRecentlyElement)
{
    CMyStack<string>copyStringStack;
    copyStringStack = stringStack;
    copyStringStack.Push("test3");

    ASSERT_NE(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CMyStackOfStringsTestFixture, CopyingObjectToItselfAndStackWillEmpty)
{
    stringStack = stringStack;
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CMyStackOfStringsTestFixture, MoveStackWithConstructorAndStackWillEmpty)
{
    CMyStack<string>copyStringStack = stringStack;
    CMyStack<string>movedStringStack = std::move(stringStack);
    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}

TEST_F(CMyStackOfStringsTestFixture, MoveStackWithAssignmentOperatorAndStackWillEmpty)
{

    CMyStack<string>copyStringStack = stringStack;
    CMyStack<string>movedStringStack;

    movedStringStack = std::move(copyStringStack);
    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}


TEST_F(CMyStackOfStringsTestFixture, MovingObjectToItselfAndStackWillEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack = std::move(stringStack);
    ASSERT_TRUE(stringStack.IsEmpty());
}

class CMyStackOfIntegerNumbersTestFixture: public ::testing::Test
{
public:
    CMyStack<int> intStack;
};

TEST_F(CMyStackOfIntegerNumbersTestFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(intStack.IsEmpty());
    intStack.Push(1);
    ASSERT_FALSE(intStack.IsEmpty());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, GetTopMustThrow)
{
    ASSERT_THROW(intStack.Top(), std::underflow_error);
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, CanPushInStackReturnLasRecentlyAddedElement)
{
    intStack.Push(1);
    ASSERT_EQ(intStack.Top(), 1);
    intStack.Push(2);
    ASSERT_EQ(intStack.Top(), 2);
}


TEST_F(CMyStackOfIntegerNumbersTestFixture, PopFromStackMustThrow)
{
    ASSERT_TRUE(intStack.IsEmpty());
    ASSERT_THROW(intStack.Pop(), std::underflow_error);
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, CanGetValidGetStackSize)
{
    ASSERT_EQ(intStack.GetSize(), 0);
    intStack.Push(1);
    ASSERT_EQ(intStack.GetSize(), 1);
    intStack.Push(1);
    ASSERT_EQ(intStack.GetSize(), 2);
    intStack.Pop();
    ASSERT_EQ(intStack.GetSize(), 1);
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, ClearStackAndStackWillEmpty)
{
    ASSERT_TRUE(intStack.IsEmpty());
    ASSERT_NO_THROW(intStack.ClearStack());
    ASSERT_TRUE(intStack.IsEmpty());
}


TEST_F(CMyStackOfIntegerNumbersTestFixture, CopyStackWithConstructorAndStackWillEmpty)
{
    ASSERT_TRUE(intStack.IsEmpty());
    CMyStack<int>copyintStack = intStack;
    ASSERT_EQ(copyintStack.IsEmpty(), intStack.IsEmpty());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, CopyStackWithAssignmentOperatorAndStackWillEmpty)
{
    CMyStack<int>copyintStack;
    copyintStack = intStack;
    ASSERT_EQ(copyintStack.IsEmpty(), intStack.IsEmpty());
    ASSERT_EQ(copyintStack.GetSize(), intStack.GetSize());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, CopyStackWithPushModifyOnlySelfAndReturnLastRecentlyElement)
{
    CMyStack<int>copyintStack;
    copyintStack = intStack;
    copyintStack.Push(3);

    ASSERT_NE(copyintStack.GetSize(), intStack.GetSize());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, CopyingObjectToItselfAndStackWillEmpty)
{
    intStack = intStack;
    ASSERT_TRUE(intStack.IsEmpty());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, MoveStackWithConstructorAndStackWillEmpty)
{
    CMyStack<int>copyintStack = intStack;
    CMyStack<int>movedintStack = std::move(intStack);
    ASSERT_EQ(copyintStack.IsEmpty(), movedintStack.IsEmpty());
    ASSERT_EQ(copyintStack.GetSize(), movedintStack.GetSize());
}

TEST_F(CMyStackOfIntegerNumbersTestFixture, MoveStackWithAssignmentOperatorAndStackWillEmpty)
{

    CMyStack<int>copyintStack = intStack;
    CMyStack<int>movedintStack;

    movedintStack = std::move(copyintStack);
    ASSERT_EQ(copyintStack.IsEmpty(), movedintStack.IsEmpty());
    ASSERT_EQ(copyintStack.GetSize(), movedintStack.GetSize());
}


TEST_F(CMyStackOfIntegerNumbersTestFixture, MovingObjectToItselfAndStackWillEmpty)
{
    ASSERT_TRUE(intStack.IsEmpty());
    intStack = std::move(intStack);
    ASSERT_TRUE(intStack.IsEmpty());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}