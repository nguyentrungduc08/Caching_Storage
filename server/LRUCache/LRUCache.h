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

#include "../UserStorage.h"

using namespace ::Task1;

#define ZMAP    std::unordered_map<int, std::list<UserProfile>::iterator >
#define ZLIST   std::list<UserProfile>


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
};

#endif	/* LRUCACHE_H */

