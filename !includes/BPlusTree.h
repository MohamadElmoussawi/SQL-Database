#pragma once
#include <iostream>
#include <cassert>
#include <iomanip>
#include "BTreeArrayFunctions.h"
using namespace std;
template <typename T>
class BPlusTree{ 
public:
    class Iterator {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it = nullptr, int _key_ptr = 0) :it(_it), key_ptr(_key_ptr) {}

        T operator *() {
            return it->data[key_ptr];
        }
        Iterator operator++(int un_used) {
            key_ptr++;
            if (key_ptr == it->data_count) {
                it = it->next;
                key_ptr = 0;
            }
            return *this;
        }
        Iterator operator++() {
            Iterator hold = Iterator(it, key_ptr);
            key_ptr++;
            if (key_ptr == it->data_count) {
                it = it->next;
                key_ptr = 0;
            }
            return hold;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }
        void print_Iterator() {
            cout << "[" << it->data[key_ptr] << "]";
        }
        bool is_null() { return !it; }
    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& temp_next = nullptr);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other);
    bool contains(const T& entry);        //true if entry can be found in the array

    T& get(const T& entry);                     //return a reference to entry in the tree
    const T& get(const T& entry)const;          //return a reference to entry in the tree
    T& get_existing(const T& entry);            //return a reference to entry in the tree

    Iterator find(const T& entry);              //return an iterator to this key. NULL if not there.`

    //Upper and lower bound?
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

    void print_tree(int level = 0,
        ostream& outs = cout) const; //print a readable version of the tree
    friend ostream& operator<<(ostream& outs,
        const BPlusTree<T>& print_me) {
        print_me.print_tree(0, outs);
        return outs;
    }
    bool is_valid();

    Iterator begin();
    Iterator end();
    T* find_ptr(const T& entry);        //return a pointer to this key. NULL if not there.


private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                       //true if duplicate keys may be inserted
    int data_count;                     //number of data elements
    T data[MAXIMUM + 1];                //holds the keys
    int child_count;                    //number of children
    BPlusTree* subset[MAXIMUM + 2];     //subtrees
    BPlusTree* next;
    bool is_leaf() const{
        return child_count == 0;
    }        //true if this is a leaf node


    //insert element functions
    void loose_insert(const T& entry);  //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);             //fix excess of data elements in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage of data elements in child i
                                        // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);        //entry := leftmost leaf
    void get_biggest(T& entry);         //entry := rightmost leaf
    //Remove biggest not needed
    void remove_biggest(T& entry);      //remove the biggest child of this tree->entry
    void transfer_left(int i);          //transfer one element LEFT from child i
    void transfer_right(int i);         //transfer one element RIGHT from child i
    BPlusTree<T>* merge_with_next_subset(int i);    //merge subset i with subset i+1

};
//---------------------------------------------------------------------
//            C T O R  /  B I G   T H R E E
//---------------------------------------------------------------------

template <typename T>
BPlusTree<T>::BPlusTree(bool dups) :dups_ok(dups), data_count(0),
child_count(0), next(nullptr) {
    //left emtpy
}

//Copy CTOR
template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other) :
    data_count(0), child_count(0) {
    BPlusTree* temp = nullptr;
    copy_tree(other, temp);
}

template <typename T>
BPlusTree<T>::~BPlusTree() {
    const bool debug = false;
    clear_tree();
    if (debug) cout << "** destructor fired!" << endl;
}

