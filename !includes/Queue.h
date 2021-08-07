#pragma once
#include <iostream>
#include "..\..\..\Iterated List\Iterated List\list.h"
using namespace std;
template <typename T>
class Queue {
public:
    class Iterator {
    public:
        friend class Queue;
        Iterator() {
            _ptr = nullptr;
        }
        //Point Iterator to where p is pointing to
        Iterator(node<T>* p) {
            _ptr = p;
        }
        operator bool() {
            return (_ptr != nullptr);
        }                               
         //dereference operator (read only)
        T& operator *() {
            return &(_ptr->_item);
        }
        //member access operator (read only)
        T& operator ->() {
            return &(_ptr->_item);
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
            return (left._ptr == right._ptr);
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
        node<T>* _ptr;
    };
    Queue();

    //Big 3
    ~Queue();
    Queue(const Queue<T>& copyThis);
    Queue& operator =(const Queue& RHS);

    template <typename U>
    friend ostream& operator<<(ostream& outs, const Queue<U> q);

    typename List<T>::Iterator Push(T i); 
    T& Front();
    T Pop();
    bool Empty(); 
    int getSize();
private:
	List<T> _q;
	typename List<T>::Iterator _rear;
    int _size;
};
template <typename U>
ostream& operator<<(ostream& outs, const Queue<U> q) {
    outs << q._q;
    return outs;
}
template <typename T>
T& Queue<T>::Front() {
    return _q.item();
}
template <typename T>
typename List<T>::Iterator Queue<T>::Push(T i) {
    typename List<T>::Iterator temp = _q._InsertAfter(i,_rear);
    _rear = temp;
    _size++;
    return _rear;
}
template <typename T>
T Queue<T>::Pop() {
    //If q begin is nullptr we will assert (lower level functions)
    if (_q._Begin() == _rear) {
        //Set _rear to hold nullptr
        _rear = List<T>::Iterator();
    }
    _size--;
    return _q.Delete(_q._Begin());
}
template <typename T>
bool Queue<T>::Empty() {
    return _q.is_empty();
}
template <typename T>
Queue<T>::Queue() {
    _q = List<T>();
    _rear = typename List<T>::Iterator();
}
template <typename T>
Queue<T>::~Queue() {} //We dont have to do anything here
template <typename T>
Queue<T>::Queue(const Queue<T>& copyThis) {
    //Copy the list
    _q = copyThis._q;
    //Set the rear to your own rear
    _rear = _q._LastNode();
}
template <typename T>
Queue<T>& Queue<T>::operator =(const Queue& RHS) {
    if (this == &RHS) {
        return *this;
    }
    _q = RHS._q;
    _rear = _q._LastNode();
    return *this;
}
template <typename T>
int Queue<T>::getSize() {
    if (Empty()) {
        return 0;
    }
    else return _size;
}