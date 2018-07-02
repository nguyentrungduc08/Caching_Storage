/* 
 * File:   newsimpletest.cpp
 * Author: cpu10664-local
 *
 * Created on Jul 2, 2018, 3:23:48 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "newsimpletest test 1" << std::endl;
}

void test2() {
    std::cout << "newsimpletest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


/*
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
//        std::string sid = std::to_string(uid);
//        std::string raw;
//        bool isFound = db.get(sid, &raw);
//        if (isFound){
//            UserProfile tmpUser = deserialize(raw);
//            _return = tmpUser;
//        } else {
//            _return = tmp;
//        }
        
        //connect KC_service
        std::string sid = std::to_string(uid);
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
 
 */