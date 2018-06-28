/* build cmd 
g++ gen-cpp/UserStorage.cpp gen-cpp/user_profile_types.cpp gen-cpp/user_profile_constants.cpp testTSimpleServer.cpp -o testTSimpleServer -lthrift

using 
./test [num]
[num] - number of turns request to server

*/

#include <bits/stdc++.h>
#include <sys/time.h>
//Boost libraries
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//Thrift libraries
#include <thrift/protocol/TBinaryProtocol.h>             
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TSocket.h>                    
#include <thrift/transport/TBufferTransports.h>          
#include <thrift/transport/TTransportUtils.h>

//Including the thrift generated files 
#include "gen-cpp/UserStorage.h"

//Namespaces
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace Task1;
using boost::make_shared;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
	struct timeval now;
      	gettimeofday (&now, NULL);
      	return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

int numTurn;
bool resultTest;

//protype function
bool 		parseInputParameter(int argc, char **argv);
int		getCMD();
std::string	genName();


int main(int argc, char **argv){
	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	UserStorageClient client(protocol);
	
	if (!parseInputParameter(argc, argv)){
		return 0;
	}
	
	resultTest = true;

	try{ 
    		transport->open();
		/*	
		for(int i = 0; i < numTurn; ++i){
			std::cout << getCMD() << std::endl; 
		} 
	 	*/
		
		UserProfile profile;
	
		timestamp_t t0 = get_timestamp();

		for(int i = 0; i < 1000000; ++i){
			profile.name 	= "abcdddddadf";
			profile.age 	= 123;
			profile.gender  = 1;
			int32_t res = client.createUser(profile); 						
		}			
		timestamp_t t1 = get_timestamp();

    		double secs = (t1 - t0) / 1000000.0L;		
		std::cout << "time add prifile " << secs << std::endl;		
		std::cout << "DONE" << std::endl;
		transport->close();
    	
	}catch (TException &tx){
      		std::cout<<"Error: " <<tx.what() <<std::endl;
    	}	
	
	return 0;
}

bool
parseInputParameter(int argc, char **argv){
	if (argc < 2){
		std::cout << "Using ./testclient [num]" << std::endl;
		numTurn = 100000;
		return false;
	}
	
	std::string spps = std::string(argv[1]);
        std::stringstream ss(spps);
        numTurn = 0;
        ss >> numTurn;
        return true;
}

int	
getCMD(){
	return rand() % 3 + 1;
}
