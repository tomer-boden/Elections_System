#pragma once

#include <iostream>
using namespace std;

template<class T>
class ListNode
{
    private:
        T& _data;
        ListNode<T>* _next;
    public:
        //Constructors
        ListNode(const T& data);
        ListNode(const T& data, const ListNode<T>* _nextPosition);
        //Distructor
        ~ListNode();

        //Getters
        const T& getData() const;
        const ListNode<T>* getNext() const;
        //Setters
        void setData(T& data);
        void setNext(ListNode<T>* next);

        friend ostream& operator<<(ostream& os, const ListNode<T>& node);
};

template <class T>
ListNode<T>::ListNode(const T& data) : _data(const_cast<T&>(data)), _next(nullptr)
{
}

template <class T>
ListNode<T>::ListNode(const T& data, const ListNode<T>* nextPosition) : _data(const_cast<T&>(data)), _next(const_cast<ListNode<T>*>(nextPosition))
{
}

template <class T>
ListNode<T>::~ListNode() {
    if (_next)
        delete _next;
}

template <class T>
ostream& operator<<(ostream& os, const ListNode<T>& node)
{
    os << node.data;
    return  os;
}

template <class T>
const T& ListNode<T>::getData() const{
    return _data;
}

template <class T>
const ListNode<T>* ListNode<T>::getNext() const {
    return _next;
}

template <class T>
void ListNode<T>::setData(T& data) {
    _data = data;
}

template <class T>
void ListNode<T>::setNext(ListNode<T>* next) {
    _next = next;
}