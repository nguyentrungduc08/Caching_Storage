/* build cmd 
g++ gen-cpp/UserStorage.cpp gen-cpp/user_profile_types.cpp gen-cpp/user_profile_constants.cpp client.cpp -o client -lthrift
*/

#include <bits/stdc++.h>

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


//protype function
void 		printMenuOption();
//int32_t 	createProfileUser(const UserStorageClient&);

int main(int argc, char **argv){
	boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	UserStorageClient client(protocol);

	try{ 
    		transport->open();
		
			
		do {
			printMenuOption();
			int cmd = 0;	
			bool loop = true;
			std::cin >> cmd;
			switch(cmd){
				case 0:
					loop = false;
					break;
				case 1:
					{
						//std::cout << createProfileUser(client) << std::endl;		 
						UserProfile profile;
         					profile.uid = -1;
         					std::cout << "name : ";
         					std::cin >> profile.name;
         					std::cout << "age: ";
         					std::cin >> profile.age;
         					std::cout << "gender: ";
         					std::cin >> profile.gender;
        	 				int32_t res = client.createUser(profile);
						std::cout << "Success. Uid form server : " << res << std::endl;
					}
					break;	
				case 2:
					{
						UserProfile profile;
						int32_t uid;
						std::cout << "uid: ";
						std::cin >> uid;
						client.getUser(profile, uid);
						if (profile.uid == -1){
							std::cout << "invalid uid " << uid << "!!!" << std::endl;
						} else {
							std::cout << "profile User with id: " << uid << std::endl;
							std::cout << "name : " << profile.name << std::endl;
							std::cout << "age: "   << profile.age << std::endl;
							std::cout << "gender: " << profile.gender << std::endl;
						}
					
					}
					break;
				case 3: {
						UserProfile profile;
						int32_t uid;
						std::cout << "uid: ";
						std::cin >> uid;
						std::cout << "name: ";
						std::cin >> profile.name;
						std::cout << "age: ";
						std::cin >> profile.age;
						std::cout << "gender: ";
						std::cin >> profile.gender;
						
						int32_t res = client.editUser(uid, profile);
						if (res == -1){
							std::cout << "invalid uid " << uid << "!!!" << std::endl;
						} else {
							std::cout << "Update success profile id " << uid << std::endl; 
						}
						
					}
					break;
				
				default:
					std::cout << "try again" << std::endl;
					break;				
			}

			if (!loop)
				break;	
		
		} while (1);
			
		
			
		//int32_t uid = 8;
		//client.editUser(uid);

		std::cout << "DONE" << std::endl;
		transport->close();
    	
	}catch (TException &tx){
      		std::cout<<"Error: " <<tx.what() <<std::endl;
    	}	
	
	return 0;
}

void 
printMenuOption(){
	std::cout << "........................" << std::endl;
	std::cout << "Choose option: " 		<< std::endl;
	std::cout << "1. create new user " 	<< std::endl;
	std::cout << "2. get user " 		<< std::endl;
	std::cout << "3. edit user "		<< std::endl;
	std::cout << "0. exit! " 		<< std::endl;
	return;
}

/*
int32_t 	
createProfileUser(const UserStorageClient& client){
	std::string name;
	int16_t age;
	int16_t gender;
	UserProfile profile;
	profile.uid = -1;
	std::cout << "name : ";
	std::cin >> profile.name;
	std::cout << "age: ";
	std::cin >> profile.age;
	std::cout << "gender: ";
	std::cin >> profile.gender;
	int32_t res = client.createUser(profile);
	return res;
}
*/

