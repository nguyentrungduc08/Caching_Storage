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

//Kyoto Cabinet database
#include <kchashdb.h>

#include "KC_Storage/KC_Storage.h"

#include "KC_GenID/WZ_GenIdService.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace  ::Task1;
using namespace  ::KC_Storage;
using namespace kyotocabinet;

Task1::listUser     _listUsers;
Task1::Users        _UserData;
Task1::idcounter    _idCounter = 0;

class UserStorageHandler : virtual public UserStorageIf {
private:
//    HashDB db;
//    shared_ptr<KC_StorageClient> KCClient;
//    shared_ptr<TTransport> transport;
public:
    UserStorageHandler() {
        // Your initialization goes here
        std::cout << "Server Starting........." <<std::endl;
        std::cout << std::endl;
        
        boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KC_StorageClient KCClinet (protocol);
        
//        try {
//            transport->open();
//            int nu = KCClinet.totalRecord();
//            _idCounter = nu;
//            std::cout << "total user's profile " << nu << std::endl;
//            transport->close();
//        } catch (TException &tx){
//            std::cerr << "ERROR: " << tx.what() << std::endl;
//            exit(0);
//        }
        
        WZ_GenIdService wzGenID;
        std::cout << "Id generate form service:  " << wzGenID.W_genID("test") << std::endl;
        
        
    }
    
    ~UserStorageHandler() {
        
    }

    int32_t createUser(const UserProfile& user) {
        // Your implementation goes here
        printf("createUser\n");
        UserProfile usert = user;
        putOption::type putType = putOption::type::add;
        ++_idCounter;
        usert.__set_uid(_idCounter);

        std::string binaryString = serialize(_idCounter);
        std::string sid = binaryString;
        std::string serialized_string = this->serialize(usert);
        
        boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KC_StorageClient KCClinet (protocol);
        
        try {
            transport->open();
            bool ok = KCClinet.put(sid, serialized_string, putType);
            transport->close();
        } catch (TException &tx){
            std::cerr << "ERROR: " << tx.what() << std::endl;
        }
        
        return _idCounter;
    }

    void getUser(UserProfile& _return, const int32_t uid) {
        // Your implementation goes here
        printf("getUser\n");
        UserProfile tmp;
        tmp.__set_uid(-1);
        
        std::string binaryString = serialize(uid);
        std::cout << "out: " << binaryString << std::endl;
        //connect KC_service
        std::string sid = binaryString;
        std::string raw;
        
        boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KC_StorageClient KCClinet (protocol);
        
        try {
            transport->open();
            KCClinet.get(raw, sid);
            if (raw != ""){
                UserProfile tmpUser = deserialize(raw);
                _return = tmpUser;
                std::cout << "tmpuser name: " << tmpUser.name << std::endl;
                std::cout << "tmpuser id: " << tmpUser.uid << std::endl;
            } else { 
                _return = tmp;
            }
            
            transport->close();
        } catch (TException &tx){
            std::cerr << "ERROR: " << tx.what() << std::endl;
        }
    }

    int32_t editUser(const int32_t uid, const UserProfile& user) {
        printf("editUser \n");
        UserProfile uProfile = user; 
        putOption::type opt = putOption::update;

        std::string binaryString = serialize(uid);
        std::string sid = binaryString;
        std::string serialized_string = this->serialize(uProfile);
        
        boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9876));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        KC_StorageClient KCClient(protocol);
        
        try {
            transport->open();
            bool ok = KCClient.put(sid, serialized_string, opt);
            if (ok) {
                return uid;
            }
            transport->close();
        } catch (TEOFException &tx){
            std::cerr << "ERROR: " << tx.what() << std::endl;
        }
//        bool isFound = db.get(sid, &raw);
//        if (isFound){
//            UserProfile up = user;
//            raw = serialize(up);
//            db.set(sid, raw);    
//            return uid;
//        }
        
        return -1;
    }
    
    std::string serialize(UserProfile& obj) {
        shared_ptr<TMemoryBuffer> transportOut(new TMemoryBuffer());
        shared_ptr<TBinaryProtocol> protocolOut(new TBinaryProtocol(transportOut));
        obj.write(protocolOut.get());
        std::string serialized_string = transportOut->getBufferAsString();
        return serialized_string;
    }

    std::string serialize(idcounter uid){
        std::string binaryString(4,'\n'); 
        for (int i = 0; i < 4; i++)
            binaryString[3 - i] = (uid >> (i * 8));
        return binaryString;
    }
    
    idcounter deserializeID(std::string binaryString){
        
    }
    
    UserProfile deserialize(std::string serializeString){        
        shared_ptr<TMemoryBuffer> strBuffer(new TMemoryBuffer());
        shared_ptr<TBinaryProtocol> binaryProtcol(new TBinaryProtocol(strBuffer));

        strBuffer->resetBuffer((uint8_t*)serializeString.data(), static_cast<uint32_t>(serializeString.length()));
        UserProfile user;
        user.read(binaryProtcol.get());
        return user;
    }
    
};


void        runTSimpleServer();
void        runTNonblockingServer();
void        runTThreadPoolServer();
void        runTThreadedServer();
void        runKCDatabaseService();

int main(int argc, char **argv) {
   
    runTSimpleServer();
//    runTThreadedServer();
//    runTThreadPoolServer();
//    runTNonblockingServer();
    
    return 0;
}

void 
runTSimpleServer(){
    std::cout << "runTSimpleServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler>  handler(new UserStorageHandler());
    shared_ptr<TProcessor>          processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport>    serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory>   transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory>    protocolFactory(new TBinaryProtocolFactory()); 
    
    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    
    return;
}

void 
runTThreadedServer(){
    std::cout << "runTThreadedServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler>  handler(new UserStorageHandler());
    shared_ptr<TProcessor>          processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport>    serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory>   transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory>    protocolFactory(new TBinaryProtocolFactory()); 
    
    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    
    return;
}

void 
runTThreadPoolServer()
{
    std::cout << "runTThreadPoolServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler>  handler(new UserStorageHandler());
    shared_ptr<TProcessor>          processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport>    serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory>   transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory>    protocolFactory(new TBinaryProtocolFactory()); 
    
    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
    
    TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    server.serve();
    return;
}


void        
runTNonblockingServer(){
    std::cout << "runTNonblockingServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler>  handler(new UserStorageHandler());
    shared_ptr<TProcessor>          processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport>    serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory>   transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory>    protocolFactory(new TBinaryProtocolFactory()); 
    
    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
    
    TNonblockingServer server(processor, protocolFactory, port, threadManager);
    server.serve();
    return;
}