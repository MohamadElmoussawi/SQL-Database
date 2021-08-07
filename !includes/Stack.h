#pragma once
#pragma once
#include <iostream>
#include "..\..\..\Iterated List\Iterated List\list.h"
using namespace std;
template <typename T>
class Stack {
public:
    class Iterator {
    public:
        friend class Stack;
        Iterator() {
            _ptr = nullptr;
        }
        //Point Iterator to where p is pointing to
        Iterator(node<T>* p) {
            _ptr = p;
        }
        operator bool() {
            return (_ptr != nullptr);
        }                                //casting operator: true if _ptr not NULL
         //dereference operator (read only access)
        T operator *() {
            return (_ptr->_item);
        }
        //member access operator (read only access)
        T operator ->() {
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
    Stack();

    //The big 3
    ~Stack();
    Stack(const Stack<T>& copyThis);
    Stack& operator =(const Stack& RHS);

    template <typename U>
    friend ostream& operator<<(ostream& outs, const Stack<U> q);

    T& Top();
    Iterator Push(T i);
    Iterator Pop();
    bool Empty();
private:
    node<T>* _top;
};
template <typename T>
T& Stack<T>::Top() {
    return _top->_item;
}
template <typename U>
ostream& operator<<(ostream& outs, const Stack<U> q) {
    _print_list(q._top,outs);
    return outs;
}
template <typename T>
typename Stack<T>::Iterator Stack<T>::Push(T i) {
    node<T>* temp = _insert_head(_top,i);
    return Iterator(temp);
}
template <typename T>
//Serve the top first
typename Stack<T>::Iterator Stack<T>::Pop() {
    DeleteNode(_top, _top);
    return Iterator(_top);
}
template <typename T>
bool Stack<T>::Empty() {
    return (_top == nullptr);
}
template <typename T>
Stack<T>::Stack() {
    _top = nullptr;
}
template <typename T>
Stack<T>::~Stack() {
    //Clear the stack
    ClearList(_top);
}
template <typename T>
Stack<T>::Stack(const Stack<T>& copyThis) {
    _top = CopyList(copyThis._top);
}
template <typename T>
Stack<T>& Stack<T>::operator =(const Stack& RHS) {
    if (this == &RHS) {
        return *this;
    }
    //Clear the stack and deallocate
    ClearList(_top);
    //Copy other stack
    _top = CopyList(RHS._top);
    return *this;
}