template <typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS) {
    if (this == &RHS)
        return *this;
    clear_tree();
    BPlusTree* temp = nullptr;
    copy_tree(RHS, temp);
    const bool debug = false;
    if (debug) cout << "** assignment operator fired!" << endl;
    return *this;
}
//---------------------------------------------------------------------
//            B E G I N ( )   &   E N D ( )
//---------------------------------------------------------------------

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin() {
    if (!empty())
        return BPlusTree<T>::Iterator(get_smallest_node(), 0);
    //If its empty return empty iterator (almost forgot)
    return BPlusTree<T>::Iterator();
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end() {
    return Iterator(nullptr);
}
template <typename T>
T& BPlusTree<T>::get(const T& entry) {
    //If entry is not in the tree, add it to the tree
    //assert(contains(entry));

    const bool debug = false;
    if (!contains(entry))
        insert(entry);
    return get_existing(entry);
}

template <typename T>
T& BPlusTree<T>::get_existing(const T& entry) {
    /*
 * ---------------------------------------------------------------
 * This routing explains plainly how the BPlusTree is organized.
 * i = first_ge
 *       |      found         |    !found         |
 * ------|--------------------|-------------------|
 * leaf  |  you're done       | it's not there    |
 *       |                    |                   |
 * ------|--------------------|-------------------|
 * !leaf | subset[i+1]->get() |  subset[i]->get() |
 *       | (inner node)       |                   |
 * ------|--------------------|-------------------|
 *       |                    |                   |
 *
 * ---------------------------------------------------------------
 *
 */
 //assert that entry is not in the tree.
 //assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);
    if (is_leaf())
        if (found) {
            return data[i];
        }
        else {
            if (debug) cout << "get_existing was called with nonexistent entry" << endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i + 1]->get(entry);
    //or just return true?
    else //not found yet...
        return subset[i]->get(entry);


}
template <typename T>
bool BPlusTree<T>::is_valid() {

    //should check that every data[i] < data[i+1]
    if (is_leaf())
        return true;
    bool valid;
    if (!is_leaf()) {
        valid = subset[child_count - 1]->is_valid();
        if (valid == false) {
            return false;
        }
    }
    for (int i = 0; i < data_count - 1; i++) {
        if (data[i] < data[i + 1]) {
            valid = true;
        }
        else {
            valid = false;
        }
    }
    return valid;
}

//------------------------------------------------
//          I N S E R T
//------------------------------------------------
template <typename T>
void BPlusTree<T>::insert(const T& entry) {
    //in order for this class to be able to keep track of the number of the keys,
    //      this function (and the functions it calls ) must return a success code.
    //If we are to keep track of the number the keys (as opposed to key/values)
    //  then the success code must distinguish between inserting a new key, or
    //  adding a new key to the existing key. (for "dupes_ok")
    //
    //loose_insert this entry into this root.
    //loose_insert(entry) will insert entry into this tree. Once it returns,
    //  all the subtrees are valid
    //  btree subtrees EXCEPT this root may have one extra data item:
    //    in this case (we have excess in the root)
    //      create a new node, copy all the contents of this root into it,
    //      clear this root node,
    //      make the new node this root's only child (subset[0])
    //
    //Then, call fix_excess on this only subset (subset[0])
    loose_insert(entry);
    if (data_count > MAXIMUM) {
        BPlusTree<T>* growth_pointer = new BPlusTree<T>;
        copy_array(growth_pointer->data, data, growth_pointer->data_count, data_count);
        copy_array(growth_pointer->subset, subset, growth_pointer->child_count, child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = growth_pointer;
        fix_excess(0);
    }

}

template <typename T>
void BPlusTree<T>::loose_insert(const T& entry) {
    /*
       int i = first_ge(data, data_count, entry);
       bool found = (i<data_count && data[i] == entry);

       three cases:
         found
         a. found/leaf: deal with duplicates: call +
         b. found/no leaf: subset[i+1]->loose_insert(entry)
                           fix_excess(i+1) if there is a need

         ! found:
         c. !found / leaf : insert entry in data at position i
         c. !found / !leaf: subset[i]->loose_insert(entry)
                            fix_excess(i) if there is a need

            |   found          |   !found         |
      ------|------------------|------------------|-------
      leaf  |a. dups? +        | c: insert entry  |
            |                  |    at data[i]    |
      ------|------------------|------------------|-------
            | b.               | d.               |
            |subset[i+1]->     | subset[i]->      |
      !leaf | loose_insert(i+1)|  loose_insert(i) |
            |fix_excess(i+1)   | fix_excess(i)    |
            |                  |                  |
      ------|------------------|------------------|-------
    */
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);
    if (found) {
        if (is_leaf()) {
            //data[i] += entry;
            data[i] = data[i] + entry;
        }
        else {
            subset[i + 1]->loose_insert(entry);
            if (subset[i + 1]->data_count > MAXIMUM) {
                fix_excess(i + 1);
            }
        }
    }
    else {
        if (is_leaf()) {
            insert_item(data, i, data_count, entry);
        }
        else {
            subset[i]->loose_insert(entry);
            if (subset[i]->data_count > MAXIMUM) {
                fix_excess(i);
            }
        }
    }
}

template <typename T>
void BPlusTree<T>::fix_excess(int i) {
    //this node's child i has one too many items: 3 steps:
    //1. add a new subset at location i+1 of this node
    //2. split subset[i] (both the subset array and the data array) and move half into
    //      subset[i+1] (this is the subset we created in step 1.)
    //3. detach the last data item of subset[i] and bring it and insert
    //      it into this node's data[]
    //
    //Note that this last step may cause this node to have too many itesm.
    //  This is OK. This will be
    //  dealt with at the higher recursive level. (my parent will fix it!)
    //
    //NOTE: ODD/EVENNESS
    // when there is an excess, data_count will always be odd
    //  and child_count will always be even.
    //  so, splitting is always the same.

    //  000 B_PLUS_TREE
    //  if (subset[i]->is_leaf())
    //  transfer the middle entry to the right and...
    //  Deal with next pointers. just like linked list insert
    BPlusTree* temp = new BPlusTree();
    //plit the B+ tree
    split(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);
    split(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);

    //My mom said this was correct so I will be sad if it is not
    temp->next = subset[i]->next;
    subset[i]->next = temp;
    //Sets the next to the subet[i] next
    T tomove;
    detach_item(subset[i]->data, subset[i]->data_count, tomove);
    insert_item(subset, i + 1, child_count, temp);
    insert_item(data, i, data_count, tomove);

    if (temp->is_leaf()) {
        //If the newly inserted b+ tree is a leaf you insert the excess item
        insert_item(temp->data, 0, temp->data_count, tomove);
    }
}
//---------------------------------------------------------------
//      S I Z E  /  E M P T Y
//---------------------------------------------------------------
template <typename T>
int BPlusTree<T>::size() const {
    //No idea what this function means
    return data_count;
    //this function counts the number of     keys in the btree
}

template <typename T>
bool BPlusTree<T>::empty() const {
    return (data_count == 0);
}
//---------------------------------------------------------------
//      C L E A R   /  C O P Y
//---------------------------------------------------------------

template <typename T>
void BPlusTree<T>::clear_tree() {
    for (int i = 0; i < child_count; i++) {
        if (subset[i] != nullptr) {
            subset[i]->clear_tree();
            subset[i]->next = nullptr;
            delete subset[i];
            subset[i] = nullptr;
        }
    }
    child_count = 0;
    data_count = 0;
}
template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    BPlusTree* temp = nullptr;
    copy_tree(other, temp);
}
template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& temp_next) {
    
    //Copy subsets
    for (int i = other.child_count - 1; i >= 0; i--) {
        subset[i] = new BPlusTree();
        subset[i]->copy_tree(*other.subset[i], temp_next);
    }
    //If they are leaves then we have to fix the next pointers
    if (other.is_leaf()) {
        next = temp_next;
        temp_next = this;
    }
    //Copy the data count and child count 
    child_count = other.child_count;
    data_count = other.data_count;
    //Copy the data 
    for (int i = 0; i <= data_count; i++) {
        data[i] = other.data[i];
    }
}
//---------------------------------------------------------------
//      P R I N T  E T C.
//---------------------------------------------------------------
template <class T>
void BPlusTree<T>::print_tree(int level, std::ostream& outs) const {
    //1. print the last child (if any)
    //2. print all the rest of the data and children
    if (!is_leaf()) {
        subset[child_count - 1]->print_tree(level + 1, outs);
    }
    for (int i = data_count - 1; i >= 0; i--) {
        outs << std::setw(4 * level) << "" << "[" << data[i] << "]" << std::endl;
        if (!is_leaf()) {
            subset[i]->print_tree(level + 1, outs);
        }
    }
}
//------------------------------------------------
//          R E M O V E
//------------------------------------------------
template <typename T>
void BPlusTree<T>::remove(const T& entry) {
    /*
     * ---------------------------------------------------------------------------------
     * Same as BTree:
     * Loose_remove the entry from this tree.
     * Shrink if you have to
     * ---------------------------------------------------------------------------------
     * once you return from loose_remove, the root (this object) may have no data and
     * only a single subset:
     * now, the tree must shrink:
     *
     * point a temporary pointer (shrink_ptr) and point it to this root's only subset
     * copy all the data and subsets of this subset into the root (through shrink_ptr)
     * now, the root contains all the data and poiners of it's old child.
     * now, simply delete shrink_ptr, and the tree has shrunk by one level.
     * Note, the root node of the tree will always be the same, it's the
     * child node we delete
     *
     *
     */
    loose_remove(entry);
    if (data_count == 0) {
        //Shrink the tree
        BPlusTree<T>* shrink_ptr = subset[0];
        copy_array(data, shrink_ptr->data, data_count, shrink_ptr->data_count);
        copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);
        shrink_ptr->data_count = 0;
        shrink_ptr->child_count = 0;
        //delete shrink_ptr;
    }
}
template <typename T>
void BPlusTree<T>::loose_remove(const T& entry) {
    /* four cases:
          leaves:
               a. not found: there is nothing to do
               b. found    : just remove the target
          non leaf:
               c. not found: subset[i]->loose_remove, fix_shortage(i)
               d. found    : subset[i+1]->loose_remove, fix_shortage(i+1) [...]
                   (No More remove_biggest)

            |   !found               |   found                 |
      ------|------------------------|-------------------------|-------
      leaf  |  a: nothing            | b: delete               |
            |     to do              |    target               |
      ------|------------------------|-------------------------|-------
      !leaf | c:                     | d: B_PLUS_TREE          |
            |  [i]->  loose_remove   |   [i+1]-> loose_remove  |
            |  fix_shortage(i)       | fix_shortage(i+1) [...] |
      ------|------------------------|-------------------------|-------


    */
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);
    const bool debug = false;
    T found_entry;
    if (is_leaf()) {
        if (!found) {
            //[a.] nothing to do
            //entry not in this tree
        }
        else {
            T trash;
            delete_item(data, i, data_count, trash);
            //[b.] just delete the item
            //   my parent will take care of my shortage
        }

    }
    else {
        //not leaf:
        // ---- 000 B_PLUS_TREE: no more remove_biggest
        if (!found) {
            //[c.] Not here: subset[i]->loose_remove
            //not found yet. search in the next level:
            subset[i]->loose_remove(entry);
            if (subset[i]->data_count < MINIMUM) {
                fix_shortage(i);
                //cout << "Fix shortage 1";
            }
        }
        else {
            //[d.] found key in an inner node:subset[i+1]->loose_remove
            assert(i < child_count - 1);
            /*
             * Here's The Story:
             * data[i] is the same as the item that we have deleted.
             * so, now, it needs to be replaced by the current smallest key
             *      in subset[i+1]
             * Problem: After fix_shortage, data[i] could have moved to a different index(?)
             *      or it could have sunk down to a lower level as a result of merge
             *      we need to find this item and replace it.
             *
             *      Before fix_shortage: we cannot replace data[i] with subset[i+1]->smallest
             *      before fix_excess because this smallest key could be the very entry
             *      we are removing. So, we'd be replacing data[i] with entry. and this will
             *      leave the deleted key in the inner nodes.
             *
             *      After fix_shortage: We have no way of knowing where data[i] key (which is
             *      same as entry) will end up. It could move down one level by the time
             *      fix_shortage returns.
             *
             *      Therefore it seems like we have no choice but to search for it in
             *      data[ ] AND subset[i]->data[ ]
             * Current Solution: Kind of messy:
             *      After fix_shortage(i+1):
             *      Search for entry in data[ ] and if found, replace it with smallest.
             *      otherwise, search for it in subset[i]->data[ ]
             *          and replace it. that's where the key (entry) will end up after
             *          fix order returns (credit: Jiaruy Li)
             *
             */
            subset[i + 1]->loose_remove(entry);
            if (subset[i + 1]->data_count < MINIMUM) {
                fix_shortage(i + 1);
            }
            int next_index = first_ge(data, data_count, entry);
            if (next_index < data_count && data[next_index] == entry) {
                subset[i + 1]->get_smallest(data[next_index]);
            }
            else {
                //otherwise, search for it in subset[i]->data[]
                next_index = first_ge(subset[i]->data, subset[i]->data_count, entry);
                //Check the next index subset[i] for the entry 
                if (next_index < subset[i]->data_count && subset[i]->data[next_index] == entry) {
                    subset[i]->subset[next_index + 1]->get_smallest(subset[i]->data[next_index]);
                }
            }
            //remember. it's possible that data[i] will be gone by the time
            //      fix_shortage returns.
            //key was removed from subset[i+1]:
            //  1. shortage: find entry in data or subset[i+1]->data 
            //              and replace it with subset[i+1]->smallest
            //  2. no shortage: replace data[i] with subset[i+1]->smallest
        }
        // --------------------------------------------------------
    }
}

