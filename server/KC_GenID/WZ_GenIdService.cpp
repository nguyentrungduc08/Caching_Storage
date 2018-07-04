/* 
 * File:   WZ_GenIdService.cpp
 * Author: cpu10664-local
 * 
 * Created on July 4, 2018, 11:12 AM
 */

#include "WZ_GenIdService.h"

WZ_GenIdService::WZ_GenIdService() {
    
}

WZ_GenIdService::WZ_GenIdService(const WZ_GenIdService& orig) {
}

WZ_GenIdService::~WZ_GenIdService() {
}

int64_t 
WZ_GenIdService::W_genID(const std::string &keyType) {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost",6789));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_GenID::KC_GenIDClient client(protocol);
    
    KC_GenID::Z_idGen result;
    try {
        transport->open();
        
        client.genId(result, keyType);
        
        transport->close();
    } catch( TException &tx){
        std::cerr << "ERROR WZ_GenIdService: " << tx.what() << std::endl;
    }
    
    if (result.errorCode >= 0) {
        return result.data;
    } else {
        return result.errorCode;
    }
    
}

int64_t 
WZ_GenIdService::W_getRangeId(const std::string &keyType, const int64_t& range) {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost",6789));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_GenID::KC_GenIDClient client(protocol);
    
    KC_GenID::Z_rangeId result;
    try {
        transport->open();
        
        client.getRangeId(result, keyType, range);
        
        transport->close();
    } catch( TException &tx){
        std::cerr << "ERROR WZ_GenIdService: " << tx.what() << std::endl;
    }
    
    if (result.errorCode >= 0) {
        return result.data;
    } else {
        return result.errorCode;
    }
}

int64_t
WZ_GenIdService::W_getIdValue(const std::string &keyType) {
     boost::shared_ptr<TTransport> socket(new TSocket("localhost",6789));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_GenID::KC_GenIDClient client(protocol);
    
    KC_GenID::Z_idValue result;
    try {
        transport->open();
        
        client.getIdValue(result, keyType);
        
        transport->close();
    } catch( TException &tx){
        std::cerr << "ERROR WZ_GenIdService: " << tx.what() << std::endl;
    }
    
    if (result.errorCode >= 0) {
        return result.data;
    } else {
        return result.errorCode;
    }
}

