#pragma once
#include "BPlusTree.h"
#include <vector>
#include <iostream>
using namespace std;
template <typename K, typename V>
struct MPair {
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
     //--------------------------------------------------------------------------------
    MPair(const K& k = K()) {
        key = k;
    }
    MPair(const K& k, const V& v) {
        key = k;
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist) {
        key = k;
        value_list = vlist;
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me) {
        cout << print_me.key << " : ";
        cout << print_me.value_list;
        return outs;
    }

    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        for (int i = 0; i < rhs.value_list.size(); i++) {
            V item = rhs.value_list[i];
            lhs.value_list.push_back(item);
        }
        return lhs;
    }
};