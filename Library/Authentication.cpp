#include "Authentication.h"
#include "Other/Exceptions.h"
#include "Users/Admin/Admin.h"

Authentication::Authentication(DATABASE *db) {
    this->db = db;
}

Reader *Authentication::readerLogIn() {
    auto credentials = this->getCredentials();
    std::string sql = "SELECT * FROM USERS;";
    std::vector<std::vector<std::string>> users = db->userTableQuery(sql);
    for (auto user: users) {
        // user[0] is name
        // user[1] is password
        //TODO check mail
        //TODO implement hashing
        if (user[0] == credentials[0] && user[1] == credentials[1]) {
            return new Reader(user[0], user[1]);
        }
    }
    throw NotExistingProfileError();
}

Reader *Authentication::readerSignUp() {
    auto credentials = this->getCredentials();
    ManagingSystem managingSystem(db);
    std::string sql = "SELECT * FROM USERS;";
    std::vector<std::vector<std::string>> users = db->userTableQuery(sql);
    for (auto user: users) {
        // user[0] is name
        // user[1] is password
        if (user[0] == credentials[0]) {
            throw TakenMailError(); // mail exists
        }
    }
    Reader *user = new Reader(credentials[0], credentials[1]);
    managingSystem.addUser(*user);
    return user;
}

Admin *Authentication::adminLogIn(Library& lib) {
    auto credentials = this->getCredentials();
    std::string sql = "SELECT * FROM ADMINS;";
    std::vector<std::vector<std::string>> admins = db->adminTableQuery(sql);
    for (auto admin: admins) {
        // admin[0] : mail
        // admin[1] : password
        if (admin[0] == credentials[0] && admin[1] == credentials[1]) {
            // Admin needs access to library
            return new Admin(lib);
        }
    }
    throw AdminNotFound(credentials[0]);
}

Author *Authentication::authorLogIn() {
    auto credentials = this->getCredentials();
    std::string sql = "SELECT * FROM AUTHORS;";
    std::vector<std::vector<std::string>> authors = db->authorTableQuery(sql);
    for (auto author: authors) {
        // author[0] : mail
        // author[1] : password
        if (author[0] == credentials[0] && author[1] == credentials[1]) {
            return new Author(credentials[0], credentials[1]);
        }
    }
    throw AuthorNotFound(credentials[0]);
}

Author *Authentication::authorSignUp() {
    auto credentials = this->getCredentials();
    std::string sql = "SELECT * FROM AUTHORS;";
    std::vector<std::vector<std::string>> authors = db->authorTableQuery(sql);
    for (auto author: authors) {
        // author[0] : mail
        // author[1] : password
        if (author[0] == credentials[0]) {
            //todo: create exception
            throw exception();
        }
    }
    // insert author to table
    sql = "INSERT INTO AUTHORS(mail, password) VALUES(" + credentials[0] + ", " + credentials[1] + ");";
    db->execute(sql);
    return new Author(credentials[0], credentials[1]);
}