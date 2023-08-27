#include "Admin.h"

using namespace std;

Admin::Admin(Library &lib) {
    this->library = &lib;
}
void Admin::requestsMail() {
    //todo: get requests from database
    std::vector<std::vector<std::string>> requests = library->requestSystem().showRequests();
    for (auto request: requests) {
        std::cout << "Accept or Deny (0/1)" << std::endl;
        int option;
        cin >> option;
        switch (option) {
            case 0:
                switch (stoi(request[2])) {
                    case RequestSystem::PUBLISH:
                        this->addBook(request.book);
                    case RequestSystem::DELETE:
                        this->deleteBook(requests.book);
                }
                break;
            case 1:
                continue;
        }
    }
}

void Admin::addBook(Book &book) {
    this->library->managingSystem().addBook(book);
}

void Admin::deleteBook(Book &book) {
    this->library->managingSystem().deleteBook(book);
}

void Admin::deleteUser(Reader &reader) {
    this->library->managingSystem().deleteUser(reader);
}