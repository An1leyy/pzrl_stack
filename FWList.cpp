#include "FWList.h"
#include <iostream>
#include <vector>

ForwardList::ForwardList() : list(nullptr), sz(0) {}
ForwardList::ForwardList(const ValueType* rawArray, const size_t size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        push_front(rawArray[i]);
    }
}
ForwardList::ForwardList(const ForwardList& other) : list(nullptr), sz(other.sz)
{
    std::vector<ValueType> vals;
    Node* current = other.list;
    while (current != nullptr)
    {
        vals.push_back(current->data);
        current = current->next;
    }
    while (!vals.empty())
    {
        Node* temp = list;
        list = new Node;
        list->next = temp;
        list->data = vals[vals.size() - 1];
        vals.pop_back();
    }
    vals.clear();
}
ForwardList& ForwardList::operator=(const ForwardList& other)
{
    if (this == &other)
    {
        return *this;
    }
    std::vector<ValueType> vals;
    Node* current = other.list;
    while (current != nullptr)
    {
        vals.push_back(current->data);
        current = current->next;
    }
    while (!vals.empty())
    {
        Node* temp = list;
        list = new Node;
        list->next = temp;
        list->data = vals[vals.size() - 1];
        vals.pop_back();
    }
    sz = other.sz;
    return *this;
}
ForwardList::ForwardList(ForwardList&& other) : list(other.list), sz(other.sz)
{
    other.list = nullptr;
    other.sz = 0;
}
ForwardList& ForwardList::operator=(ForwardList&& other)
{
    if (this == &other)
    {
        return *this;
    }
    while (list != nullptr)
    {
        Node* temp = list;
        list = list->next;
        delete temp;
    }
    list = other.list;
    other.list = nullptr;
    sz = other.sz;
    other.sz = 0;
    return *this;
}
ForwardList::~ForwardList()
{
    clear();
}
void ForwardList::push_front(ValueType value)
{
    Node* temp = list;
    list = new Node;
    list->data = value;
    list->next = temp;
    sz++;
}
void ForwardList::pop_front()
{
    if (list != nullptr)
    {
        Node* temp = list;
        list = temp->next;
        delete temp;
        sz--;
    }
    
}
ValueType& ForwardList::front() const
{
    if (list != nullptr) { return list->data; }
    else { throw std::out_of_range("Элемента не существует."); } 
}
unsigned int ForwardList::size() const
{
    return sz;
}
void ForwardList::empty() const
{
    if (sz != 0) { std::cout<<"Список не пуст"<<std::endl; }
    else { std::cout<<"Список пуст"<<std::endl; }
}
void ForwardList::display() const
{
    Node* temp = list;
    while (temp != nullptr)
    {
        std::cout<<temp->data<<std::endl;
        temp = temp->next;
    }
}
void ForwardList::erase(ValueType value)
{
    while (list != nullptr && list->data == value)
    {
        Node* temp = list;
        list = list->next;
        delete temp;
        sz--;
    }
    Node* current = list;
    while (current != nullptr && current->next != nullptr)
    {
        if ((current->next)->data == value)
        {
            Node* todelete = current->next;
            current->next = (current->next)->next;
            delete todelete;
            sz--;
        }
        else { current = current->next; }
    }
    if (sz == 0) { list = nullptr; }
}
void ForwardList::clear()
{
    while (list != nullptr)
    {
        Node* temp = list->next;
        delete list;
        list = temp;
    }
    sz = 0;
}
