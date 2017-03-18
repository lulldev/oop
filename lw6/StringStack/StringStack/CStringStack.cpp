#include "CStringStack.h"

using namespace std;

CStringStack::CStringStack() = default;

CStringStack::CStringStack(CStringStack const& stack)
{
    *(this) = stack;
}

CStringStack::CStringStack(CStringStack && movedStack)
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

void CStringStack::Push(std::string const& newString)
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

    shared_ptr<StringElement> tmpElement = m_top;
    m_top = m_top->next;
    // todo: test deleting
    --m_size;
}

shared_ptr<StringElement> CStringStack::Top() const
{
    if (IsEmpty())
    {
        throw std::underflow_error("Error get top element: stack is empty");
    }

    return m_top;
}

void CStringStack::MoveStackToThis(CStringStack& movedStack)
{
    m_size = movedStack.m_size;
    m_top = movedStack.m_top;
    movedStack.m_top = nullptr;
    movedStack.m_size = 0;
}

CStringStack& CStringStack::operator=(CStringStack const& cloneStack)
{
    if (this != &cloneStack)
    {
        ClearStack();

        if (!cloneStack.IsEmpty())
        {
            std::shared_ptr<StringElement> tmpCopy = cloneStack.m_top;
            m_top = tmpCopy;
            std::shared_ptr<StringElement> target = tmpCopy;

            target->stringElement = tmpCopy->stringElement;

            while (tmpCopy->next != nullptr)
            {
                target->next = std::make_shared<StringElement>(*tmpCopy->next);

                tmpCopy = tmpCopy->next;
                target = target ->next;
            }
            m_size = cloneStack.m_size;
        }
    }

    return *this;
}

CStringStack& CStringStack::operator=(CStringStack && movedStack)
{
    if (this != &movedStack)
    {
        MoveStackToThis(movedStack);
    }

    return *this;
}