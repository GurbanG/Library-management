#ifndef LIBRARY_SYSTEM_MAILSYSTEM_H
#define LIBRARY_SYSTEM_MAILSYSTEM_H


#include "DB/database.h"

class MailSystem {
private:
    DATABASE* db;
public:
    MailSystem(DATABASE* db) : db(db) {}

    std::vector<std::vector<std::string>> showRequests();

    void sendRequest();
};


#endif //LIBRARY_SYSTEM_MAILSYSTEM_H
