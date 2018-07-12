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
LRUCache::refer(const int& key) {
    
}

UserProfile     
LRUCache::get(const int& key) {
    ZMAP::iterator it  = this->_index.find(key);
    if (it != this->_index.end()) {
        return this->_list.;
    } else {
//        return NULL;
    }
 }
    
 
 void      
 LRUCache::add(const int& key, const UserProfile& data) {
     
 }