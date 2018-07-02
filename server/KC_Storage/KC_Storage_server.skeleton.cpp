// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "KC_Storage.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::KC_Storage;

class KC_StorageHandler : virtual public KC_StorageIf {
 public:
  KC_StorageHandler() {
    // Your initialization goes here
  }

  int32_t totalRecord() {
    // Your implementation goes here
    printf("totalRecord\n");
  }

  void get(std::string& _return, const std::string& key) {
    // Your implementation goes here
    printf("get\n");
  }

  bool put(const std::string& key, const std::string& value, const putOption::type opt) {
    // Your implementation goes here
    printf("put\n");
  }

  bool remove(const std::string& key) {
    // Your implementation goes here
    printf("remove\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<KC_StorageHandler> handler(new KC_StorageHandler());
  shared_ptr<TProcessor> processor(new KC_StorageProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

