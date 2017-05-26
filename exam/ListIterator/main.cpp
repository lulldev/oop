#include <memory>
#include <iostream>
#include <cassert>

using namespace std;

struct Node
{
	// написать недостающий код
    Node(int value, unique_ptr<Node>&& next)
        : m_value(value)
        , m_next(move(next))
    {
    }
	int m_value;
	unique_ptr<Node> m_next;
};

class List
{
public:
	class Iterator
	{
	public:
		Iterator(Node * node = nullptr)
		: m_node(node)
		{
		}

		Iterator& operator++()
		{
			assert(m_node);
			m_node = m_node->m_next.get();
			return *this;
		}

		const Iterator operator++(int)
		{
			auto copy(*this);
			++*this;
			return copy;
		}

		int& operator*()const
		{
			assert(m_node);
			return m_node->m_value;
		}

        // operator==
        bool operator==(const Iterator& rhsIterator)const
        {
			return m_node == rhsIterator.m_node;
        }

        // operator!=
        bool operator!=(const Iterator& rhsIterator)const
        {
			return !(*this == rhsIterator);
        }
	private:
		Node *m_node;
	};

	List() = default;

	// копирование и присваивание реализовывать не требуется
	List(const List&) = delete;
	List& operator=(const List&) = delete;

	~List()
	{
		// при разрушении списка не должен возникать stack overflow
        while(m_firstNode)
		{
			m_firstNode = std::move(m_firstNode->m_next);
        }
	}

	void PushFront(int value)
	{
		// написать недостающий код
        m_firstNode = std::make_unique<Node>(value, move(m_firstNode));
	}

	Iterator begin()
	{
		return Iterator(m_firstNode.get());
	}

	Iterator end()
	{
		return nullptr;
	}

private:
	unique_ptr<Node> m_firstNode;
};

int main()
{
	List lst;
	lst.PushFront(3);
	lst.PushFront(2);
	lst.PushFront(4);

	for (int x : lst)
	{
		cout << x << ",";
	}

	// Должно быть выведено "4,2,3,"

	return 0;
}