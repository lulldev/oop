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

bool CStringStack::IsEmpty()const
{
    return (m_size == 0);
}

size_t CStringStack::GetSize()const
{
    return m_size;
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
    m_size = movedStack.GetSize();
    m_top = movedStack.m_top;
    movedStack.m_top = nullptr;
    movedStack.m_size = 0;
}

CStringStack &CStringStack::operator=(CStringStack const& rhsStack)
{
    if (this != std::addressof(rhsStack))
    {
        std::shared_ptr<StringElement> tmpCloneTop = rhsStack.m_top;
        std::shared_ptr<StringElement> currentElement = std::make_shared<StringElement>(tmpCloneTop->stringElement, nullptr);
        std::shared_ptr<StringElement> tmpCurrentElement = currentElement;

        tmpCloneTop = tmpCloneTop->next;

        try
        {
            while (tmpCloneTop != nullptr)
            {
                currentElement->next = std::make_shared<StringElement>(tmpCloneTop->stringElement, nullptr);
                currentElement = currentElement->next;

                tmpCloneTop = tmpCloneTop->next;
            }
        }
        catch (...)
        {
            while (currentElement != nullptr)
            {
                std::shared_ptr<StringElement> deleteNode = currentElement;
                currentElement = currentElement->next;
            }
        }
        m_top = tmpCurrentElement;
        m_size = rhsStack.m_size;
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