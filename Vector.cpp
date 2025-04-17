#include "Vector.h"
#include <iostream>

Vector::Vector(const ValueType& value, size_t size) : _size(size), _capacity((size * 2))
{
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < size; i++)
    {
        _data[i] = value;
    }
}
Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef)
{
    if (_capacity != 0)
    {
        if (rawArray != nullptr)
        {
            _data = new ValueType[_capacity];
            for (size_t i = 0; i < size; i++)
            {
                _data[i] = rawArray[i];
            }
        }
    }
}
Vector::Vector(const Vector& other) : _size(other._size), _capacity(other._size)
{
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}
Vector& Vector::operator=(const Vector& other)
{
    if (this == &other) { return *this; }
    _size = other._size;
    _capacity = other._size;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
    return *this;
}
Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}
Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other) { return *this; }
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    return *this;
}
Vector::~Vector() { delete[] _data; }
void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        if (_capacity == 0) { _capacity = 1; }
        _capacity *= _multiplicativeCoef;
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
    _data[_size] = value;
    _size++;
}
void Vector::pushFront(const ValueType& value)
{
    if (_capacity == 0)
    {
        _capacity = _multiplicativeCoef;
        _data = new ValueType[_capacity];
    }
    if (_size == _capacity)
    {
        _capacity *= _multiplicativeCoef;
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 1; i < _size + 1; i++)
        {
            temp[i] = _data[i - 1];
        }
        delete[] _data;
        _data = temp;
    }
    else
    {
        for (size_t i = _size; i > 0; i--)
        {
            _data[i] = _data[i - 1];
        }
    }
    _data[0] = value;
    _size++;
}
void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos >= 0 && pos < _size + 1)
    {
        if (_size == _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size + 1; i++)
        {
            if (i < pos) { temp[i] = _data[i]; }
            if (i == pos) { temp[i] = value; }
            if (i > pos) { temp[i] = _data[i - 1]; }
        }
        delete[] _data;
        _data = temp;
        _size++;
    }
}
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (pos >= 0 && pos < _size + 1)
    {
        _size += size;
        while (_size >= _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            if (i < pos) { temp[i] = _data[i]; }
            if (i >= pos && i < pos + size) { temp[i] = values[i - pos]; }
            if (i >= pos + size) { temp[i] = _data[i - size]; }
        }
        delete[] _data;
        _data = temp;
    }
}
void Vector::insert(const Vector& vector, size_t pos)
{
    if (pos >= 0 && pos < _size + 1)
    {
        _size += vector._size;
        while (_size >= _capacity) { _capacity *= _multiplicativeCoef; }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            if (i < pos) { temp[i] = _data[i]; }
            if (i >= pos && i < pos + vector._size) { temp[i] = vector[i - pos]; }
            if (i >= pos + vector._size) { temp[i] = _data[i - vector._size]; }
        }
        delete[] _data;
        _data = temp;
    }
}
ValueType& Vector::operator[](size_t idx)
{
    if (_size == 0) { throw std::out_of_range("Index out of range"); }
    if (idx >= 0 && idx < _size) { return _data[idx]; }
    else { throw std::out_of_range("Index out of range"); }
}
const ValueType& Vector::operator[](size_t idx) const
{
    if (idx >= 0 && idx < _size) { return _data[idx]; }
    else { throw std::out_of_range("Index out of range"); }
}
size_t Vector::size() const { return _size; }
size_t Vector::capacity() const { return _capacity; }
double Vector::loadFactor() const { return double(_size) / _capacity; }
long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] == value) { return i; }
    }
    return -1;
}
void Vector::reserve(size_t capacity)
{
    if (capacity > _capacity)
    {
        _capacity = capacity;
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
        {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
}
void Vector::shrinkToFit()
{
    _capacity = _size;
    ValueType *temp = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        temp[i] = _data[i];
    }
    delete[] _data;
    _data = temp;
}
void Vector::popBack()
{
    if (_size > 0)
    {
        _size--;
    }
    else { throw std::length_error("Vector is empty, nothing to delete"); }
}
void Vector::popFront()
{
    if (_size > 0)
    {
        for (size_t i = 1; i < _size; i++)
        {
            _data[i - 1] = _data[i];
        }
        _size--;
    }
    else { throw std::length_error("Vector is empty, nothing to delete"); }
}
void Vector::erase(size_t pos, size_t count)
{
    if (pos < _size)
    {
        if ((pos + count) > _size) { count = _size - pos; }
        ValueType *temp = new ValueType[_capacity];
        size_t j = 0;
        for (size_t i = 0; i < _size; i++)
        {
            if (i < pos || i > pos + count - 1) { temp[i - j] = _data[i]; }
            else { j++; }
        }
        _size -= count;
        delete[] _data;
        _data = temp;
    }
}
void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos < _size && endPos >= beginPos)
    {
        if (endPos >= _size) { endPos = _size; }
        ValueType *temp = new ValueType[_capacity];
        size_t j = 0;
        for (size_t i = 0; i < _size; i++)
        {
            if (i < beginPos || i >= endPos) { temp[i - j] = _data[i]; }
            else { j++; }
        }
        _size -= endPos - beginPos;
        delete[] _data;
        _data = temp;
    }
}
Vector::Iterator Vector::begin() { return Iterator(_data); }
Vector::Iterator Vector::end() { return Iterator(_data + _size); }
Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}
ValueType& Vector::Iterator::operator*() { return *_ptr; }
const ValueType& Vector::Iterator::operator*() const { return *_ptr; }
ValueType* Vector::Iterator::operator->() { return _ptr; }
const ValueType* Vector::Iterator::operator->() const { return _ptr; }
Vector::Iterator Vector::Iterator::operator++()
{
    _ptr++;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator temp = *this;
    _ptr++;
    return temp;
}
bool Vector::Iterator::operator==(const Iterator& other) const { return (_ptr == other._ptr); }
bool Vector::Iterator::operator!=(const Iterator& other) const { return !(*this == other); }
