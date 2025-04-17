#ifndef fwlist_H
#define fwlist_H
#include <cstddef>

#pragma once

using ValueType = double;


class ForwardList
{
    private:
        struct Node
        {
            ValueType data;
            struct Node* next;
        };
        Node* list;
        unsigned int sz;
    public:
        ForwardList();
        ForwardList(const ForwardList& other);
        ForwardList(const ValueType* rawArray, const size_t size);
        ForwardList& operator=(const ForwardList& other);
        ForwardList(ForwardList&& other);
        ForwardList& operator=(ForwardList&& other);
        ~ForwardList();
        void push_front(ValueType value);
        void pop_front();
        ValueType& front() const;
        unsigned int size() const;
        void empty() const;
        void display() const;
        void erase(ValueType value);
        void clear();
};

#endif