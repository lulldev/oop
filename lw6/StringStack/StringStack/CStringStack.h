#include <iostream>

class StringElement
{
public:
    StringElement(std::string const& newString, std::shared_ptr<StringElement> const& nextElement)
            :stringElement(newString),
             next(nextElement)
    {
    }
    std::string stringElement;
    std::shared_ptr<StringElement> next = nullptr;
};

class CStringStack
{
public:
    CStringStack();
    ~CStringStack();

    void Push(std::string const& newString);
    void Pop();
    std::shared_ptr<StringElement> Top() const;
    bool IsEmpty()const;
    void ClearStack();

    //CStringStack(CStringStack const& stack);
    //CStringStack(CStringStack && stackCopy);
//    CStringStack& operator=(CStringStack const& cloneStack);
//    CStringStack& operator=(CStringStack && moveStack);

private:
    size_t m_size = 0;
    std::shared_ptr<StringElement> m_top = nullptr;
};