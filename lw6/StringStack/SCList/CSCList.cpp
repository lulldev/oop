#include "CSCList.h"

using namespace std;

CSCList::CSCList()
{
    head = NULL;
}

CSCList::~CSCList() //Деструктор вынесен за класс
{
    while (head != NULL)  //Пока по адресу не пусто
    {
        StringListElement *temp = head->next; //Временная переменная для хранения адреса следующего элемента
        delete head; //Освобождаем адрес обозначающий начало
        head = temp; //Меняем адрес на следующий
    }
}

void CSCList::Push(std::string x) //Функция добавления элементов в список
{
    StringListElement *temp = new StringListElement; //При каждом вызове выделяется память
    temp->str = x; //Записываем x в элемент структуры  StringListElement (в x структуры StringListElement)
    temp->next = head; //Указываем, что след. элемент это объект по адресу head
    head = temp; //Указываем, что последний активный элемент это только что введенный
}

void CSCList::Show() //Функция отображения списка на экране
{
    StringListElement *temp = head; //Определяем указатель, который изначально он равен адресу начала списка
    while (temp != NULL) //До тех пор пока не встретит пустое значение
    {
        cout << temp->str << " "; //Выведет элемент x из списка
        temp = temp->next; //Указываем, что далее нам нужен следующий элемент
    }
}
