#pragma once

#include "DB/database.h"
#include "Users/UserType.h"
//#include "Admin.h"
#include "Users/Author/Author.h"
#include "Users/Admin/Admin.h"
//TODO forgot password


class Admin;

class Authentication {
private:
    DATABASE *db;
public:
    Authentication(DATABASE *db);

    std::vector<std::string> getCredentials();

    Admin *adminLogIn(Library &lib);

    Author *authorLogIn();

    Author *authorSignUp();

    Reader *readerLogIn();

    Reader *readerSignUp();

};
