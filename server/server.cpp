#include <bits/stdc++.h>

#include "UserStorage.h"
#include <thrift/protocol/TBinaryProtocol.h>

#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>

#include <thrift/transport/TServerSocket.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TBufferTransports.h>

//Kyoto Cabinet database
#include <kchashdb.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace  ::Task1;
using namespace kyotocabinet;

Task1::listUser     _listUsers;
Task1::Users        _UserData;
Task1::idcounter    _idCounter = 0;



class UserStorageHandler : virtual public UserStorageIf {
private:
    HashDB db;
public:
    UserStorageHandler() {
        // Your initialization goes here
        std::cout << "Server Starting........." <<std::endl;
        std::cout << std::endl;
        
        if (db.open("db.kch", HashDB::OWRITER | HashDB::OCREATE)) {
            std::cout << "open KC database success" << std::endl; 
        } else {
            std::cerr << "open error: " << db.error().name() << std::endl; 
        }
    }
    
    ~UserStorageHandler() {
        if (db.close()) {
            std::cout << "close KC database success" << std::endl;
        } else {
            std::cerr << "close error: " << db.error().name() << std::endl;
        }
    }

    int32_t createUser(const UserProfile& user) {
        // Your implementation goes here
        printf("createUser\n");
        UserProfile usert = user;
        ++_idCounter;
        usert.__set_uid(_idCounter);
        
        _UserData[_idCounter] = usert;
        
        std::string sid = std::to_string(_idCounter);
        
//        std::cout << "total user: " << _UserData.size() << std::endl;
        std::string serialized_string = this->serialize(usert);
        
        db.set(sid, serialized_string);
        
//        std::cout << "object user: [ " << serialized_string << "]" << std::endl;
        
        return _idCounter;
    }

    void getUser(UserProfile& _return, const int32_t uid) {
        // Your implementation goes here
        printf("getUser\n");
        UserProfile tmp;
        tmp.__set_uid(-1);

//        Task1::Users::iterator it;
//        it = _UserData.find(uid);
//        if (it != _UserData.end()){
//            _return = it->second;
//            //return;
//        }
        
        //using KC
        std::string sid = std::to_string(uid);
        std::string raw;
        bool isFound = db.get(sid, &raw);
        if (isFound){
            //std::cout << "get data form db" << raw << std::endl;
            UserProfile tmpUser = deserialize(raw);
            //std::cout << "uid db: " << tmpUser.uid << std::endl;
            //std::cout << "name db: " << tmpUser.name << std::endl;
            //std::cout << "age db: " << tmpUser.age << std::endl;
            //std::cout << "gender db: " << tmpUser.gender << std::endl;
            _return = tmpUser;
        } else {
            _return = tmp;
        }
    }

    int32_t editUser(const int32_t uid, const UserProfile& user) {
        // Your implementation goes here
        std::cout << "uid from client " << uid << std::endl;
        printf("editUser \n");
        
        Task1::Users::iterator it;
        it = _UserData.find(uid);
        if (it != _UserData.end()){
            it->second.name     = user.name;
            it->second.age      = user.age;
            it->second.gender   = user.gender;
            return it->second.uid;
        }
        
        std::string sid = std::to_string(uid);
        std::string raw;
        bool isFound = db.get(sid, &raw);
        if (isFound){
            UserProfile up = user;
            raw = serialize(up);
            db.set(sid, raw);    
            return uid;
        }
        
        return -1;
    }
    
    std::string serialize(UserProfile& obj) {
        shared_ptr<TMemoryBuffer> transportOut(new TMemoryBuffer());
        shared_ptr<TBinaryProtocol> protocolOut(new TBinaryProtocol(transportOut));
        obj.write(protocolOut.get());
        std::string serialized_string = transportOut->getBufferAsString();
        return serialized_string;
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