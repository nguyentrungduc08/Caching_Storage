/* 
 * File:   SubSystem.h
 * Author: ducnt
 *
 * Created on July 20, 2018, 2:12 PM
 */

#ifndef SUBSYSTEM_H
#define	SUBSYSTEM_H

#include <iostream>
#include <string>
#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/AutoPtr.h"

#include "UserStorage.h"
#include "LRUCache/LRUCache.h"
#include "LRUCache/LRUCache.cpp"

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
    
    bool find(const int &key) {
        return this->_cache.find(key);
    }
    
};


class Zconfiguration {
private:
    Zconfiguration() {
        std::cout << "construct create configuration" << std::endl;
    }
    Zconfiguration(const Zconfiguration& );
    void operator=(const Zconfiguration&);

public:
    ~Zconfiguration() {
        std::cout << "destructor release configuration" << std::endl;
    }

    static Zconfiguration& getInstance() {
        static Zconfiguration instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    
    int loadConfig(){
        Poco::AutoPtr<Poco::Util::IniFileConfiguration> pConf(new Poco::Util::IniFileConfiguration("/home/cpu10664-local/NetBeansProjects/Probation/Caching_Storage/config/Caching_Storage.ini"));
        std::cout << "____Configuration Information____" << std::endl;
        if (pConf->has("Caching_Storage.port")){
            try {
                this->_port = pConf->getInt("Caching_Storage.port");
                std::cout << "- Port: " << this->_port << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        
        if (pConf->has("Caching_Storage.hostKC_Storage_Service")){
            try {
                this->_hostStorageService = pConf->getString("Caching_Storage.hostKC_Storage_Service");
                std::cout << "- Host Storage service: " << this->_hostStorageService << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        
        if (pConf->has("Caching_Storage.portKC_Storage_Service")){
            try {
                this->_portStorageService = pConf->getInt("Caching_Storage.portKC_Storage_Service");
                std::cout << "- Port Storage service: " << this->_portStorageService << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        
        if (pConf->has("Caching_Storage.hostGenID_Service")){
            try {
                this->_hostGenIDService = pConf->getString("Caching_Storage.hostGenID_Service");
                std::cout << "- Host Generate Id service: " << this->_hostGenIDService << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        
        if (pConf->has("Caching_Storage.portGenID_Service")){
            try {
                this->_portGenIDService = pConf->getInt("Caching_Storage.portGenID_Service");
                std::cout << "- Port Generate Id service: " << this->_portGenIDService << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        
        if (pConf->has("Caching_Storage.numLocker")){
            try {
                this->_numLockers = pConf->getInt("Caching_Storage.numLocker");
                std::cout << "- Num lock mutex for thread-safe: " << this->_numLockers << std::endl;
            } catch ( Poco::SyntaxException& e ) {
                std::cerr << "writeValue: " << e.displayText() << std::endl;
                return -1;
            }
        }
        return 0;
    }
    
    std::string getHostGenIDService() {
        return this->_hostGenIDService;
    }
    
    int getPortGenIDService() {
        return this->_portGenIDService;
    }
    
    std::string getHostStorageService() {
        return this->_hostStorageService;
    }
    
    int getPortStorageService() {
        return this->_portStorageService;
    }
    
    int getNumLocker() {
        return this->_numLockers;
    }
    
private:
    std::string     _patch;  
    std::string     _hostGenIDService;
    std::string     _hostStorageService;
    int             _portGenIDService;
    int             _portStorageService;
    int             _port;
    int             _numLockers;
};

class Zlocker {
private: 
    Poco::Mutex     *m_locker;
    int32_t         m_size;
    Zlocker() {
    }
    
    Zlocker(const Zlocker& );
    void operator=(const Zlocker&);
    
    int32_t keyLocker(const int32_t & key){
        return key % this->m_size;
    }
    
    int32_t deserializeID(std::string binaryString) {
        int32_t res = 0;
        for(int i = 0; i < 4; ++i){
            int32_t tmp = std::bitset<8>((int32_t) binaryString[i] ).to_ulong();
            res+= (tmp << (i*8));
        }
        return res;
    }

public:
    static Zlocker& getInstance(){
        static Zlocker instance;
        
        return instance;
    }
    
    void alocateMemory(int _size){
        this->m_locker = new Poco::Mutex[_size];
        this->m_size = _size;
        std::cout << "created locker with size: " << this->m_size << std::endl;
    }
    
    Poco::Mutex &operator [](std::string key) {
        int index = keyLocker( deserializeID(key) );
        return this->m_locker[index];
    }
};

#endif	/* SUBSYSTEM_H */

