#pragma once
#include <exception>
#include <string>


using namespace std;


class BaseException : public exception {
public:
    BaseException() {

    }

    virtual std::string what() {
        return message;
    }

private:
    std::string message = "Some error";
};


class BookNotFound : public BaseException {
public:
    BookNotFound(std::string name) : BaseException() {
        message = "The " + name + " wasn't found in library!";
    }

    std::string what() {
        return message;
    }

private:
    std::string message;
};


class AuthorNotFound : public BaseException {
public:
    AuthorNotFound(std::string author) : BaseException() {
        message = author +" wasn't found in library!";
    }

    std::string what() {
        return message;
    }

private:
    std::string message;
};

class AdminNotFound : public BaseException {
public:
    AdminNotFound(std::string mail) : BaseException() {
        message = mail +" wasn't found in library!";
    }

    std::string what() {
        return message;
    }

private:
    std::string message;
};

class GenreNotFound : public BaseException {
public:
    GenreNotFound(std::string genre) : BaseException() {
        message = "There is no any book that relates to " + genre+".";
    }

    std::string what() {
        return message;
    }

private:
    std::string message;
};

class TakenMailError : public exception {
public:
    TakenMailError() {}

    std::string what() {
        return message;
    }
private:
    std::string message = "This mail has already taken!";
};

class WrongPasswordError : public exception {
public:
    WrongPasswordError() {}

    std::string what() {
        return message;
    }
private:
    std::string message = "Wrong password!";
};

class NotExistingProfileError : public exception {
public:
    NotExistingProfileError() {}

    std::string what() {
        return message;
    }
private:
    std::string message = "Profile with specified mail was not found!";
};


class UnsupportedMailError : public exception {
public:
    UnsupportedMailError() {}

    std::string what() {
        return message;
    }
private:
    std::string message = "System not supports given mail!";
};