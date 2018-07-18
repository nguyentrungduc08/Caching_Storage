/* 
 * File:   RLUCache.h
 * Author: ducnt
 *
 * Created on July 10, 2018, 5:59 PM
 */

#ifndef RLUCACHE_H
#define	RLUCACHE_H

#include <iostream>

#include "DoublyLinkedList.h"
#include "HashTable.h"
#include "ArrayList.h"


template<class Tkey, class Tvalue>
class LRUCache {
public:
    LRUCache() {
        this->_cacheSize = HashTableSize;
    }
    
    virtual ~LRUCache(){
        
    }
    
    void setCacheSize(const int &Zsize);
    void add(const Tkey&, Tvalue);
    void get(const Tkey&, Tvalue&);
    void refactoring(const Tkey&);
    bool find(const Tkey &key);

    void display();
    
private:
    LinkedList<Tkey, Tvalue>                _list;
    HashTable<Tkey, Node<Tkey,Tvalue>*>     _hashTable;
    unsigned int                            _cacheSize;
};

#endif	/* RLUCACHE_H */

