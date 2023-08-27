//
// Created by amine on 7/22/2023.
//

#include "RequestSystem.h"

void RequestSystem::sendRequest(std::string author, std::string book, RequestType type) {
    std::string sql = "INSERT INTO REQUESTS VALUES(" + author +", "+ book + ", "+ std::to_string(type) +");";
    db->execute(sql);
}

std::vector<std::vector<std::string>> RequestSystem::showRequests() {
    std::string sql = "SELECT * FROM REQUESTS;";
    return db->requestsTableQuery(sql);
}
