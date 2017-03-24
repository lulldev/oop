#include "StringStack.h"

using namespace std;

CStringStack::CStringStack() = default;

CStringStack::CStringStack(CStringStack const &stack)
{
    *(this) = stack;
}

CStringStack::CStringStack(CStringStack &&movedStack)
{
    MoveStackToThis(movedStack);
}

CStringStack::~CStringStack()
{
    ClearStack();
}

bool CStringStack::IsEmpty() const
{
    return (m_size == 0);
}

void CStringStack::ClearStack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

void CStringStack::Push(std::string const &newString)
{
    m_top = std::make_shared<StringElement>(newString, m_top);
    ++m_size;
}

void CStringStack::Pop()
{
    if (IsEmpty())
    {
        throw std::underflow_error("Error pop element: stack is empty");
    }

    m_top = m_top->next;
    --m_size;
}

std::string CStringStack::Top() const
{
    if (IsEmpty())
    {
        throw std::underflow_error("Error get top element: stack is empty");
    }

    return m_top->stringElement;
}

void CStringStack::MoveStackToThis(CStringStack &movedStack)
{
    m_size = movedStack.m_size;
    m_top = movedStack.m_top;
    movedStack.m_top = nullptr;
    movedStack.m_size = 0;
}

CStringStack &CStringStack::operator=(CStringStack const &cloneStack)
{
    if (this != std::addressof(cloneStack) && !cloneStack.IsEmpty())
    {
        std::shared_ptr<StringElement> tmpCopy = cloneStack.m_top;
        std::shared_ptr<StringElement> tmpStack = std::make_shared<StringElement>(*tmpCopy);
        std::shared_ptr<StringElement> headTmpStack = tmpStack;

        tmpCopy = tmpCopy->next;

        try
        {
            while (tmpCopy->next != nullptr)
            {
                tmpStack->next = std::make_shared<StringElement>(*tmpCopy);
                tmpStack = tmpStack->next;
                tmpCopy = tmpCopy->next;
            }
            ClearStack();
            m_top = headTmpStack;
            m_size = cloneStack.m_size;
        }
        catch(...)
        {
            while (headTmpStack != nullptr)
            {
                std::shared_ptr<StringElement> deleteNode = headTmpStack;
                headTmpStack = headTmpStack->next;
                delete deleteNode.get();
            }
        }
    }
    return *this;
}

CStringStack &CStringStack::operator=(CStringStack &&movedStack)
{
    if (this != std::addressof(movedStack))
    {
        MoveStackToThis(movedStack);
    }

    return *this;
}