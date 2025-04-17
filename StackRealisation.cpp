#include <iostream>
#include "StackRealisation.h"

VectorStack::VectorStack(const ValueType* rawArray, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        _data.pushBack(rawArray[i]);
    }
}
VectorStack::VectorStack(const VectorStack& other)
{
    _data = other._data;
}
VectorStack& VectorStack::operator=(const VectorStack& other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}
void VectorStack::push(const ValueType& value) { _data.pushFront(value); }
void VectorStack::pop() { _data.popFront(); }
const ValueType& VectorStack::top() const { return _data[0]; }
bool VectorStack::isEmpty() const { return (_data.size() == 0 ? true : false); }
size_t VectorStack::size() const { return _data.size(); }

FWListStack::FWListStack(const ValueType* rawArray, const size_t size)
{
    for (size_t i = size - 1; i >= 0; i--)
    {
        _data.push_front(rawArray[i]);
    }
}
FWListStack::FWListStack(const FWListStack& other)
{
    _data = other._data;
}
FWListStack& FWListStack::operator=(const FWListStack& other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}
void FWListStack::push(const ValueType& value) { _data.push_front(value); }
void FWListStack::pop() { _data.pop_front(); }
const ValueType& FWListStack::top() const { return _data.front(); }
bool FWListStack::isEmpty() const { return (_data.size() == 0 ? true : false); }
size_t FWListStack::size() const { return _data.size(); }