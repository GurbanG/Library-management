#ifndef LIBRARY_SYSTEM_AUTHOR_H
#define LIBRARY_SYSTEM_AUTHOR_H


#include <string>
#include <utility>
#include "PublishFunc.h"

class Author {
private:
    std::string mail;
    std::string password;
    PublishFunc publishFunc;
//    PayingFunc payingFunc;
//    CreditInfo creditInfo;
public:
    Author(std::string mail, std::string password) :
            mail(std::move(mail)), password(std::move(password)) {};

    PublishFunc publish();
};


#endif //LIBRARY_SYSTEM_AUTHOR_H
