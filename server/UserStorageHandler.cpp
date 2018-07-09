/* 
 * File:   UserStorageHandler.cpp
 * Author: Ducnt
 * 
 * Created on July 6, 2018, 4:05 PM
 */

#include "UserStorageHandler.h"

UserStorageHandler::UserStorageHandler() {
    // Your initialization goes here
    std::cout << "Server Starting........." << std::endl;
    
    //create worker 
    this->_worker1 = make_shared<Worker>(this->_queue, "Worker1"); 
    this->_worker2 = make_shared<Worker>(this->_queue, "Worker2"); 
    this->_worker3 = make_shared<Worker>(this->_queue, "Worker3"); 
    
//    Worker worker11(this->_queue,"Worker1");
//    this->worker1 = worker11;
//    Worker worker22(this->_queue,"Worker2");
//    this->worker2 = worker22;
//    Worker worker33(this->_queue,"Worker3");
//    this->worker3 = worker33;
//    
//    // start workers
    
    shared_ptr<Worker> w = shared_ptr<Worker>(new Worker(this->_queue, "Worker1xxx"));
    ThreadPool::defaultPool().start(*(w.get()));
    
//    Worker w1;
//    ThreadPool::defaultPool().start(*(this->_worker1.get())); 
//    ThreadPool::defaultPool().start(*(this->_worker2.get())); 
//    ThreadPool::defaultPool().start(*(this->_worker3.get())); 
//    ThreadPool::defaultPool().
//    ThreadPool::defaultPool().start(this->_worker2);
//    ThreadPool::defaultPool().start(this->_worker3);
}

UserStorageHandler::UserStorageHandler(const UserStorageHandler& orig) {
    
}

UserStorageHandler::~UserStorageHandler() {
    // wait until all work is done
    while (!this->_queue.empty()){ 
        Poco::Thread::sleep(100);
    }
    
    // tell workers they're done
    this->_queue.wakeUpAll(); 
    
    ThreadPool::defaultPool().joinAll();
    
    std::cout << "Server shutdown!!! " << std::endl;
}

int32_t
UserStorageHandler::createUser(const UserProfile& user) {
    // Your implementation goes here
    printf("createUser\n");
    UserProfile usert = user;
    KC_Storage::putOption::type opt = KC_Storage::putOption::type::add;
    WZ_GenIdService wzGenId;
    int zId = wzGenId.W_genID("test");

    usert.__set_uid(zId);
    this->showProfile(usert);

    std::string binaryString = serialize(zId);
    std::string sid = binaryString;
    std::string serialized_string = this->serialize(usert);

//    WZ_StorageService wzStorage;
//    bool ok = wzStorage.W_put(sid, serialized_string, opt);
    
    this->_queue.enqueueNotification(new NotificationStoreProfile(sid, serialized_string, opt));
    
    if (true) {
        std::cout << "Store user's profile success" << std::endl;
        return zId;
    } else {
        return -1;
    }
}

void 
UserStorageHandler::getUser(UserProfile& _return, const int32_t uid) {
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

int32_t 
UserStorageHandler::editUser(const int32_t uid, const UserProfile& user) {
    printf("editUser \n");
    UserProfile uProfile = user;

    std::string binaryString = serialize(uid);
    std::string sid = binaryString;
    std::string serialized_string = this->serialize(uProfile);

    KC_Storage::putOption::type opt = KC_Storage::putOption::type::update;
    WZ_StorageService wzStorage;
    bool ok = wzStorage.W_put(sid, serialized_string, opt);
    this->showProfile(uProfile);
    if (ok) {
        return uid;
    }
    return -1;
}

std::string 
UserStorageHandler::serialize(UserProfile& obj) {
    shared_ptr<TMemoryBuffer> transportOut(new TMemoryBuffer());
    shared_ptr<TBinaryProtocol> protocolOut(new TBinaryProtocol(transportOut));
    obj.write(protocolOut.get());
    std::string serialized_string = transportOut->getBufferAsString();
    return serialized_string;
}

std::string 
UserStorageHandler::serialize(idcounter uid) {
    std::string binaryString(4, '\n');
    for (int i = 0; i < 4; i++)
        binaryString[3 - i] = (uid >> (i * 8));
    return binaryString;
}

idcounter 
UserStorageHandler::deserializeID(std::string binaryString) {

}

UserProfile 
UserStorageHandler::deserialize(std::string serializeString) {
    shared_ptr<TMemoryBuffer> strBuffer(new TMemoryBuffer());
    shared_ptr<TBinaryProtocol> binaryProtcol(new TBinaryProtocol(strBuffer));

    strBuffer->resetBuffer((uint8_t*) serializeString.data(), static_cast<uint32_t> (serializeString.length()));
    UserProfile user;
    user.read(binaryProtcol.get());
    return user;
}

void
UserStorageHandler::showProfile(const UserProfile& profile) {
    std::cout << "Detail User's Profile" << std::endl;
    std::cout << "- UId: " << profile.uid << std::endl;
    std::cout << "- Name: " << profile.name << std::endl;
    std::cout << "- age: " << profile.age << std::endl;
    std::cout << "- gender: " << profile.gender << std::endl;
}