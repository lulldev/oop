#include "CStringStack.h"

using namespace std;

CStringStack::CStringStack() = default;

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