#include <iostream>

using namespace std;

template <typename T>
struct ListElement
{
    T element;
    ListElement<T> *next;
};

template <typename T>
class CSCList
{
public:
    /*
    CSCList();
    ~CSCList();
    void Push(const T newElement);
    void Show();
     */

    CSCList()
    {
        head = NULL;
    }

    ~CSCList() //Деструктор вынесен за класс
    {
        while (head != NULL)  //Пока по адресу не пусто
        {
            ListElement<T> *temp = head->next; //Временная переменная для хранения адреса следующего элемента
            delete head; //Освобождаем адрес обозначающий начало
            head = temp; //Меняем адрес на следующий
        }
    }

    void Push(const T newElement) //Функция добавления элементов в список
    {
        ListElement<T> *temp = new ListElement<T>; //При каждом вызове выделяется память
        temp->element = newElement; //Записываем x в элемент структуры  ListElement (в x структуры ListElement)
        temp->next = head;
        head = temp;
    }

    void Show()
    {
        ListElement<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->element << " ";
            temp = temp->next;
        }
    }

private:
    ListElement<T> *head;
};

/*
CSCList::CSCList()
{
    head = NULL;
}

CSCList::~CSCList() //Деструктор вынесен за класс
{
    while (head != NULL)  //Пока по адресу не пусто
    {
        ListElement *temp = head->next; //Временная переменная для хранения адреса следующего элемента
        delete head; //Освобождаем адрес обозначающий начало
        head = temp; //Меняем адрес на следующий
    }
}

template <typename T>
void CSCList::Push(const T newElement) //Функция добавления элементов в список
{
    ListElement *temp = new ListElement; //При каждом вызове выделяется память
    temp->element = newElement; //Записываем x в элемент структуры  ListElement (в x структуры ListElement)
    temp->next = head;
    head = temp;
}

void CSCList::Show()
{
    ListElement *temp = head;
    while (temp != NULL)
    {
        cout << temp->element << " ";
        temp = temp->next;
    }
}
*/