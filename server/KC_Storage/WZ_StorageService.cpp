/* 
 * File:   WZ_StorageService.cpp
 * Author: cpu10664-local
 * 
 * Created on July 4, 2018, 11:18 AM
 */

#include "WZ_StorageService.h"

WZ_StorageService::WZ_StorageService() {
}

WZ_StorageService::WZ_StorageService(const WZ_StorageService& orig) {
}

WZ_StorageService::~WZ_StorageService() {
}

int64_t
WZ_StorageService::W_getTotalRecord() {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_StorageClient client(protocol);
    Z_total total;
    try {
        transport->open();
        client.totalRecord(total);
        transport->close();
    } catch (TException &tx) {
        std::cerr << "ERROR: " << tx.what() << std::endl;
    }
    if (total.errorCode >= 0 ){
        return total.total;
    } else {
        return total.errorCode;
    }
}

std::string
WZ_StorageService::W_get(const std::string &key) {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_StorageClient client(protocol);
    Z_data data;
    try {
        transport->open();
        client.get(data, key);
        transport->close();
    } catch (TException &tx) {
        std::cerr << "ERROR: " << tx.what() << std::endl;
    }
    
    if (data.errorCode >= 0 ){
        return data.data;
    } else {
        return "";
    }
}

bool 
WZ_StorageService::W_put(const std::string& key, const std::string& value, const putOption::type& opt) {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_StorageClient client(protocol);
    Z_status status;
    try {
        transport->open();
        client.put(status, key, value, opt);
        transport->close();
    } catch (TException &tx) {
        std::cerr << "ERROR: " << tx.what() << std::endl;
    }
    
    return status.status;
}

bool
WZ_StorageService::W_remove(const std::string& key) {
    boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KC_StorageClient client(protocol);
    Z_status status;
    try {
        transport->open();
        client.remove(status, key);
        transport->close();
    } catch (TException &tx) {
        std::cerr << "ERROR: " << tx.what() << std::endl;
    }
    
    return status.status;
}
