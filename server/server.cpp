#include <bits/stdc++.h>

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

#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Subsystem.h"

#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"

#include <boost/make_shared.hpp>

#include "UserStorageHandler.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;


using boost::shared_ptr;

using namespace ::Task1;

class UserProfileStorageService : public Poco::Util::ServerApplication {
public:
    UserProfileStorageService() : _helpRequested(false) {
        std::cout << "Start POCO Application service..." << std::endl;
        this->_host = "localhost";
        this->_port = 9090;
        this->_helpRequested = false;
    }

protected:

    void
    initialize(Application& self) {
        loadConfiguration(); // load default configuration files, if present
        Application::initialize(self);
        // add your own initialization code here
    }

    void
    uninitialize() {
        // add your own uninitialization code here
        Application::uninitialize();    
    }

    void
    reinitialize(Application& self) {
        Application::reinitialize(self);
        // add your own reinitialization code here
    }

    void
    defineOptions(OptionSet& options) {
        ServerApplication::defineOptions(options);

        options.addOption(
                Option("help", "h", "display help information on command line arguments")
                .required(false)
                .repeatable(false)
                .callback(OptionCallback<UserProfileStorageService>(this, &UserProfileStorageService::handleHelp)));

        options.addOption(
                Option("port", "p", "Listening port (default 9090)")
                .required(false)
                .repeatable(false)
                .argument("<port>")
                .callback(OptionCallback<UserProfileStorageService>(this, &UserProfileStorageService::setPort)));

        options.addOption(
                Option("host", "ip", "default (localhost)")
                .required(false)
                .repeatable(false)
                .argument("<host>")
                .callback(OptionCallback<UserProfileStorageService>(this, &UserProfileStorageService::setHost)));

        options.addOption(
                Option("bind", "b", "bind option value to test.property")
                .required(false)
                .repeatable(false)
                .argument("<value>")
                .binding("test.property"));
    }

    void
    handleHelp(const std::string& name, const std::string& value) {
        this->_helpRequested = true;
        displayHelp();
        stopOptionsProcessing();
    }

    void
    setPort(const std::string& name, const std::string& value) {
        std::cout << "set port - " << value << " - " << name << std::endl;
        this->_port = std::stoi(value);
        std::cout << "value int " << this->_port + 1 << std::endl;
    }

    void
    setHost(const std::string& name, const std::string& value) {
        std::cout << "set host - " << value << " - " << name << std::endl;
    }

    void
    displayHelp() {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("[OPTIONS]");
        helpFormatter.setHeader("C++ server using to store user profile ");
        helpFormatter.format(std::cout);
    }

    int
    main(const ArgVec& args) {
        std::cout << "begin main" << std::endl;
        if (!_helpRequested) {
            runTSimpleServer();
            //            runTThreadedServer();
            //            runTThreadPoolServer();
            //            runTNonblockingServer();
        }
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
    int _port;
    std::string _host;

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
};

//POCO_APP_MAIN(UserProfileStorageService)

int main(int argc, char* argv[]) {
    UserProfileStorageService serverApp;
    return serverApp.run(argc, argv);
}

