#include "SearchSystem.h"
#include "Other/Exceptions.h"

SearchSystem::SearchSystem(DATABASE *db) {
    this->db = db;
}

std::vector<Book> SearchSystem::searchByName(std::string &bookName) {
    std::string sql = "SELECT * FROM BOOKS WHERE NAME = " + bookName + ";";
    std::vector<Book> requestedBooks;

    auto answer = db->bookTableQuery(sql);

    for (auto bookParams: answer) {
        Book bookInstance;
        requestedBooks.push_back(bookInstance);
    }

    if (requestedBooks.empty()) {
        throw BookNotFound(bookName);
    }

    return requestedBooks;
}

std::vector<Book> SearchSystem::searchByAuthor(std::string &authorName) {
    std::vector<Book> requestedBooks;
    std::string sql = "SELECT * FROM BOOKS WHERE AUTHOR = " + authorName + ";";
    auto answer = db->bookTableQuery(sql);

    for (auto bookParams: answer) {
        Book bookInstance;
        requestedBooks.push_back(bookInstance);
    }

    if (requestedBooks.empty()) {
        throw AuthorNotFound(authorName);
    }

    return requestedBooks;
}

std::vector<Book> SearchSystem::searchByGenre(std::string &genre) {
    std::vector<Book> requestedBooks;
    std::string sql = "SELECT * FROM BOOKS WHERE GENRE = " + genre + ";";
    auto answer = db->bookTableQuery(sql);

    for (auto bookParams: answer) {
        Book bookInstance;
        requestedBooks.push_back(bookInstance);
    }

    if (requestedBooks.empty()) {
        throw GenreNotFound(genre);
    }

    return requestedBooks;
}