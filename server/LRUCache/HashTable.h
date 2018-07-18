/* 
 * File:   HashTable.h
 * Author: ducnt
 *
 * Created on July 13, 2018, 10:51 AM
 */

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#include "DoublyLinkedList.h"
#include "ArrayList.h"


#define HashTableSize 1000000

template<class Tkey, class Tvalue>
class HashNode {
public:
    HashNode(const Tkey &key, const Tvalue &value) : _key(key), _value(value), _next(NULL) {
        
    }
    
    /*
     * get key of bucket
     * @return key value
     */
    Tkey 
    getKey() {
        return this->_key;
    }
    
    /*
     * get value of bucket
     * @return value of bucket
     */
    Tvalue 
    getValue() {
        return this->_value;
    }
    
    void 
    setValue(Tvalue value) {
        this->_value = value;
    }
    
    HashNode* 
    getNext() {
        return this->_next;
    }
    
    void
    setNext(HashNode *next) {
        this->_next = next;
    }
    
private:
    Tkey _key;
    Tvalue _value;  
    HashNode<Tkey, Tvalue> *_next;
};

/*
 hash function 
 @return key 
 */
template <class Tkey>
struct KeyHash {
    unsigned int operator() (const Tkey& key) const {
//        return reinterpret_cast<int> (key) % HashTableSize;
        return (key) % HashTableSize;
    }
};

template <class Tkey, class Tvalue, class HF = KeyHash<Tkey> >
class HashTable {
private:
    HashNode<Tkey, Tvalue>  **_hashTable;
    HF                      _hashFunction;
    unsigned int            _size;

public:
    /*
     construct zero initialized hash table of size
     */
    HashTable() {
        this->_hashTable = new HashNode<Tkey, Tvalue> *[HashTableSize]();
        for(int i = 0; i < HashTableSize; ++i){
            this->_hashTable[i] = NULL;
        }
        this->_size = 0;
    }
    
    /*
     release hashtable
     */
    ~HashTable() {
        for(int i = 0; i < HashTableSize; ++i) {
            HashNode<Tkey, Tvalue> *bucket = this->_hashTable[i];
            while (bucket != NULL){
                HashNode<Tkey, Tvalue> *node = bucket;
                bucket = bucket->getNext();
                delete node;
            }
            this->_hashTable[i] = NULL;
        }
        delete [] this->_hashTable;
        this->_size = 0;
    }
    
    void 
    put(const Tkey &key, Tvalue value) {
        int hashValue = this->_hashFunction(key);
        std::cout << "put log hashfunction: " << key << " - " << hashValue << std::endl;
        HashNode<Tkey, Tvalue> *prevBucket = NULL;
        HashNode<Tkey, Tvalue> *bucket = this->_hashTable[hashValue];
        
        while (bucket != NULL && bucket->getKey() != key ){
            prevBucket = bucket;
            bucket = bucket->getNext();
        } 
        
        if (bucket == NULL) {
            bucket = new HashNode<Tkey, Tvalue>(key, value);
            if (prevBucket == NULL) {
                this->_hashTable[hashValue] = bucket;
            } else {
                prevBucket->setNext(bucket);
            }
            ++this->_size; 
        } else { // overide hash value
            bucket->setValue(value);
        }
    }
    
    void 
    remove(const Tkey &key) {
        int hashValue = this->_hashFunction(key);
        std::cout << "remove log hashfunction: " << key << " - " << hashValue << std::endl;
        HashNode<Tkey, Tvalue> *prevBucket = NULL;
        HashNode<Tkey, Tvalue> *bucket = this->_hashTable[hashValue];
        
        while (bucket != NULL && bucket->getKey() != key) {
            prevBucket = bucket;
            bucket = bucket->getNext();
        }
        
        if (bucket == NULL) {
            // key no exist
            std::cout << "key not exist" << std::endl;
            return; 
        } else {
            if (prevBucket == NULL){
                this->_hashTable[hashValue] = bucket->getNext();
            } else {
                prevBucket->setNext(bucket->getNext()); 
            }
            delete bucket;
            --this->_size;
        } 
        return;
    }

    /*
     * get value (address value of key in linked list)
     * @para: - key : key value to be searched for.
     * @para: - value: refer parameter to store result value
     * @return true if key value is found and value return in refer value parameter. false if not found.   
     */
    bool 
    get(const Tkey &key, Tvalue &value) {
        int hashValue = this->_hashFunction(key);
        HashNode<Tkey, Tvalue> *bucket = this->_hashTable[hashValue];   
        
        while (bucket != NULL) {
            if (bucket->getKey() == key) {
                value = bucket->getValue();
                return true;
            }
            bucket = bucket->getNext();
        }
        return false;
    }

    /*
     @return size of hash table 
     */
    unsigned int size(){
        return this->_size;
    }
    
    /*
     * @para: key - key value to be searched for.
     * @return true if key value is fonud. false if key is not found. 
     */
    bool
    find(const Tkey& key) {
        int hashValue = this->_hashFunction(key);
        HashNode<Tkey, Tvalue> *bucket = this->_hashTable[hashValue];
        std::cout << "find log hashfunction: " << key << " - " << hashValue << std::endl;
        while (bucket != NULL) {
            if (bucket->getKey() == key){
                return true;
            }
            bucket = bucket->getNext();
        }
        return false;
    }
     
};

#endif	/* HASHTABLE_H */

