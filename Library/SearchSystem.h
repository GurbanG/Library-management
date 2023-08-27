#pragma once

#include "Book/Book.h"
#include "ManagingSystem.h"

class SearchSystem {
private:
    DATABASE *db;
public:
    SearchSystem(DATABASE *db);

    std::vector<Book> searchByName(std::string &bookName);

    std::vector<Book> searchByAuthor(std::string &authorName);

    std::vector<Book> searchByGenre(std::string &genre);
};
