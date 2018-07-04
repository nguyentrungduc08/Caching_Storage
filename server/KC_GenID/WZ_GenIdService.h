/* 
 * File:   WZ_GenIdService.h
 * Author: cpu10664-local
 *
 * Created on July 4, 2018, 11:12 AM
 */

#ifndef WZ_GENIDSERVICE_H
#define	WZ_GENIDSERVICE_H

#include <bits/stdc++.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "KC_GenID.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace KC_GenID;
using boost::make_shared;


class WZ_GenIdService {
public:
    WZ_GenIdService();
    WZ_GenIdService(const WZ_GenIdService& orig);
    virtual ~WZ_GenIdService();
    
    int64_t W_genID(const std::string &keyType);
    int64_t W_getRangeId(const std::string &keyType, const int64_t &range);
    int64_t W_getIdValue(const std::string &keyType);
private:
    
};

#endif	/* WZ_GENIDSERVICE_H */

