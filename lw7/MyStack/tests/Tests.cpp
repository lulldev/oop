#include "Tests.h"

using testing::Eq;
using namespace std;

class CMyStackStringTestFixture: public ::testing::Test
{
public:
    CMyStack<string> stringStack;
};

TEST_F(CMyStackStringTestFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
}

TEST_F(CMyStackStringTestFixture, GetTopOnEmptyStack)
{
    ASSERT_THROW(stringStack.Top(), std::underflow_error);
}

TEST_F(CMyStackStringTestFixture, GetTopOnFilledStack)
{
    stringStack.Push("test");
    ASSERT_NO_THROW(stringStack.Top());
    ASSERT_EQ(stringStack.Top(), "test");
}

TEST_F(CMyStackStringTestFixture, PushInEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}

TEST_F(CMyStackStringTestFixture, PushInFilledStack)
{
    stringStack.Push("test1");
    stringStack.Push("test2");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test2");
    stringStack.Push("test1");
    ASSERT_EQ(stringStack.Top(), "test1");
}

TEST_F(CMyStackStringTestFixture, PopInEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_THROW(stringStack.Pop(), std::underflow_error);
}

TEST_F(CMyStackStringTestFixture, PopInFilledStack)
{
    stringStack.Push("test1");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.Pop());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CMyStackStringTestFixture, ManyPushesAndPops)
{
    ASSERT_TRUE(stringStack.IsEmpty());

    int c = 0;
    while (c < 20)
    {
        stringStack.Push(to_string(c));
        ASSERT_EQ(stringStack.Top(), to_string(c));
        stringStack.Pop();
        c++;
    }
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CMyStackStringTestFixture, GetStackSize)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.GetSize(), 0);
    stringStack.Push("test");
    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.GetSize(), 1);
    stringStack.Push("test");
    ASSERT_EQ(stringStack.GetSize(), 2);
    stringStack.Pop();
    ASSERT_EQ(stringStack.GetSize(), 1);
}

TEST_F(CMyStackStringTestFixture, ClearEmptyStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    ASSERT_NO_THROW(stringStack.ClearStack());
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CMyStackStringTestFixture, ClearFilledStack)
{
    ASSERT_TRUE(stringStack.IsEmpty());
    stringStack.Push("test1");
    stringStack.Push("test2");
    ASSERT_FALSE(stringStack.IsEmpty());
    stringStack.ClearStack();
    ASSERT_TRUE(stringStack.IsEmpty());
}

TEST_F(CMyStackStringTestFixture, CopyStackByConstructor)
{
    stringStack.Push("test1");
    stringStack.Push("test2");
    stringStack.Push("test3");
    stringStack.Push("test4");
    stringStack.Pop();
    stringStack.Push("test4");
    stringStack.Pop();
    stringStack.Push("test5");

    CMyStack<string> copyStringStack = stringStack;

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), stringStack.Top());
        copyStringStack.Pop();
        stringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), stringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), stringStack.GetSize());
}

TEST_F(CMyStackStringTestFixture, CopyStackByAssignmentOperator)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CMyStack<string> copyStringStack;
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

TEST_F(CMyStackStringTestFixture, CopyStackByPushModifyOnlySelf)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CMyStack<string> copyStringStack;
    copyStringStack = stringStack;

    copyStringStack.Push("test3");
    ASSERT_NE(copyStringStack.Top(), stringStack.Top());
}

TEST_F(CMyStackStringTestFixture, CopyingObjectToItself)
{
    ASSERT_TRUE(stringStack.IsEmpty());

    stringStack.Push("test1");
    stringStack.Push("test2");

    ASSERT_FALSE(stringStack.IsEmpty());

    stringStack = stringStack;

    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test2");
}

TEST_F(CMyStackStringTestFixture, MoveStackByConstructor)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CMyStack<string> copyStringStack = stringStack;
    CMyStack<string> movedStringStack = std::move(stringStack);

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), movedStringStack.Top());
        copyStringStack.Pop();
        movedStringStack.Pop();
    }

    ASSERT_EQ(copyStringStack.IsEmpty(), movedStringStack.IsEmpty());
    ASSERT_EQ(copyStringStack.GetSize(), movedStringStack.GetSize());
}

