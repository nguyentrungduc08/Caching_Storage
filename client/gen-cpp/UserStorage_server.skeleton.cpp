// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

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

class UserStorageHandler : virtual public UserStorageIf {
 public:
  UserStorageHandler() {
    // Your initialization goes here
  }

  int32_t createUser(const UserProfile& user) {
    // Your implementation goes here
    printf("createUser\n");
  }

  void getUser(UserProfile& _return, const int32_t uid) {
    // Your implementation goes here
    printf("getUser\n");
  }

  int32_t editUser(const int32_t uid, const UserProfile& user) {
    // Your implementation goes here
    printf("editUser\n");
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

