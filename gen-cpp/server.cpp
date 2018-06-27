// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include <bits/stdc++.h>

#include "UserStorage.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::Task1;

Task1::listUser     _listUsers;
Task1::idcounter    _idCounter;

class UserStorageHandler : virtual public UserStorageIf {
public:
    UserStorageHandler() {
        // Your initialization goes here
        std::cout << "Server Starting........." <<std::endl;
        std::cout << std::endl;
    }

    int32_t createUser(const UserProfile& user) {
        // Your implementation goes here
        //UserProfile usert = user;
        
        _listUsers.emplace_back(user);
        std::cout << "num of list user: " << _listUsers.size() << std::endl;
        printf("createUser\n");
    }

    void getUser(UserProfile& _return, const int32_t uid) {
        // Your implementation goes here
        printf("getUser\n");
    }

    void editUser(const int32_t uid) {
        // Your implementation goes here
        std::cout << "uid from client " << uid << std::endl;
        printf("editUser \n");
    }
};

int main(int argc, char **argv) {
    int port = 9090;
    shared_ptr<UserStorageHandler> handler(new UserStorageHandler());
    shared_ptr<TProcessor> processor(new UserStorageProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
    return 0;
}
