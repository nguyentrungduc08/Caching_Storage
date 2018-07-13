/* 
 * File:   LRUCache.cpp
 * Author: cpu10664-local
 * 
 * Created on July 12, 2018, 11:38 AM
 */

#include "LRUCache.h"

LRUCache::LRUCache(): _capacity(12345) {

}

LRUCache::LRUCache(const LRUCache& orig) {
}

LRUCache::~LRUCache() {
}

void            
LRUCache::refer(const int& key, const UserProfile& data) {
    ZMAP::iterator it  = this->_index.find(key);
    if (it == this->_index.end()) { // cache not have key.
        if (this->_list.size() == this->_capacity) { // if cache full
            this->_list.pop_back();
            this->_index.erase(key);
        }
    } else { // if user existed in cache
        this->_list.erase(it->second);
    }
        
    this->_list.push_front(data);
    this->_index[key] = this->_list.begin(); 
}

void            
LRUCache::refer(const int& key) {
    ZMAP::iterator it  = this->_index.find(key);
    UserProfile tmp;
    if (it == this->_index.end()) { // cache not have key.
        if (this->_list.size() == this->_capacity) { // if cache full
            this->_list.pop_back();
            this->_index.erase(key);
        }
    } else { // if user existed in cache
        this->_list.erase(it->second);
    }
        
//    this->_list.push_front(data);
    this->_index[key] = this->_list.begin(); 
}



UserProfile     
LRUCache::get(const int& key) {
    ZMAP::iterator it  = this->_index.find(key);
    if (it != this->_index.end()) {
//        return this->_list.;
    } else {
//        return NULL;
    }
 }
    
 
 void      
 LRUCache::add(const int& key, const UserProfile& data) {
     
 }