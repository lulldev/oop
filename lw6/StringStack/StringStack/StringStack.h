#include <iostream>

struct StringElement
{
    StringElement(std::string const& newString, std::shared_ptr<StringElement>const& nextElement)
            : stringElement(newString)
            , next(nextElement)
    {
    }
    std::string stringElement;
    std::shared_ptr<StringElement> next;
};

class CStringStack
{
public:
    CStringStack();
    CStringStack(CStringStack const& stack);
    CStringStack(CStringStack && movedStack);
    CStringStack& operator=(CStringStack const& rhsStack);
    CStringStack& operator=(CStringStack && movedStack);
    ~CStringStack();

    std::string Top()const;
    bool IsEmpty()const;
    size_t GetSize()const;

    void Push(std::string const& newString);
    void Pop();
    void ClearStack();

private:
    size_t m_size = 0;
    std::shared_ptr<StringElement> m_top = nullptr;
    void MoveStackToThis(CStringStack& movedStack);
};