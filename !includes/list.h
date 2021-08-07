#pragma once
#include <iostream>
#include "..\..\!includes\Node\Node\node.h"
using namespace std;
template <typename T>
class List {
public:
    class Iterator {
    public:
        friend class List;                              //give access to list to access _ptr
        Iterator() {
            _ptr = nullptr;
        }
        //Point Iterator to where p is pointing to
        Iterator(node<T>* p) {
            _ptr = p;
        }
        operator bool() {
            if (_ptr == nullptr) {
                return false;
            }
            else return true;
        }                                //casting operator: true if _ptr not NULL
                                         //      this turned out to be a pain!
         //dereference operator
        T& operator *() {
            return &(_ptr->_item);
        }
        friend ostream& operator<<(ostream& outs, const List<T> l) {
            return _print_list(l._head_ptr, outs);
        }
        //member access operator
        T* operator ->() {
            return (_ptr->_item);
        }
        //true if _ptr is NULL
        bool is_null() {
            return (_ptr == nullptr);
        }
        //true if left != right
        friend bool operator !=(const Iterator& left,
            const Iterator& right) {
            return (left._ptr != right._ptr);
        }
        //true if left == right
        friend bool operator ==(const Iterator& left,
            const Iterator& right) {
            if (left._ptr == right._ptr) {
                return true;
            }
            else return false;
        }
        //member operator: ++it; or ++it = new_value
        Iterator& operator++() {
            this->_ptr = this->_ptr._next;
            return this;
        }
        //friend operator: it++
        friend Iterator operator++(Iterator& it,
            int unused) {
            it._ptr = it._ptr->_next;
            return it;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };
    List();
    //big 3 functions:
    ~List();
    List(const List<T>& copyThis);
    List& operator =(const List& RHS);
    //Functions that return iterators
    Iterator _InsertHead(T i);                           //insert at the head of list
    Iterator _InsertAfter(T i, Iterator iMarker);        //insert after marker
    Iterator _InsertBefore(T i, Iterator iMarker);       //insert before marker
    Iterator _InsertSorted(T i);                         //insert in a sorted list

    T Delete(List<T>::Iterator iMarker);        //delete node pointed to by marker
    void Print() const;
    Iterator Search(const T& key);                      //return Iterator to node [key]
    Iterator Prev(Iterator iMarker);                            //previous node to marker

    T& operator[](int index);                           //return item at position index
    Iterator _Begin() const;                                     //Iterator to the head node
    Iterator _End() const;                                       //Iterator to NULL
    Iterator _LastNode() const;                                  //Iterator to the last node

    bool is_empty() {
        return (_head_ptr == nullptr);
    }
    T& item() {
        return _head_ptr->_item;
    }
private:
    node<T>* _head_ptr;
    node<T>* insert_head(const T& item);
    node<T>* insert_after(T i,
        //insert i after iMarker
        node<T>* iMarker);

    node<T>* insert_before(T i,
        node<T>* iMarker);

    node<T>* insert_sorted(T i);
    T Delete(node<T>* iMarker);
    node<T>* search(const T& key);
    node<T>* Prev(node<T>* iMarker);
    node<T>* Begin() const;
    node<T>* End() const;
};

//All list functions just call lower level node functions
template <typename T>
List<T>::List() :_head_ptr(nullptr) {}

template <typename T>
node<T>* List<T>::insert_head(const T& item) {
    return _insert_head(_head_ptr, item);
}

template <typename T>
List<T>::~List() {
    ClearList(_head_ptr);
}
template <typename T>
List<T>::List(const List<T>& copyThis) {
    _head_ptr = CopyList(copyThis._head_ptr);
}
template <typename T>
List<T>& List<T>::operator =(const List& RHS) {
    if (this == &RHS) {
        return *this;
    }
    //deallocate  and clear old list
    ClearList(_head_ptr);
    _head_ptr = CopyList(RHS._head_ptr);
    return *this;
}
template <typename T>
node<T>* List<T>::insert_after(T i,
    //insert i after iMarker
    node<T>* iMarker) {
    return InsertAfter(_head_ptr, iMarker, i);
}
template <typename T>
node<T>* List<T>::insert_before(T i,
    node<T>* iMarker) {
    return InsertBefore(_head_ptr, iMarker, i);
}
template <typename T>
node<T>* List<T>::insert_sorted(T i) {
    return InsertSorted(_head_ptr, i);
}
template <typename T>
T List<T>::Delete(node<T>* iMarker) {
    return DeleteNode(_head_ptr, iMarker);
}
template <typename T>
void List<T>::Print() const {
    _print_list(_head_ptr);
}
template <typename T>
node<T>* List<T>::search(const T& key) {
    return SearchList(_head_ptr, key);
}
template <typename T>
node<T>* List<T>::Prev(node<T>* iMarker) {
    return PreviousNode(_head_ptr, iMarker);
}
template <typename T>
T& List<T>::operator[](int index) {
    return At(_head_ptr, index);
}
template <typename T>
node<T>* List<T>::Begin() const {
    return _head_ptr;
}
template <typename T>
node<T>* List<T>::End() const {
    return LastNode(_head_ptr);
}
template <typename T>
typename List<T>::Iterator List<T>::_InsertHead(T i) {
    node<T>* temp = insert_head(i);
    return Iterator(temp);
}
template <typename T>
typename List<T>::Iterator List<T>::_InsertAfter(T i, Iterator iMarker) {
    node<T>* temp = insert_after(i,iMarker._ptr);
    return Iterator(temp);
}
template <typename T>
typename List<T>::Iterator List<T>::_InsertBefore(T i, Iterator iMarker) {
    node<T>* temp = insert_before(i, iMarker._ptr);
    return Iterator(temp);
}
template <typename T>
typename List<T>::Iterator List<T>::_InsertSorted(T i) {
    node<T>* temp = insert_sorted(i);
    return Iterator(temp);
}
template <typename T>
T List<T>::Delete(typename List<T>::Iterator iMarker) {
    return Delete(iMarker._ptr);
}
template <typename T>
typename List<T>::Iterator List<T>::Search(const T& key) {
    node<T>* temp = search(key);
    return Iterator(temp);
}

template <typename T>
typename List<T>::Iterator List<T>::Prev(Iterator iMarker) {
    node<T>* temp = Prev(iMarker._ptr);
    return Iterator(temp);
}
template <typename T>
typename List<T>::Iterator List<T>::_Begin() const {
    return Iterator(Begin());
}
template <typename T>
typename List<T>::Iterator List<T>::_End() const {
    return Iterator(End());
}
template <typename T>
typename List<T>::Iterator List<T>::_LastNode() const {
    node<T>* temp = LastNode(_head_ptr);
    return Iterator(temp);
}