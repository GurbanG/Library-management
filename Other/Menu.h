#ifndef LIBRARY_SYSTEM_MENU_H
#define LIBRARY_SYSTEM_MENU_H

#include <iostream>

using namespace std;

class Menu {
public:
    Menu() {}

    void welcomeMenu() {
        cout << "==================== Welcome to Library! ============================" << endl;
        cout << "============================ MENU ============================" << endl;
        cout << "\t\t     1.Enter as Reader" << endl;
        cout << "\t\t     2.Enter as Admin" << endl;
    }

    void searchMenu(Library* lib) {
        cout << "\t\t\tMENU" << endl;
        cout << "\t1.Search book by name" << endl;
        cout << "\t2.Search by author" << endl;
        cout << "\t3.Search by genre" << endl;
        int option;
        cin >> option;
        std::string book, author, genre;
        switch (option) {
            case 1:
                std::cout<< "Enter book name: ";
                cin >> book;
                lib->searchSystem().searchByName(book);
                break;
            case 2:
                std::cout<< "Enter author: ";
                cin >> author;
                lib->searchSystem().searchByAuthor(author);
                break;
            case 3:
                std::cout << "Enter genre: ";
                cin >> genre;
                lib->searchSystem().searchByGenre(genre);
                break;
        }
    }

    void chooseAction() {
        cout << "============================ MENU ============================" << endl;
        cout << "\t\t     1.Search for book" << endl;
        cout << "\t\t     2.Manage my Books" << endl;
    }

    int adminMenu() {
        cout << "============================ MENU ============================" << endl;
        cout << "\t\t     1.Mail" << endl;
        cout << "\t\t     2.Search Books" << endl;
        cout << "\t\t     3.Manage Users" << endl;
        cout << "\t\t     0.Exit" << endl;
        return 0;
    }

    int readerMenu() {
        cout << "============================ MENU ============================" << endl;
        cout << "\t\t     1.Search Books" << endl;
        cout << "\t\t     2.Fill credit info" << endl;
        cout << "\t\t     0.Exit" << endl;
        return 0;
    }

    int authorMenu() {
        cout << "============================ MENU ============================" << endl;
        cout << "\t\t     1.Search Books" << endl;
        cout << "\t\t     2.Manage Books" << endl;
        cout << "\t\t     0.Exit" << endl;
        return 0;
    }


};


#endif //LIBRARY_SYSTEM_MENU_H