TEST_F(CMyStackStringTestFixture, MoveStackByAssignmentOperator)
{
    stringStack.Push("test1");
    stringStack.Push("test2");

    CMyStack<string> copyStringStack = stringStack;
    CMyStack<string> movedStringStack;

    movedStringStack = std::move(copyStringStack);

    while (!copyStringStack.IsEmpty())
    {
        ASSERT_EQ(copyStringStack.Top(), movedStringStack.Top());
        copyStringStack.Pop();
        movedStringStack.Pop();
    }
}

TEST_F(CMyStackStringTestFixture, MovingObjectToItself)
{
    ASSERT_TRUE(stringStack.IsEmpty());

    stringStack.Push("test1");
    stringStack.Push("test2");

    ASSERT_FALSE(stringStack.IsEmpty());

    stringStack = std::move(stringStack);

    ASSERT_FALSE(stringStack.IsEmpty());
    ASSERT_EQ(stringStack.Top(), "test2");
}

/* Для чисел (int) */

class CMyStackIntegerTestFixture: public ::testing::Test
{
public:
    CMyStack<int> numberStack;
};

TEST_F(CMyStackIntegerTestFixture, NewStackIsEmpty)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    numberStack.Push(1);
    ASSERT_FALSE(numberStack.IsEmpty());
}

TEST_F(CMyStackIntegerTestFixture, GetTopOnEmptyStack)
{
    ASSERT_THROW(numberStack.Top(), std::underflow_error);
}

TEST_F(CMyStackIntegerTestFixture, GetTopOnFilledStack)
{
    numberStack.Push(1);
    ASSERT_NO_THROW(numberStack.Top());
    ASSERT_EQ(numberStack.Top(), 1);
}

TEST_F(CMyStackIntegerTestFixture, PushInEmptyStack)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    numberStack.Push(1);
    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.Top(), 1);
    numberStack.Push(2);
    ASSERT_EQ(numberStack.Top(), 2);
}

TEST_F(CMyStackIntegerTestFixture, PushInFilledStack)
{
    numberStack.Push(1);
    numberStack.Push(2);
    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.Top(), 2);
    numberStack.Push(1);
    ASSERT_EQ(numberStack.Top(), 1);
}

TEST_F(CMyStackIntegerTestFixture, PopInEmptyStack)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    ASSERT_THROW(numberStack.Pop(), std::underflow_error);
}

TEST_F(CMyStackIntegerTestFixture, PopInFilledStack)
{
    numberStack.Push(1);
    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_NO_THROW(numberStack.Pop());
    ASSERT_TRUE(numberStack.IsEmpty());
}

TEST_F(CMyStackIntegerTestFixture, ManyPushesAndPops)
{
    ASSERT_TRUE(numberStack.IsEmpty());

    int c = 0;
    while (c < 20)
    {
        numberStack.Push(c);
        ASSERT_EQ(numberStack.Top(), c);
        numberStack.Pop();
        c++;
    }
    ASSERT_TRUE(numberStack.IsEmpty());
}

TEST_F(CMyStackIntegerTestFixture, GetStackSize)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.GetSize(), 0);
    numberStack.Push(1);
    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.GetSize(), 1);
    numberStack.Push(1);
    ASSERT_EQ(numberStack.GetSize(), 2);
    numberStack.Pop();
    ASSERT_EQ(numberStack.GetSize(), 1);
}

TEST_F(CMyStackIntegerTestFixture, ClearEmptyStack)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    ASSERT_NO_THROW(numberStack.ClearStack());
    ASSERT_TRUE(numberStack.IsEmpty());
}

