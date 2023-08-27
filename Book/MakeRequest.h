#pragma once
#include "Book/Book.h"
#include "Other/Commands.h"


class MakeRequest {
private:
    Book::BookDTO book;
public:
    MakeRequest(Book::BookDTO &book) : book(book) {};

    std::string insert();

    std::string remove();

    std::string update(Commands command);
};
