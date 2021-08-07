#pragma once
#include <iostream>
#include "BPlusTree.h"
#include "Pair.h"
template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    //Map iterator pretty similar to mmap iterator
    class Iterator {
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = map_base::Iterator()) {
            _it = it;
        }
        Map<K, V>::Iterator operator ++(int unused) {
            return Map<K, V>::Iterator(++_it);
        }
        Map<K, V>::Iterator operator ++() {
            return Map<K, V>::Iterator(_it++);
        }
        Pair<K, V> operator *() {
            return *_it;
        }
        friend bool operator ==(const Map<K, V>::Iterator& lhs, const Map<K, V>::Iterator& rhs) {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Map<K, V>::Iterator& lhs, const Map<K, V>::Iterator& rhs) {
            return !(lhs == rhs);
        }
        friend ostream& operator <<(ostream& outs, const Iterator& iter) {
            outs << iter._it;
            return outs;
        }
        
    private:
        typename map_base::Iterator _it;
    };
    
    Map();
    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    V& operator[](const K& key);


    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

    //  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target);


    bool is_valid() { return map.is_valid(); }

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me) {
        outs << print_me.map << endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};
//All are just wrapper functions
template <typename K, typename V>
Map<K,V>::Map() {
    key_count = 0;
}
template <typename K, typename V>
int Map<K, V>::size() const{
    return key_count;
}
template <typename K, typename V>
bool Map<K,V>::empty() const {
    return map.empty();
}
template <typename K, typename V>
void Map<K,V>::insert(const K& k, const V& v) {
    Pair<K,V> p(k, v);
    map.insert(p);
}

template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::begin() {
    return Map<K,V>::Iterator(map.begin());
}
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::end() {
    return Map<K, V>::Iterator(map.end());
}
template <typename K, typename V>
V& Map<K,V>::operator[](const K& key) {
    Pair<K, V> pair(key, V());
    //We want address of the value 
    return map.get(pair).value;
}
template <typename K, typename V>
void Map<K, V>::erase(const K& key) {
    Pair<K, V> pair(key, V());
    map.remove(pair);
}
template <typename K, typename V>
void Map<K, V>::clear() {
    map.clear_tree();
}
template <typename K, typename V>
V Map<K, V>::get(const K& key) {
    Pair<K, V> pair(key, V());
    return map.get(pair);
}
//  Operations:
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::find(const K& key) {
    Pair<K, V> pair(key, V());
    return Iterator(map.find(pair));
}
template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V>& target)  {
    return map.contains(target);
}