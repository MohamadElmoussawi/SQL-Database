#pragma once
#include <iostream> 
#include <cassert>
using namespace std;
template <typename T>
struct node {
    T _item;
    node<T>* _next;
    node(const T& item = T(), node<T>* next = nullptr) :
        _item(item), _next(next) {}

    friend ostream& operator<<(ostream& outs, const node<T> n) {
        outs << "[" << n._item << "]->";
        return outs;
    }
};


template <typename T>
node<T>* _InsertSortedAndAdd(node<T>*& head,     
    T item,
    bool ascending = true);

template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item);

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs = cout);

//======================

template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item) {
    //insert the item at the head of the list: make it the first j
    //      link in the chain.

    //1: create a new node:
    node<T>* temp = new node<T>(item);
    //2. point (the next field of) this new node to where head is pointing to
    temp->_next = head_ptr;

    //3. point head to this new node:
    head_ptr = temp;

    return head_ptr;
}

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs) {
    outs << "H->";
    //Prints the list
    for (node<T>* w = head_ptr;
        w != nullptr;
        w = w->_next) {
        outs << *w;
    }
    outs << "|||";
    return outs;
}

template <typename T>
//recursive fun! :)
void PrintList_backwards(node<T>* head) {
    if (head != nullptr) {
        //Call printlist_backwards on next recursively
        PrintList_backwards(head->_next);
        //This will print only at the end of all the previous function calls
        cout << *head;
    }
    else cout << "H->";
}        

template <typename T>
node<T>* SearchList(node<T>* head, T key) {
    assert(head != nullptr);
    if (head->_item == key) {
        //If we found the key
        return head;
    }
    else if (head->_next == nullptr) {
        //If we are at end and it can not be found return the head
        //Make sure this does not BREAK anything
        return nullptr;
    }
    else {
        //Search for key in the next element
        return SearchList(head->_next, key);
    }
}

template <typename T>
node<T>* InsertAfter(node<T>*& head,        //insert after ptr
    node<T>* afterThis,
    T insertThis) {
    //Insert head if at the head 
    if (head == nullptr) {
        _insert_head(head, insertThis);
        return head;
    }
    else {
        for (node<T>* w = head;
            w != nullptr;
            w = w->_next) {
            if (w == afterThis) {
                //create a pointer to a new node
                node<T>* temp = new node<T>(insertThis);
                //Assign the old afterThis.next to the new node
                temp->_next = afterThis->_next;
                //Replace the _next sticker for afterThis to be the new node
                afterThis->_next = temp;
                return temp;
            }
        }
    }
    //If the afterThis pointer cannot be found
    return nullptr;
}

template <typename T>
node<T>* InsertBefore(node<T>*& head,       //insert before ptr
    node<T>* beforeThis,
    T insertThis) {
    if (beforeThis == head){
        //Create new node
        node<T>* temp = new node<T>(insertThis);
        //Set next to head
        temp->_next = head;
        //Reassign the head pointer 
        head = temp;
        //Return the newly created node
        return temp;
    }
    for (node<T>* w = head;
        w != nullptr;
        w = w->_next) {
        if (w->_next == beforeThis) {
            //Insert after the current node 
            return InsertAfter(head, w, insertThis);
        }
    }
}

template <typename T>
node<T>* PreviousNode(node<T>* head,        //ptr to previous node
    node<T>* prevToThis) {
    if (prevToThis == head) {
        //Return nullptr if our previous is on the head
        return head;
    }
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        if (w->_next == prevToThis) {
            return w;
        }
    }   
    return nullptr;
}

template <typename T>
T DeleteNode(node<T>*& head,                 //delete, return item
    node<T>* deleteThis) {
    assert(head != nullptr);
    if (deleteThis == head) {
        //Set head to be the next node
        head = head->_next;
        //Save the item so we can return it
        T hold = deleteThis->_item;
        //Deallocate the space allocated for the node
        delete deleteThis;
        return hold;
    }
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        if (w->_next == deleteThis) {
            //If the next thing is what we will delete
            w->_next = deleteThis->_next;
            T hold = deleteThis->_item;
            delete deleteThis;
            return hold;
        }
    }
    //If deleteThis is not in the list
    assert("Thing to delete not found");
    //Might need to add something here
    //return nullptr;
}
template <typename T>
//duplicate the list...
node<T>* CopyList(node<T>* head) {
    //If we are copying nullptr then return nullptr
    if (head == nullptr) {
        return nullptr;
    }
    node<T>* theCopy = nullptr;
    node<T>* hold = nullptr;
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        //Insert into the copied list the item needed
        hold = InsertAfter(theCopy, hold, w->_item);
    }
    return theCopy;
}          

template <typename T>
void ClearList(node<T>*& head) {
    //Deletes the nodes one by one
    for (node<T>* w = head; w != nullptr;) {
        node<T>* hold = w->_next;
        DeleteNode(head, w);
        w = hold;
    }
}                   

template <typename T>
//_item at this position
T& At(node<T>* head, int pos) {
    int count = 0;
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        if (count == pos) {
            return w->_item;
        }
        count++;
    }
}
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* InsertSorted(node<T>*& head,       //insert
    T item,
    bool ascending = true) {
    if (head == nullptr) {
        return _insert_head(head, item);
    }
    if (ascending && head->_item > item) {
        return _insert_head(head, item);
    }
    if (!ascending && head->_item < item) {
        return _insert_head(head,item);
    }
    node<T>* afterThis = WhereThisGoes(head, item, ascending);
    return InsertAfter(head, afterThis, item);
}
    
template <typename T>
node<T>* WhereThisGoes(node<T>* head,         //node after which this
    T item,                //    item goes
    bool ascending = true) {
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        if (w->_next == nullptr) {
            return w;
        }
        if (ascending && w->_next->_item > item) {
            return w;
        }
        else if (!ascending && w->_next->_item < item) {
            return w;
        }
    }
    //return nullptr;
}

template <typename T>
node<T>* _InsertSortedAndAdd(node<T>*& head,       //insert
    T item,
    bool ascending) {
    node<T>* hold  = SearchList(head, item);
    if (hold != nullptr) {
        //cout << "In here";
        hold->_item += item;
        return hold;
    }
    else return InsertSorted(head, item,ascending);
}
template <typename T>
//Last Node in the list
node<T>* LastNode(node<T>* head) {
    for (node<T>* w = head; w != nullptr; w = w->_next) {
        //If the next node is nullptr we are at the end
        if (w->_next == nullptr) {
            return w;
        }
    }
    return nullptr;
}