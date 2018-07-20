/* 
 * File:   UserStorageHandler.h
 * Author: Ducnt
 *
 * Created on July 6, 2018, 4:05 PM
 */

#ifndef USERSTORAGEHANDLER_H
#define	USERSTORAGEHANDLER_H

#include <bits/stdc++.h>

#include "UserStorage.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>

#include <thrift/transport/TSocket.h>  
#include <thrift/transport/TServerSocket.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TTransportUtils.h>

#include <boost/make_shared.hpp>

#include "KC_GenID/WZ_GenIdService.h"
#include "KC_Storage/WZ_StorageService.h"
#include "KC_Storage/KC_Storage.h"
#include "LRUCache/LRUCache.h"
#include "LRUCache/LRUCache.cpp"

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using Poco::AutoPtr;
using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Runnable;

using boost::shared_ptr;

using namespace ::Task1;

class Zcache {
private:
    LRUCache<int, UserProfile> _cache;

private:

    Zcache() {
        std::cout << "construct create Cache" << std::endl;
    }
    
    Zcache(const Zcache& );
    void operator=(const Zcache&);

public:

    ~Zcache() {
        std::cout << "destructor release Cache" << std::endl;
    }

    static Zcache& getInstance() {
        static Zcache instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void setSize(const int &Zsize) {
        this->_cache.setCacheSize(Zsize);
    }

    void add(const int &key, UserProfile data) {
        this->_cache.add(key, data);
    }
    

    void get(const int &key, UserProfile &data) {
        this->_cache.get(key, data);
    }
};


class NotificationStoreProfile : public Poco::Notification {
public:

    NotificationStoreProfile(std::string key, std::string data, putOption::type opt) : _key(key), _data(data), _putType(opt) {

    }

    std::string getKey() const {
        return this->_key;
    }

    std::string getData() const {
        return this->_data;
    }

    putOption::type getPutOption() const {
        return this->_putType;
    }

private:
    std::string _key;
    std::string _data;
    putOption::type _putType;
};


/*
 class wrapper using to write asynchronous to database.
 */
class Z_Worker : public Poco::Runnable {
public:
    Z_Worker(const std::string & key, const std::string data, const putOption::type opt) : _key(key), _data(data) , _putType(opt) {   
    } 
    
    Z_Worker(const Z_Worker& other) : _key(other._key), _data(other._data), _putType(other._putType)
    {
    }
    
    virtual ~Z_Worker(){
        std::cout << "remove worker" << std::endl;
    } 
    
    void run() {
        WZ_StorageService wzStorage;
        bool ok = wzStorage.W_put(this->_key, this->_data, this->_putType);
    }
    
private:
    std::string _key;
    std::string _data;
    putOption::type _putType;
};


class UserStorageHandler : virtual public UserStorageIf, Poco::Runnable {
public:
    UserStorageHandler();
    UserStorageHandler(const UserStorageHandler& orig);
    virtual ~UserStorageHandler();

    int32_t createUser(const UserProfile& user);
    void getUser(UserProfile& _return, const int32_t uid);
    int32_t editUser(const int32_t uid, const UserProfile& user);
    std::string serialize(UserProfile& obj);
    std::string serialize(idcounter uid);
    idcounter deserializeID(std::string binaryString);
    UserProfile deserialize(std::string serializeString);

    void run();

private:
    void showProfile(const UserProfile& profile);

    NotificationQueue _queue;
    Poco::Thread _thread;
};



#endif	/* USERSTORAGEHANDLER_H */

