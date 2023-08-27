#ifndef LIBRARY_SYSTEM_PUBLISHFUNC_H
#define LIBRARY_SYSTEM_PUBLISHFUNC_H

#include "Book/MakeRequest.h"

class PublishFunc {
public:
    PublishFunc() {}

    std::string publishBook(Book &book) {
        //TODO check that author has not the same book (not necessary)
        return book.makeRequest().insert();
    }

    std::string deleteBook(Book &book) {
        //TODO check that book belongs Author
        return book.makeRequest().remove();
    }
};

#endif //LIBRARY_SYSTEM_PUBLISHFUNC_H