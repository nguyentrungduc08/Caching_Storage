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
//    UserProfile u;
//    u.uid = 0;
//    u.name = "test";
//    u.age = 1;
//    u.gender = 1;
//    Zcache::getInstance().add(0, u);    
//
//    UserProfile e;
//    Zcache::getInstance().get(0, e);
//    std::cout << "hello " << e.name << std::endl;   

    this->_thread.start(*this); // start thread waiting to handle notification queue.
}

void
UserStorageHandler::run() {
    std::cout << "log thread run to get notifications" << std::endl;
    AutoPtr<Notification> pNf(_queue.waitDequeueNotification()); //
    while (pNf) {
        NotificationStoreProfile* pWorkNf = dynamic_cast<NotificationStoreProfile*> (pNf.get()); //get notification from NotificationQueue
        if (pWorkNf && ThreadPool::defaultPool().available() > 0) {
            shared_ptr<Z_Worker> worker(new Z_Worker(pWorkNf->getKey(), pWorkNf->getData(), pWorkNf->getPutOption()));
            ThreadPool::defaultPool().start(*(worker.get())); // set task for Worker
            pNf = _queue.waitDequeueNotification(); // get Net nofitication if available in queue
        }
    }
}

UserStorageHandler::UserStorageHandler(const UserStorageHandler& orig) {

}

UserStorageHandler::~UserStorageHandler() {
    // wait until all work is done
    while (!this->_queue.empty()) {
        Poco::Thread::sleep(100);
    }
    // tell workers they're done
    this->_queue.wakeUpAll();

    ThreadPool::defaultPool().joinAll();

    std::cout << "Server shutdown!!! " << std::endl;
}

/*
 * create new user profile and store in KC.
 *   
 */
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
