#include <vector>
#include <algorithm>
#include "Reader.h"

void Reader::buy(Book &book) {
    std::vector<Book> owned;
    //TODO:fill owned table
    if (std::find(owned.begin(), owned.end(), book) == owned.end()) {

    } else {
        std::cout << "The book was already bought" << std::endl;
    }
}

void Reader::rate(Book &book) {
    std::cout << "Rate the book from 1 to 5." << std::endl;
    int rating;
    std::cin >> rating;
    while (rating < 1 or rating > 5) {
        std::cout << "Incorrect rating was given!\nRate the book from 1 to 5!" << std::endl;
        std::cin >> rating;
    }
    book.rate(rating);
}

std::string Reader::newUserSQL() {
    return "INSERT INTO USERS (name, password) "  \
                "VALUES ('" + mail + "', '" + password + "');";
}

std::string Reader::deleteUserSQL() {
    return "DELETE FROM USERS (name, password) "  \
                "VALUES ('" + mail + "', '" + password + "');";
}
