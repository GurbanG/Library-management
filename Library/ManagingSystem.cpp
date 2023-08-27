#include "ManagingSystem.h"
#include "Book/MakeRequest.h"

ManagingSystem::ManagingSystem(DATABASE *db) {
    this->db = db;
}

void ManagingSystem::addBook(Book &book) {
    std::string sql = book.makeRequest().insert();
    try {
        db->bookTableQuery(sql);
    } catch (...) {
        std::cerr << "Error: could not add book" << std::endl;
    }
}

void ManagingSystem::deleteBook(Book &book) {
    std::string sql = book.makeRequest().remove();
    try {
        db->bookTableQuery(sql);
    } catch (...) {
        std::cerr << "Error: could not delete book" << std::endl;
    }
}

void ManagingSystem::addUser(Reader &user) {
    //Adds new user to DB. It could be either user or author
    db->execute(user.newUserSQL());
}

void ManagingSystem::deleteUser(Reader &user) {
    db->execute(user.deleteUserSQL());
}
