#pragma once
#include "MPair.h"
/*
Map class is just a wrapper for BPlusTree with MPairs

*/
template <typename K, typename V>
class MMap{
public:
    typedef BPlusTree<MPair<K, V>> map_base;
    //Iterator for the Map / Multimap uses the Bplustree iterator
    class Iterator {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = map_base::Iterator()) {
            _it = it;
        }
        MMap<K, V>::Iterator operator ++(int unused) {
            return MMap<K, V>::Iterator(++_it);
        }
        MMap<K, V>::Iterator operator ++() {
            return MMap<K, V>::Iterator(_it++);
        }
        MPair<K, V> operator *() {
            return *_it;
        }
        friend bool operator ==(const MMap<K, V>::Iterator& lhs, const MMap<K, V>::Iterator& rhs) {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const MMap<K, V>::Iterator& lhs, const MMap<K, V>::Iterator& rhs) {
            return !(lhs == rhs);
        }
        friend ostream& operator <<(ostream& outs, const Iterator& iter) {
            outs << iter._it;
            return outs;
        }
    private:
        typename map_base::Iterator _it;
    };

    MMap();

    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

    //  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    //  Operations:
    bool contains(const K& key);
    vector<V>& get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    MMap<K, V>::Iterator lower_bound(const K& key);
    MMap<K, V>::Iterator upper_bound(const K& key);

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me) {
        outs << print_me.mmap << endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V>> mmap;
};
template <typename K, typename V>
MMap<K,V>::MMap() {
    //Left blank
}
//All functions are just B+ tree functions wrapped
template <typename K, typename V>
void MMap<K,V>::insert(const K& k, const V& v) {
    MPair<K, V> p(k, v);
    mmap.insert(p);
}
template <typename K, typename V>
vector<V>& MMap<K,V>::operator[](const K& key) {
    MPair<K, V> pair(key);
    return get(key);
}
template <typename K, typename V>
vector<V>& MMap<K,V>::get(const K& key) {
    MPair<K, V> pair(key);
    return mmap.get(pair).value_list;
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key) {
    MPair<K, V> pair(key);
    return Iterator(mmap.find(pair));
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K,V>::begin() {
    return MMap<K, V>::Iterator(mmap.begin());
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end() {
    return MMap<K, V>::Iterator(mmap.end());
}
template <typename K, typename V>
bool MMap<K,V>::is_valid() {
    return mmap.is_valid();
}
template <typename K, typename V>
void MMap<K,V>::erase(const K& key) {
    MPair<K, V> pair(key);
    mmap.remove(pair);
}
template <typename K, typename V>
void MMap<K, V>::clear() {
    mmap.clear_tree();
}
template <typename K, typename V>
int MMap<K, V>::size() const {
    return mmap.size();
}
template <typename K, typename V>
bool MMap<K, V>::empty() const {
    return mmap.empty();
}
template <typename K, typename V>
bool MMap<K, V>::contains(const K& key)  {
    MPair<K, V> pair(key);
    return mmap.contains(pair);
}
template <typename K, typename V>
int MMap<K, V>::count(const K& key) {
    MPair<K, V> pair(key);
    return find(key).size();
}
template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key){
    return Iterator(mmap.lower_bound(key));
}
template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key){
    return Iterator(mmap.upper_bound(key));
}
template<typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const {
    return this[key];
}