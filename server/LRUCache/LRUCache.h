/* 
 * File:   LRUCache.h
 * Author: ducnt
 *
 * Created on July 12, 2018, 11:38 AM
 */

#ifndef LRUCACHE_H
#define	LRUCACHE_H

#include <iostream>
#include <map>
#include <list>
#include <unordered_map>

#include <Poco/LRUCache.h>

#include "../UserStorage.h"

using namespace ::Task1;

#define ZMAP    std::unordered_map<int, std::list<UserProfile>::iterator >
#define ZLIST   std::list<UserProfile>

template<class Tkey, class Tvalue>
class Node {
public :
    Tkey    _key;
    Tvalue  _value;
    Node    *_prev;
    Node    *_next;
    Node(Tkey k, Tvalue v): _key(k), _value(v), _prev(NULL), _next(NULL) {}
};  

template<class Tkey, class Tvalue>
class LinkedList {
private: 
    Node<Tkey, Tvalue> *_front;
    Node<Tkey, Tvalue> *_rear;
    
    bool isEmpty() {
        return this->_rear == NULL;  
    }
    
public:
    LinkedList() : _front(NULL), _rear(NULL) {};
    
    void        
    addFront(Tkey key, Tvalue value ){
        Node * node = new Node(key, value);
    }
    void        addEear(Node );
    void        getNode(Node*);
    void        removeNode(Node*);
    
};


class LRUCache {
public:
    LRUCache();
    LRUCache(const LRUCache& orig);
    virtual ~LRUCache();
    
    UserProfile     get(const int& key);
    void            add(const int& key, const UserProfile& data);
    
private:
    int     _capacity;
    ZLIST   _list;
    ZMAP    _index;
    Poco::LRUCache<int, UserProfile>  _lruCache;
    
    void            refer(const int& key);
    void            refer(const int& key, const UserProfile& data);
};

#endif	/* LRUCACHE_H */