TEST_F(CMyStackIntegerTestFixture, ClearFilledStack)
{
    ASSERT_TRUE(numberStack.IsEmpty());
    numberStack.Push(1);
    numberStack.Push(2);
    ASSERT_FALSE(numberStack.IsEmpty());
    numberStack.ClearStack();
    ASSERT_TRUE(numberStack.IsEmpty());
}

TEST_F(CMyStackIntegerTestFixture, CopyStackByConstructor)
{
    numberStack.Push(1);
    numberStack.Push(2);
    numberStack.Push(3);
    numberStack.Push(4);
    numberStack.Pop();
    numberStack.Push(4);
    numberStack.Pop();
    numberStack.Push(5);

    CMyStack<int> copynumberStack = numberStack;

    while (!copynumberStack.IsEmpty())
    {
        ASSERT_EQ(copynumberStack.Top(), numberStack.Top());
        copynumberStack.Pop();
        numberStack.Pop();
    }

    ASSERT_EQ(copynumberStack.IsEmpty(), numberStack.IsEmpty());
    ASSERT_EQ(copynumberStack.GetSize(), numberStack.GetSize());
}

TEST_F(CMyStackIntegerTestFixture, CopyStackByAssignmentOperator)
{
    numberStack.Push(1);
    numberStack.Push(2);

    CMyStack<int> copynumberStack;
    copynumberStack = numberStack;

    while (!copynumberStack.IsEmpty())
    {
        ASSERT_EQ(copynumberStack.Top(), numberStack.Top());
        copynumberStack.Pop();
        numberStack.Pop();
    }

    ASSERT_EQ(copynumberStack.IsEmpty(), numberStack.IsEmpty());
    ASSERT_EQ(copynumberStack.GetSize(), numberStack.GetSize());
}

TEST_F(CMyStackIntegerTestFixture, CopyStackByPushModifyOnlySelf)
{
    numberStack.Push(1);
    numberStack.Push(2);

    CMyStack<int> copynumberStack;
    copynumberStack = numberStack;

    copynumberStack.Push(3);
    ASSERT_NE(copynumberStack.Top(), numberStack.Top());
}

TEST_F(CMyStackIntegerTestFixture, CopyingObjectToItself)
{
    ASSERT_TRUE(numberStack.IsEmpty());

    numberStack.Push(1);
    numberStack.Push(2);

    ASSERT_FALSE(numberStack.IsEmpty());

    numberStack = numberStack;

    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.Top(), 2);
}

TEST_F(CMyStackIntegerTestFixture, MoveStackByConstructor)
{
    numberStack.Push(1);
    numberStack.Push(2);

    CMyStack<int> copynumberStack = numberStack;
    CMyStack<int> movednumberStack = std::move(numberStack);

    while (!copynumberStack.IsEmpty())
    {
        ASSERT_EQ(copynumberStack.Top(), movednumberStack.Top());
        copynumberStack.Pop();
        movednumberStack.Pop();
    }

    ASSERT_EQ(copynumberStack.IsEmpty(), movednumberStack.IsEmpty());
    ASSERT_EQ(copynumberStack.GetSize(), movednumberStack.GetSize());
}

TEST_F(CMyStackIntegerTestFixture, MoveStackByAssignmentOperator)
{
    numberStack.Push(1);
    numberStack.Push(2);

    CMyStack<int> copynumberStack = numberStack;
    CMyStack<int> movednumberStack;

    movednumberStack = std::move(copynumberStack);

    while (!copynumberStack.IsEmpty())
    {
        ASSERT_EQ(copynumberStack.Top(), movednumberStack.Top());
        copynumberStack.Pop();
        movednumberStack.Pop();
    }
}

TEST_F(CMyStackIntegerTestFixture, MovingObjectToItself)
{
    ASSERT_TRUE(numberStack.IsEmpty());

    numberStack.Push(1);
    numberStack.Push(2);

    ASSERT_FALSE(numberStack.IsEmpty());

    numberStack = std::move(numberStack);

    ASSERT_FALSE(numberStack.IsEmpty());
    ASSERT_EQ(numberStack.Top(), 2);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}