template <typename T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i) {
    /*
     * fix shortage in subtree i:
     * if child i+1 has more than MINIMUM,
     *          (borrow from right) transfer / rotate left(i+1)
     * elif child i-1 has more than MINIMUM,
     *          (borrow from left) transfer /rotate right(i-1)
     * elif there is a left sibling,
     *          merge with prev child: merge(i-1)
     * else
     *          merge with next (right) child: merge(i)
     *
     *
     * returns a pointer to the fixed_subset
     */
    const bool debug = false;
    if ((i < child_count - 1) && (subset[i + 1]->data_count > MINIMUM)) {
        //borrow from right subtree if possible
        transfer_left(i + 1);
        return subset[i];
    }
    else if ((i > 0) && (subset[i - 1]->data_count > MINIMUM)) {
        transfer_right(i - 1);
        return subset[i];
    }
    else if (i > 0) {
        merge_with_next_subset(i - 1);
        return subset[i];
    }
    else {
        merge_with_next_subset(i);
        return subset[i];
    }
}

template <typename T>
void BPlusTree<T>::get_smallest(T& entry) {
    //replace entry with the left_most leaf of this tree
    // Keep looking in the first subtree (recursive)
    //  until you get to a leaf.
    // Then, replace entry with data[0] of the leaf node
    //This is handeled by the get_smallest_node recursively 
    entry = get_smallest_node()->data[0];
}
template<class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    if (!is_leaf())
        return subset[0]->get_smallest_node();
    return this;
}
template<class T>
void BPlusTree<T>::get_biggest(T& entry){
    if (!is_leaf())
        data = subset[child_count - 1]->get_biggest()->data[data_count-1];
}

