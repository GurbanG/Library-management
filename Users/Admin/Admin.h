#ifndef LIBRARY_SYSTEM_ADMIN_H
#define LIBRARY_SYSTEM_ADMIN_H

#include "AdministratingFunc.h"
#include "Library/Library.h"

class Admin {
private:
    Library *library;
public:
    Admin(Library &lib);

    void requestsMail();

    void addBook(Book &book);

    void deleteBook(Book &book);

    void deleteUser(Reader &reader);
};


#endif //LIBRARY_SYSTEM_ADMIN_H