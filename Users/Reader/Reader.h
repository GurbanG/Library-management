#ifndef LIBRARY_SYSTEM_READER_H
#define LIBRARY_SYSTEM_READER_H

#include <string>
#include <utility>
#include "Book/Book.h"

//TODO add balance field and logic
//TODO add "email" field as unique ID
//TODO add passcheck, word to recover password

class Reader {
private:
    std::string mail;
    std::string password;
//    PayingFunc payingFun;
//    CreditInfo creditInfo;
public:
    Reader() = default;

    Reader(std::string mail, std::string password) :
            mail(std::move(mail)), password(std::move(password)) {};

    void buy(Book& book);

    void rate(Book& book);

    void fillCreditInfo();

    std::string newUserSQL();
    std::string deleteUserSQL();
};


#endif //LIBRARY_SYSTEM_READER_H