template <typename T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i) {
    /*
     * ----------------------------------------------------------------------
     *  Merge subset[i] with subset [i+1] REMOVE data[i];
     *  non leaf: same as BTree
     *  leaves  : delete but do not bring down data[i]
     * ----------------------------------------------------------------------
     *
     *   1. remove data[i] from this object
     *   2. if not a leaf, append it to child[i]->data:
     *   3. Move all data items from subset[i+1]->data to right of subset[i]->data
     *   4. Move all subset pointers from subset[i+1]->subset to
     *          right of subset[i]->subset
     *   5. delete subset[i+1] (store in a temp ptr)
     *   6. if a leaf, point subset[i]->next to temp_ptr->next
     *   6. delete temp ptr
     *
     *
     * non-leaf nodes: (same as BTree)
     * ------------------
     *  i = 0:
     *             [50  100]
     *          /      |     \
     *  [  ]         [75]       ....
     *    |         /    \
     *   [a]      [b]    [c]
     *
     *  bring down data[i], merge it with subset[i] and subset[i+1]:
     *      then, get rid of subset[i+1]
     *             [100]
     *               |
     *            [50|75]       ....
     *            /  |  \
     *         [a]  [b]  [c]
     *
     *
     *
     * leaf node:
     * ----------------
     * Exactly the same, but do not attach the deleted data[i] to subset[i]->data[ ]
     *
     *  i = 0 : merge 5 and [()]
     *        [7 | 10]
     *      /    |     \
     *  [5]->   [()]->  [10]
     *
     *  Delete data[i] (7), merge subset[i] and subset[i+1]
     *      WITHOUT bringing down data[i]
     *
     *        [10]
     *      /      \
     *  [5]->      [10]
     *
     *
     * i = 1 merge 7 and [()]
     *        [7 | 10]
     *      /    |     \
     *  [5]->   [7]->  [()]
     *
     *  Delete data[i] (10), merge subset[i] and subset[i+1]
     *      WITHOUT bringing down data[i]
     *
     *        [7]
     *      /     \
     *  [5]->      [7]
     *
     *
     *
     *
     */
    T deleted;
    BPlusTree* temp_tree;
    delete_item(data, i, data_count, deleted);
    if (!subset[i]->is_leaf()) {
        attach_item(subset[i]->data, subset[i]->data_count, deleted);
    }
    //The same the subset i with subset i + 1
    merge(subset[i]->data, subset[i]->data_count,subset[i+1]->data, subset[i+1]->data_count);
    merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
    subset[i+1]->data_count = 0;
    subset[i+1]->child_count = 0;
    delete_item(subset, i + 1, child_count, temp_tree);
    //Fix the next pointers 
    if (subset[i]->is_leaf()) {
        subset[i]->next = temp_tree->next;
    }
    delete temp_tree;
    return subset[i];

}
template <typename T>
void BPlusTree<T>::transfer_left(int i) {
    /*
     * --------------------------------------------------------------
     * transfer_left: from subset[i] to subset[i-1]
     *      non-leaf: same as BTree
     *      leaves  : rotate and leave and update data[i-1] with subset[i]->data[0]
     *                  leftmost key after you borrowed goes to replace data[i-1]
     * --------------------------------------------------------------
     *
     * non-leaf keys: BTree's rotate_left
     * ---------------
     *
     * (0 < i < child_count) and (subset[i]->data_count > MINIMUM)
     * subset[i-1] has only MINIMUM - 1 entries.
     *
     * item transfers from child[i] to child [i-1]
     *
     * FIRST item of subset[i]->data moves up to data to replace data[i-1],
     * data[i-1] moves down to the RIGHT of subset[i-1]->data
     *
     *  i = 1:
     *              [50  100]
     *  [  ]         [65 75]       ....
     *   [a]      [b]  [c]  [d]
     *
     *  65 move up to replace 50 (data[i])
     *  65's child (its child 0) moves over to be the future child of 50
     *  50 moves down to the right of subset[i]->data
     *
     *               [65 100]
     *   [50]         [ 75 ]       ....
     * [a]  [b]      [c]  [d]
     *
     * ****This does not belong here:
     * last item of subset[i-1]->data moves up to data to replace data[i],
     * data[i] moves down to the RIGHT of subset[i]->data
     *
     * leaf keys:
     * -------------
     *  fix_shortage(0) calls trnasfer_left(1) so, i = 1
     *          [7 | 10]
     *        /    |     \
     * [( )]<=[(7) | 8]  [10]
     *
     * 1. transfer subset[i(1)]->data[0] to end of subset[i-1]
     *        [7 | 10]
     *      /    |     \
     *   [7]    [8]   [10]
     *
     * 2. update parent of the transfered subset: data[i-1 (0)] = subset[i(1)]->data[0]
     *
     *        [(8) | 10]
     *      /      |     \
     *   [7]     [(8)]   [10]
     *
     *
     *
     */
    if (!subset[i]->is_leaf()) {
        //If subset[i] is a leaf 
        //Transfer from subet[i] to child[i-1]
        attach_item(subset[i-1]->data, subset[i - 1]->data_count, data[i-1]);
        delete_item(subset[i]->data, 0, subset[i]->data_count, data[i-1]);
        if (!subset[i]->is_leaf()) {
            BPlusTree* temp_tree;
            delete_item(subset[i]->subset, 0, subset[i]->child_count, temp_tree);
            attach_item(subset[i - 1]->subset, subset[i-1]->child_count, temp_tree);
        }
    }
    else {
        //Not a leaf is same as B Tree 
        T trash;
        attach_item(subset[i-1]->data, subset[i-1]->data_count, subset[i]->data[0]);
        delete_item(subset[i]->data, 0, subset[i]->data_count, trash);
        data[i-1] = subset[i]->data[0];
    }
}

