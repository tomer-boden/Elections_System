#pragma once

#include <iostream>
#include "listNode.h"
using namespace std;

//Linked List one way template
template<class T>
class LinkedList
    {
    private:
        ListNode<T>* _head;
        ListNode<T>* _tail;
        int _listSize;

        LinkedList& operator+=(ListNode<T>& node);
        LinkedList& operator-=(ListNode<T>& node);
        
    public:
        class LinkedListIter
        {
            friend class LinkedList;
            private:
                ListNode<T>* pCurrentNode;
            public:

                LinkedListIter() : pCurrentNode(_head) { }
                LinkedListIter(ListNode<T>* pNode) : pCurrentNode(pNode) { }

                LinkedListIter& operator=(ListNode<T>* pNode)
                {
                    this->pCurrentNode = pNode;
                    return *this;
                }
                LinkedListIter& operator++()
                {
                    if (pCurrentNode)
                        pCurrentNode = pCurrentNode->next;
                    return *this;
                }
                LinkedListIter operator++(int)
                {
                    LinkedListIter iterator = *this;
                    ++* this;
                    return iterator;
                }
                bool operator!=(const LinkedListIter& iterator) { return pCurrentNode != iterator.pCurrentNode; }
                bool operator==(const LinkedListIter& iterator) { return pCurrentNode == iterator.pCurrentNode; }
                T& operator*() { return pCurrentNode->data; }
            };
        class LinkedListConstIterator
        {
            friend class LinkedList;
            private:
                ListNode<T>* pCurrentNode;
            public:

                LinkedListConstIterator() : pCurrentNode(_head) { }
                LinkedListConstIterator(ListNode<T>*pNode) : pCurrentNode(pNode) { }

                LinkedListConstIterator& operator=(ListNode<T>*pNode)
                {
                    this->pCurrentNode = pNode;
                    return *this;
                }
                LinkedListConstIterator& operator++()
                {
                    if (pCurrentNode)
                        pCurrentNode = const_cast<ListNode<T>*>(pCurrentNode->getNext());
                    return *this;
                }
                LinkedListConstIterator operator++(int)
                {
                    LinkedListConstIterator iterator = *this;
                    ++* this;
                    return iterator;
                }
                bool operator!=(const LinkedListConstIterator& iterator) { return pCurrentNode != iterator.pCurrentNode; }
                bool operator==(const LinkedListConstIterator& iterator) { return pCurrentNode == iterator.pCurrentNode; }
                const T& operator*() { return pCurrentNode->getData(); }
         };


        //Constructor
        LinkedList() : _head(nullptr), _tail(nullptr), _listSize(0) {}
        LinkedList(LinkedList<T>& otherLinkedList);
        //Distructor
        ~LinkedList() {
            if (_head)
                delete _head;
        }

        LinkedListIter begin() { return LinkedListIter(_head); }
        LinkedListIter end() { return LinkedListIter(_tail); }
        LinkedListConstIterator cbegin() const { return LinkedListConstIterator(_head); }
        LinkedListConstIterator cend() const { return LinkedListConstIterator(_tail); }

        //Gettes
        ListNode<T>* getHead() const { return _head; }
        int getlListSize() const { return _listSize; }
        const T& getDataByIndex(int index) const {
            LinkedListConstIterator iter = cbegin();
            for (int i = 0; i < index; i++) {
                iter++;
            }
            return *iter;
        }

        LinkedListIter erase(LinkedListIter position) {
            ListNode<T>* toDelete = position.pCurrentNode;
            position.pCurrentNode->setNext(position.pCurrentNode->getNext()->getNext());
            if (toDelete == _tail) 
                _tail = position.pCurrentNode;
            delete toDelete;
            return position;
        }

        LinkedListIter insert(LinkedListIter position, const T& value) {
            ListNode<T>* newNode = new ListNode<T>(value, position.pCurrentNode->getNext());
            if (position.pCurrentNode == _tail)
                _tail = newNode;
            position.pCurrentNode->setNext(newNode);
            return position;
        }

        void add(const T& data); //add alwayes to the end of the list
        bool isEmpty() const { return _listSize == 0; }
        bool isDataInList(const T& data) const;
        
        const LinkedList& operator=(const LinkedList& otherList);
        friend ostream& operator<<(ostream& os, const LinkedList& list) {
            LinkedListConstIterator iterator = list.cbegin();
            LinkedListConstIterator end = ++list.cend();
            for (iterator; iterator != end; iterator++)
            {
                os << *iterator;
            }
            return os;
        }
 };

 template <class T>
 LinkedList<T>::LinkedList(LinkedList<T>& otherLinkedList) {
     *this = otherLinkedList;
 }

 template <class T>
 void LinkedList<T>::add(const T& data)
 {
    int current = _listSize;
     *this += *(new ListNode<T>(data));
 }

 template <class T>
 bool LinkedList<T>::isDataInList(const T& data) const
 {
     if (!_head)
         return false;
     for (LinkedListIter iterator = LinkedListIter(_head); iterator != LinkedListIter(nullptr); iterator++)
     {
         if (*iterator == data)
             return  true;
     }
     return false;
 }

 template <class T>
 const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& otherList) {
     if (_head)
        _head;
     ListNode<T>* other_head = otherList._head;
     while (other_head)
     {
         add(other_head->getData());
         other_head = const_cast<ListNode<T>*>(other_head->getNext());
     }
     _listSize = otherList._listSize;
     return *this;
 }

 template <class T>
 LinkedList<T>& LinkedList<T>::operator+=(ListNode<T>& node)
 {
     if (_head)
     {
         ListNode<T>* currentNode = _head;
         while (currentNode->getNext())
             currentNode = const_cast<ListNode<T>*>(currentNode->getNext());
         currentNode->setNext(&node);
     }
     else
     {
         _head = &node;
         _head->setNext(nullptr);
     }
     _listSize++;
     _tail = &node;
     return *this;
 }

 template <class T>
 LinkedList<T>& LinkedList<T>::operator-=(ListNode<T>& node)
 {
     if (_head)
     {
         if (*_head == node)
         {
             ListNode<T>* temp = _head->next;
             _head->next = nullptr;
             delete _head;
             _head = temp;
             _listSize--;
             if (_listSize == 0)
             {
                 _tail = nullptr;
             }
         }
         else if (_listSize > 1)
         {
             ListNode<T>* currentNode = _head;
             ListNode<T>* currentPrevNode = nullptr;
             while (currentNode)
             {
                 if (*currentNode == node)
                 {
                     if (currentNode->next)
                     {
                         currentPrevNode->next = currentNode->next;
                         currentNode->next = nullptr;
                     }
                     else
                     {
                         currentPrevNode->next = nullptr;
                         _tail = currentPrevNode;
                     }
                     delete currentNode;
                     _listSize--;
                     break;
                 }
                 currentPrevNode = currentNode;
                 currentNode = currentNode->next;
             }
         }
     }
     return *this;
 }
