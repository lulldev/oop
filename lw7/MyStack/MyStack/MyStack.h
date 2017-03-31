#include <iostream>

struct StackElement
{
    StackElement(std::string const& element, std::shared_ptr<StackElement>const& nextElement)
            : stringElement(element)
            , next(nextElement)
    {
    }
    std::string stringElement;
    std::shared_ptr<StackElement> next;
};

class CMyStack
{
public:
    CMyStack() = default;

    CMyStack(CMyStack const &stack)
    {
        *(this) = stack;
    }

    CMyStack(CMyStack &&movedStack)
    {
        MoveStackToThis(movedStack);
    }

    CMyStack &operator=(CMyStack const& cloneStack)
    {
        if (this != std::addressof(cloneStack) && !cloneStack.IsEmpty())
        {
            std::shared_ptr<StackElement> tmpCloneTop = cloneStack.m_top;
            std::shared_ptr<StackElement> currentElement = std::make_shared<StackElement>(tmpCloneTop->stringElement, nullptr);
            m_top = currentElement;

            tmpCloneTop = tmpCloneTop->next;
            while (tmpCloneTop != nullptr)
            {
                currentElement->next = std::make_shared<StackElement>(tmpCloneTop->stringElement, nullptr);
                currentElement = currentElement->next;

                tmpCloneTop = tmpCloneTop->next;
            }
            m_size = cloneStack.m_size;
        }
        return *this;
    }

    CMyStack &operator=(CMyStack &&movedStack)
    {
        if (this != std::addressof(movedStack))
        {
            MoveStackToThis(movedStack);
        }

        return *this;
    }

    ~CMyStack()
    {
        ClearStack();
    }

    bool IsEmpty()const
    {
        return (m_size == 0);
    }

    size_t GetSize()const
    {
        return m_size;
    }

    void ClearStack()
    {
        while (!IsEmpty())
        {
            Pop();
        }
    }

    void Push(std::string const &newString)
    {
        m_top = std::make_shared<StackElement>(newString, m_top);
        ++m_size;
    }

    void Pop()
    {
        if (IsEmpty())
        {
            throw std::underflow_error("Error pop element: stack is empty");
        }

        m_top = m_top->next;
        --m_size;
    }

    std::string Top() const
    {
        if (IsEmpty())
        {
            throw std::underflow_error("Error get top element: stack is empty");
        }

        return m_top->stringElement;
    }

private:
    size_t m_size = 0;
    std::shared_ptr<StackElement> m_top = nullptr;

    void MoveStackToThis(CMyStack &movedStack)
    {
        m_size = movedStack.GetSize();
        m_top = movedStack.m_top;
        movedStack.m_top = nullptr;
        movedStack.m_size = 0;
    }
};