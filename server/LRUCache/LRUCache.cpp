/* 
 * File:   RLUCache.cpp
 * Author: ducnt
 * 
 * Created on July 10, 2018, 5:59 PM
 */

#include "LRUCache.h"

/*
 * set size of cache.
 */
template<class Tkey, class Tvalue>
void 
LRUCache<Tkey, Tvalue>::setCacheSize(const int &Zsize){
    this->_cacheSize = Zsize;
}

/*
 * them mot phan tu vao cache.
 */
template<class Tkey, class Tvalue>
void 
LRUCache<Tkey, Tvalue>::add(const Tkey& key, Tvalue value) {
    if (!this->_hashTable.find(key)){ // neu key khong ton tai trong cache
        std::cout << "cache miss" << std::endl;
        if (this->_list.size() == this->_cacheSize ) {// cache full
            std::cout << "cache full" << std::endl;
            Node<Tkey, Tvalue>* last = this->_list.getBack();
            this->_hashTable.remove(last->_key);
            this->_list.popBack();
        }    
    } else { // neu key da ton tai trong cache
        std::cout << "cache hit" << std::endl;
        Node<Tkey, Tvalue>* ptrNode;
        this->_hashTable.get(key, ptrNode);
        this->_hashTable.remove(ptrNode->_key);
        this->_list.removeNode(ptrNode);
    }

    this->_list.pushFront(key, value);
    this->_hashTable.put(key,this->_list.getFront());
}

/*
 * kiem tra phan tu da ton tai trong cache.
 */
template <class Tkey, class Tvalue> 
bool 
LRUCache<Tkey, Tvalue>::find(const Tkey& key) {
    if (this->_hashTable.find(key) ) {
        return true;
    } else {
        return false;
    }
}

/*
 * lay gia tri cua mot phan tu trong cach tuong ung voi gia tri key.
 */
template<class Tkey, class Tvalue>
void 
LRUCache<Tkey, Tvalue>::get(const Tkey& key, Tvalue &value) {
    Node<Tkey, Tvalue>* addressData = NULL;
    if (this->find(key)){
        this->_hashTable.get(key, addressData);
        if (addressData != NULL){
            value = addressData->_value;
            this->refactoring(key);
        }
    } else {
        return;
    }
}

/*
 * hien thi tat ca cac phan tu nam trong cache
 */
template<class Tkey, class Tvalue>
void 
LRUCache<Tkey, Tvalue>::display() {
    this->_list.displayList();
}

template<class Tkey, class Tvalue>
void 
LRUCache<Tkey, Tvalue>::refactoring(const Tkey& key) {
    Node<Tkey, Tvalue>* ptrNode;
    Tvalue value;
    this->_hashTable.get(key, ptrNode);
    this->_hashTable.remove(ptrNode->_key);
    value = ptrNode->_value;
    this->_list.removeNode(ptrNode);

    this->_list.pushFront(key, value);
    this->_hashTable.put(key,this->_list.getFront());
}