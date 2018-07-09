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

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
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

class NotificationStoreProfile : public Poco::Notification {
public :
    NotificationStoreProfile(std::string key, std::string data, putOption::type opt) : _key(key), _data(data), _putType(opt) {
        
    }

    std::string getKey() const {
        return this->_key;
    }
    
    std::string getData() const{
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

class Worker : public Poco::Runnable { 
public :
    Worker(NotificationQueue & queue, std::string workerName) : _queue(queue), _name(workerName) {
        std::cout << "construct Worker " << std::endl;
    }

    void run() {
        AutoPtr<Notification> pNf(_queue.waitDequeueNotification()); //
        while (pNf) {
            NotificationStoreProfile* pWorkNf = dynamic_cast<NotificationStoreProfile*>(pNf.get());
            if (pWorkNf) {
                WZ_StorageService wzStorage;
                bool ok = wzStorage.W_put(pWorkNf->getKey(), pWorkNf->getData(), pWorkNf->getPutOption());
            } 
            pNf = _queue.waitDequeueNotification();
        }
    }
private:
    NotificationQueue& _queue;
    std::string _name;
};

class UserStorageHandler : virtual public UserStorageIf {
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
    
private:
    void showProfile(const UserProfile& profile);
    
    NotificationQueue _queue;
    shared_ptr<Worker> _worker1;
    shared_ptr<Worker> _worker2;
    shared_ptr<Worker> _worker3;
};



#endif	/* USERSTORAGEHANDLER_H */

