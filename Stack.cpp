#include <iostream>
#include "Stack.h"
#include "StackImplementation.h"
#include "StackRealisation.h"

Stack::Stack(StackContainer container) : _containerType(container)
{
    switch (container)
    {
        case StackContainer::Vector:
            _pimpl = new VectorStack;
            break;
        case StackContainer::List:
            _pimpl = new FWListStack;
            break;
    }
}
// элементы массива последовательно подкладываются в стек
Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container) : _containerType(container)
{
    switch (container)
    {
        case StackContainer::Vector:
            _pimpl = new VectorStack(valueArray, arraySize);
            break;
        case StackContainer::List:
            _pimpl = new FWListStack(valueArray, arraySize);
            break;
    }
}
Stack::Stack(const Stack& copyStack) : _containerType(copyStack._containerType)
{
    *this = copyStack;
}
Stack& Stack::operator=(const Stack& copyStack)
{
    if (this != &copyStack)
    {
        _containerType = copyStack._containerType;
        delete _pimpl;
        switch (_containerType)
        {
            case StackContainer::Vector:
                _pimpl = new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl));
                break;
            case StackContainer::List:
                _pimpl = new FWListStack(*dynamic_cast<FWListStack*>(copyStack._pimpl));
                break;
        }
    }
    return *this;
}
Stack::Stack(Stack&& moveStack) noexcept
{
    *this = std::move(moveStack);
}
Stack& Stack::operator=(Stack&& moveStack) noexcept
{
    if (this != &moveStack)
    {
        delete _pimpl;
        _containerType = moveStack._containerType;
        _pimpl = moveStack._pimpl;
        moveStack._pimpl = nullptr;
    }
    return *this;
}
Stack::~Stack() { delete _pimpl; }
// добавление в хвост
void Stack::push(const ValueType& value) { _pimpl->push(value); }
// удаление с хвоста
void Stack::pop() { _pimpl->pop(); }
// посмотреть элемент в хвосте
const ValueType& Stack::top() const { return _pimpl->top(); }
// проверка на пустоту
bool Stack::isEmpty() const { return _pimpl->isEmpty(); }
// размер 
size_t Stack::size() const { return _pimpl->size(); }
