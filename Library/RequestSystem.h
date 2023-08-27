//
// Created by amine on 7/22/2023.
//

#ifndef LIBRARY_SYSTEM_REQUESTSYSTEM_H
#define LIBRARY_SYSTEM_REQUESTSYSTEM_H

#include <vector>
#include <string>
#include "DB/database.h"
#include "Book/book.h"
#include "Users/Author/Author.h"

class RequestSystem {
    DATABASE* db;
public:
    RequestSystem(DATABASE* db) : db(db) {}
    enum RequestType{
        PUBLISH = 0,
        DELETE,
    };
    void sendRequest(std::string author, std::string book, RequestType type);
    std::vector<std::vector<std::string>> showRequests();
};


#endif //LIBRARY_SYSTEM_REQUESTSYSTEM_H
