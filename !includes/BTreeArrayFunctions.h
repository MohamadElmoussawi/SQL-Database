#pragma once
#include <iostream>
#include <vector>
using namespace std;
//Old shift right function (from last semester)
template <typename T>
void shiftRight(T* arr, int& size, int index, T toInsert);
//Shift left helper function 
template <typename T>
void shiftLeft(T* arr, T* toRemove, int& size);
//return the larger of the two items
template <class T>
T maximal(const T& a, const T& b) {
    return a > b ? a : b;
}

//Swaps two elements
template <class T>
void swaps(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

//return index of the largest item in data
template <class T>
int index_of_maximal(T data[], int n) {
    int index = 0;
    T currentMax = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] > currentMax) {
            currentMax = data[i];
            index = i;
        }
    }
    return index;
}

//insert entry into the sorted array
//data with length n
template <class T>
void ordered_insert(T data[], int& n, T entry) {
    //This makes it the responsibility of hte caaller to make sure 
    //That we do not go over the capacity so...
    int finalIndex = n - 1;
    int i;
    for (i = n - 1; (i >= 0 && data[i] > entry); i--) {
        //For loop condition finds the spot and shifts right
        data[i + 1] = data[i];

    }
    data[i + 1] = entry;
    n++;
}

//return the first element in data that is
//not less than entry
template <class T>
int first_ge(const T data[], int n, const T& entry) {
    int i;
    for (i = 0; i < n && data[i] < entry; i++) {
        //We don't do anything here its all handeled in the forloop condition
    }
    return i;
}

//append entry to the right of data
template <class T>
void attach_item(T data[], int& n, const T& entry) {
    data[n] = entry;
    n++;
}

//insert entry at index i in data
template <class T>
void insert_item(T data[], int i, int& n, T entry) {
    n++;
    shiftRight(data, n, i, entry);
}


//remove the last element in data and place
//it in entry
template <class T>
void detach_item(T data[], int& n, T& entry) {
    entry = data[n - 1];
    n--;
}

//delete item at index i and place it in entry
template <class T>
void delete_item(T data[], int i, int& n, T& entry) {
    T* pointerToThingRemoved = data + i;
    entry = data[i];
    shiftLeft(data, pointerToThingRemoved, n);
}

//append data2 to the right of data1
template <class T>
void merge(T data1[], int& n1, T data2[], int& n2) {
    for (int i = 0; i < n2; i++) {
        data1[n1 + i] = data2[i];
    }
    n1 += n2;
}

//move n/2 elements from the right of data1
//and move to data2
template <class T>
void split(T data1[], int& n1, T data2[], int& n2) {
    int tomove = n1 / 2;
    for (int i = 0; i < tomove; i++) {
        if (n1 % 2 == 0)
            data2[i] = data1[tomove + i];
        else
            data2[i] = data1[tomove + i + 1];
    }
    n1 -= tomove;
    n2 = tomove;
}

//copy src[] into dest[]
template <class T>
void copy_array(T dest[], const T src[],
    int& dest_size, int src_size) {
    for (int i = 0; i < src_size; i++) {
        *dest = *src; //dereference both pointers and assign the
                              //value at source to destination
        src++; //increment source pointer (point to next element)    
        dest++; //increment destination pointer (point to next element)
    }
    dest_size = src_size;
}

//print array data
template <class T>
void print_array(const T data[], int n, int pos = 0) {
    for (int i = pos; i < n; i++) {
        cout << data[i] << " ";
    }
}

//Old shift right insert (from last semester) 
template <typename T>
void shiftRight(T* arr, int& size, int index, T toInsert) {
    T* end = arr + size;
    //Temp to store old values
    T temp = *(arr + index);
    T temp2 = *arr; //temporary initilization
    for (T* w = arr + index + 1; w < end; w++) {
        //Store second old value in temp 2
        temp2 = *w;
        //Replace the thing  that the walker is pointing at with temp
        *w = temp;
        //Reassign temp to be temp 2
        temp = temp2;
    }
    //Place the thing you wanted to be inserted inside the array
    T* needsReplacing = arr + index;
    *needsReplacing = toInsert;
}
template <typename T>
void shiftLeft(T* arr, T* toRemove, int& size) {
    //Loop from the index needed to be removed to the end
    for (T* end = arr + size; toRemove < end; toRemove++) {
        *toRemove = *(toRemove + 1);
    }
    size--;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << ", ";
    }
    return outs;
}

template <typename T, typename U>
vector<T>& operator +=(vector<T>& list, const U& addme) {
    list.push_back(addme);
    return list;
}




//item > all data[i]
template <class T>
bool is_gt(const T data[], int n, const T& item);

//item <= all data[i]
template <class T>
bool is_le(const T data[], int n, const T& item);