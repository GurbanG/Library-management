#pragma once

#include <utility>
#include <vector>
#include "Book/Book.h"
#include "Users/Reader/Reader.h"
#include "DB/sqlite3.h"
#include "DB/database.h"

class ManagingSystem {
private:
    DATABASE* db;
public:
    ManagingSystem(DATABASE *db);

    void addBook(Book &book);

    void deleteBook(Book &book);

    void deleteUser(Reader &user);

    void addUser(Reader &reader);
};
