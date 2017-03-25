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

CStringStack &CStringStack::operator=(CStringStack const& cloneStack)
{
    if (this != std::addressof(cloneStack) && !cloneStack.IsEmpty())
    {
        std::shared_ptr<StringElement> cloneStackTop = cloneStack.m_top;
        std::shared_ptr<StringElement> tmpStack = std::make_shared<StringElement>(*cloneStackTop);
        std::shared_ptr<StringElement> copyTmpStack = tmpStack;

        cloneStackTop = cloneStackTop->next;

        try
        {
            while (cloneStackTop->next != nullptr)
            {
                tmpStack->next = std::make_shared<StringElement>(*cloneStackTop);
                tmpStack = tmpStack->next;
                cloneStackTop = cloneStackTop->next;
            }
            ClearStack();
            m_top = copyTmpStack;
            m_size = cloneStack.GetSize();
        }
        catch(...)
        {
            while (copyTmpStack != nullptr)
            {
                delete copyTmpStack.get();
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