template <typename T>
void BPlusTree<T>::transfer_right(int i) {
    /*
     * --------------------------------------------------------------
     * transfer right from subset[i] to subset[i+1]
     *      non-leaf: same as BTree
     *      leaves  : rotate and leave a 'trace':
     *              data[i] is replaced with subset[i+1]->data[0]
     *              after you borrowed the key,
     * --------------------------------------------------------------
     *
     * non-leaf keys: BTree's rotate_right
     * ---------------
     * (i < child_count - 1) and (subset[i-1]->data_count > MINIMUM)
     * subset[i+ 1] has only MINIMUM - 1 entries.
     *
     * item transfers from child[i] to child [i+1]
     *
     * LAST item of subset[i]->data moves up to data to replace data[i],
     * data[i] moves down to the LEFT of subset[i+1]->data
     *
     * i = 1
     *                     [50 100]
     *      [20 30]        [65 75]          [ ]
     *  [..] [..] [..]   [a] [b] [c]        [..]
     *
     *  75 moves up to replace 100 (data[i])
     *  75's child (its last child) moves over to be the (child 0) child of 100
     *  100 moves down to subset[i]->data
     *
     *                     [50 75]
     *      [20 30]          [65]          [100]
     *  [..] [..] [..]     [a] [b]        [c] [..]
     *
     * last item of subset[i-1]->data moves up to data,
     * data[i] moves down to the RIGHT of subset[i]->data
     *
     * leaf keys:
     * -------------
     *  fix_shortage(2) calls trnasfer_right(1) so, i = 1 subset[i] is ([7|8])
     *  subset[i+1] is the one being fixed.
     *        [7 | 10]
     *      /    |     \
     * [5|6]->[7 | (8)]=>[()]
     *
     * 1. transfer subset[i(1)]->data[last item] to left of subset[i+1]->data
     *        [7 | (10)]
     *      /    |     \
     *   [5|6]->[7]-> [8]
     *
     * 2. update parent of the transfered subset: data[i (1)] = subset[i+1(2)]->data[0]
     *
     *        [7 | 8]
     *      /    |    \
     *   [5|6]->[7]-> [8]
     *
     *
     */
    if (subset[i]->is_leaf()) {
        //IF it is a leaf then detatch the subset i data and insert the data[i] to
        detach_item(subset[i]->data, subset[i]->data_count, data[i]);
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);
    }
    else if (!subset[i]->is_leaf()) {
        //If it is a leaf insert to subset i + 1 data 
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);
        detach_item(subset[i]->data, subset[i]->data_count, data[i]);
        //Check if the new subset is a leaf 
        if (!subset[i]->is_leaf()) {
            BPlusTree* old_right;
            detach_item(subset[i]->subset, subset[i]->child_count, old_right);
            insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, old_right);
        }
    }
}
template <typename T>
bool BPlusTree<T>::contains(const T& entry) {
    return find_ptr(entry) != nullptr;
}
template <typename T>
const T& BPlusTree<T>::get(const T& entry)const {
    return get(entry);
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry) {
    int i = first_ge(data, data_count, entry);
    bool found = i < data_count&& data[i] == entry;
    //If found check if it is a leaf 
    if (found) {
        //If leaf we return an iterator to it 
        if (is_leaf()) return BPlusTree<T>::Iterator(this, i);
        //otherwise we search more 
        else return subset[i + 1]->find(entry);
    }
    else if (is_leaf()) {
        //If leaf and not found we failed so we return nullptr
        return BPlusTree<T>::Iterator(nullptr);
    }
    else {
        return subset[i]->find(entry);
    }
}
template <typename T>
T* BPlusTree<T>::find_ptr(const T& entry) {
    int i = first_ge(data, data_count, entry);
    bool found = i < data_count&& data[i] == entry;
    if (found) {
        if (is_leaf())
            return data + i;
        else return subset[i + 1]->find_ptr(entry);
    }

    else if (is_leaf())
        return nullptr;
    else return subset[i]->find_ptr(entry);
}
//Upper and lower bound?
//return first that goes NOT BEFORE
template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
    BPlusTree<T>::Iterator it = begin();
    while (it != end() && *it < key) {
        it++;
    }
    return it;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
    BPlusTree<T>::Iterator it = begin();
    while (it != end() && *it <= key) {
        it++;
    }
    return it;
}