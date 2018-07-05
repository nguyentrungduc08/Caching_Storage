/* 
 * File:   WZ_StorageService.h
 * Author: cpu10664-local
 *
 * Created on July 4, 2018, 11:18 AM
 */

#ifndef WZ_STORAGESERVICE_H
#define	WZ_STORAGESERVICE_H
#include <bits/stdc++.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "KC_Storage.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace KC_Storage;
using boost::make_shared;

class WZ_StorageService {
public:
    WZ_StorageService();
    WZ_StorageService(const WZ_StorageService& orig);
    virtual ~WZ_StorageService();

    int64_t W_getTotalRecord();
    std::string W_get(const std::string& key);
    bool W_put(const std::string& key, const std::string& value, const putOption::type& opt);
    bool W_remove(const std::string& key);
    
private:
    
};

#endif	/* WZ_STORAGESERVICE_H */

