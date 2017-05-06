#include <iostream>

template<typename T>
class CMyStack
{
    struct StackElement
    {
        StackElement(T const& newElement, std::shared_ptr<StackElement>const& nextElement)
                : element(newElement)
                , next(nextElement)
        {
        }
        T element;
        std::shared_ptr<StackElement> next;
    };

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

    CMyStack &operator=(CMyStack const& rhsStack)
    {
        if (rhsStack.IsEmpty())
        {
            ClearStack();
            return *this;
        }

        if (this != std::addressof(rhsStack))
        {
            std::shared_ptr<StackElement> tmpCopyTop = rhsStack.m_top;
            std::shared_ptr<StackElement> currentElement = std::make_shared<StackElement>(tmpCopyTop->element, nullptr);
            std::shared_ptr<StackElement> tmpCurrentElement = currentElement;

            tmpCopyTop = tmpCopyTop->next;
            try
            {
                while (tmpCopyTop != nullptr)
                {
                    currentElement->next = std::make_shared<StackElement>(tmpCopyTop->element, nullptr);
                    currentElement = currentElement->next;
                    tmpCopyTop = tmpCopyTop->next;
                }
                ClearStack();
                m_top = tmpCurrentElement;
                m_size = rhsStack.GetSize();
            }
            catch (...)
            {
                while (currentElement != nullptr)
                {
                    std::shared_ptr<StackElement> deleteNode = currentElement;
                    currentElement = currentElement->next;
                }
            }
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

    void Push(T const &newString)
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

    T Top() const
    {
        if (IsEmpty())
        {
            throw std::underflow_error("Error get top element: stack is empty");
        }

        return m_top->element;
    }

private:
    size_t m_size = 0;
    std::shared_ptr<StackElement> m_top = nullptr;

    void MoveStackToThis(CMyStack &movedStack)
    {
        ClearStack();
        m_size = movedStack.GetSize();
        movedStack.m_top.swap(m_top);
        movedStack.m_size = 0;
    }
};