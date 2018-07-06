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

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace ::Task1;

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
};

#endif	/* USERSTORAGEHANDLER_H */

