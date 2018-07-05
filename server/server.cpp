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
//using namespace  ::KC_Storage;
using namespace kyotocabinet;

Task1::listUser _listUsers;
Task1::Users _UserData;
Task1::idcounter _idCounter = 0;

class UserStorageHandler : virtual public UserStorageIf {
private:
    //    HashDB db;

public:

    UserStorageHandler() {
        // Your initialization goes here
        std::cout << "Server Starting........." << std::endl;
        std::cout << std::endl;

        //        WZ_GenIdService wzGenID;
        //        std::cout << "Id generate form service:  " << wzGenID.W_genID("test") << std::endl;

    }

    ~UserStorageHandler() {
        std::cout << "Server shutdown!!! " << std::endl;
    }

    int32_t createUser(const UserProfile& user) {
        // Your implementation goes here
        printf("createUser\n");
        UserProfile usert = user;
        putOption::type putType = putOption::type::add;
        WZ_GenIdService wzGenId;
        int zId = wzGenId.W_genID("test");

        usert.__set_uid(zId);
        this->showProfile(usert);

        std::string binaryString = serialize(zId);
        std::string sid = binaryString;
        std::string serialized_string = this->serialize(usert);

        WZ_StorageService wzStorage;
        KC_Storage::putOption::type opt = KC_Storage::putOption::type::add;
        bool ok = wzStorage.W_put(sid, serialized_string, opt);
        if (ok) {
            std::cout << "Store user's profile success" << std::endl;
            return zId;
        } else {
            return -1;
        }
    }

    void getUser(UserProfile& _return, const int32_t uid) {
        // Your implementation goes here
        printf("getUser\n");
        UserProfile tmp;
        tmp.__set_uid(-1);

        std::string binaryString = serialize(uid);
        std::string sid = binaryString;
        std::string raw;

        WZ_StorageService wzStorage;
        raw = wzStorage.W_get(sid);
        if (raw != "") {
            UserProfile tmpUser = deserialize(raw);
            _return = tmpUser;
            this->showProfile(tmpUser);
        } else {
            _return = tmp;
        }

    }

    int32_t editUser(const int32_t uid, const UserProfile& user) {
        printf("editUser \n");
        UserProfile uProfile = user;

        std::string binaryString = serialize(uid);
        std::string sid = binaryString;
        std::string serialized_string = this->serialize(uProfile);

        KC_Storage::putOption::type opt = KC_Storage::putOption::type::update;
        WZ_StorageService wzStorage;
        bool ok = wzStorage.W_put(sid, serialized_string, opt);
        this->showProfile(uProfile);
        if (ok){
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

    std::string serialize(idcounter uid) {
        std::string binaryString(4, '\n');
        for (int i = 0; i < 4; i++)
            binaryString[3 - i] = (uid >> (i * 8));
        return binaryString;
    }

    idcounter deserializeID(std::string binaryString) {

    }

    UserProfile deserialize(std::string serializeString) {
        shared_ptr<TMemoryBuffer> strBuffer(new TMemoryBuffer());
        shared_ptr<TBinaryProtocol> binaryProtcol(new TBinaryProtocol(strBuffer));

        strBuffer->resetBuffer((uint8_t*) serializeString.data(), static_cast<uint32_t> (serializeString.length()));
        UserProfile user;
        user.read(binaryProtcol.get());
        return user;
    }

private:

    void showProfile(const UserProfile& profile) {
        std::cout << "Detail User's Profile" << std::endl;
        std::cout << "- UId: " << profile.uid << std::endl;
        std::cout << "- Name: " << profile.name << std::endl;
        std::cout << "- age: " << profile.age << std::endl;
        std::cout << "- gender: " << profile.gender << std::endl;
    }

};


void runTSimpleServer();
void runTNonblockingServer();
void runTThreadPoolServer();
void runTThreadedServer();
void runKCDatabaseService();

int main(int argc, char **argv) {

    runTSimpleServer();
    //    runTThreadedServer();
    //    runTThreadPoolServer();
    //    runTNonblockingServer();

    return 0;
}

void
runTSimpleServer() {
    std::cout << "runTSimpleServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler> handler(new UserStorageHandler());
    shared_ptr<TProcessor> processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();

    return;
}

void
runTThreadedServer() {
    std::cout << "runTThreadedServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler> handler(new UserStorageHandler());
    shared_ptr<TProcessor> processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();

    return;
}

void
runTThreadPoolServer() {
    std::cout << "runTThreadPoolServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler> handler(new UserStorageHandler());
    shared_ptr<TProcessor> processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    server.serve();
    return;
}

void
runTNonblockingServer() {
    std::cout << "runTNonblockingServer" << std::endl;
    int port = 9090;
    shared_ptr<UserStorageHandler> handler(new UserStorageHandler());
    shared_ptr<TProcessor> processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TNonblockingServer server(processor, protocolFactory, port, threadManager);
    server.serve();
    return;
}