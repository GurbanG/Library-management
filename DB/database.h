#pragma once
#include <utility>
#include <vector>
#include "Book/Book.h"
#include "DB/sqlite3.h"

class DATABASE {
private:
    sqlite3 *DB;
    int dp_return_code;
    char *zErrMsg = 0;
public:
    DATABASE();
    ~DATABASE();
    void execute(std::string command);
    void observe();
    void dropAll();
    std::vector<std::vector<std::string>> bookTableQuery(std::string sql);
    std::vector<std::vector<std::string>> userTableQuery(std::string sql);
    std::vector<std::vector<std::string>> adminTableQuery(std::string sql);
    std::vector<std::vector<std::string>> authorTableQuery(std::string sql);
    std::vector<std::vector<std::string>> requestsTableQuery(std::string sql);

};