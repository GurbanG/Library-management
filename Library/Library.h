#pragma once
#include <vector>
#include <string>
#include <map>
#include "ManagingSystem.h"
#include "SearchSystem.h"
#include "SortSystem.h"
#include "Authentication.h"
#include "DB/database.h"
#include "MailSystem.h"
#include "RequestSystem.h"

class Library {
protected:
    std::vector<Book> allBooks;
    std::map<std::string, std::vector<Book>> storage;
    DATABASE db;
public:

    Library() {}

    ManagingSystem managingSystem();

    SearchSystem searchSystem();

    SortSystem sortSystem();

    Authentication authSystem();

    MailSystem mailSystem();

    RequestSystem requestSystem();
};

