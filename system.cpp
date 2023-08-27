#include "Users/Reader/Reader.h"
#include <iostream>
#include <limits>
#include "Users/UserType.h"
#include "Library/Library.h"
#include "Other/Menu.h"
#include "Users/Admin/Admin.h"
#include "Users/Author/Author.h"
#include "Users/password.h"
using namespace std;

void adminInterface() {
    Menu menu;
    Library lib;
    Admin* admin = lib.authSystem().adminLogIn();
    bool activeSession = true;
    while (activeSession) {
        int choose = menu.adminMenu();
        switch (choose) {
            case 1: // Check requests mail
                admin->requestsMail();
                break;
            case 2: //Searching
                menu.searchMenu(&lib);
                lib.searchSystem();
                break;
            case 3: //Administrate
                break;
            case 0:
                activeSession = false;
        }
    }
}

void readerInterface(int option) {
    Library lib;
    Menu menu;
    Reader* reader;
    switch (option) {
        case 1:
            reader = lib.authSystem().readerLogIn();
            break;
        case 2:
            reader = lib.authSystem().readerSignUp();
            break;
    }
    bool activeSession = true;
    while (activeSession) {
        int choose = menu.readerMenu();
        switch (choose) {
            case 1:
                //menu.searchMenu();
                lib.searchSystem();
            case 2:
                reader->fillCreditInfo();
            case 0:
                activeSession = false;
        }
    }
}

void authorInterface(int option) {
    Library lib;
    Menu menu;
    Author* author;
    switch (option) {
        case 1:
            author = lib.authSystem().authorLogIn();
            break;
        case 2:
            author = lib.authSystem().authorSignUp();
            break;
    }
    bool activeSession = true;
    while (activeSession) {
        int choose = menu.readerMenu();
        switch (choose) {
            case 1:
                //author->search();
            case 2:
                author->publish();
            case 0:
                activeSession = false;
        }
    }
}

int runner() {
    Menu().welcomeMenu(); //Choose the user type

    int userType;

    bool isCorrectChoice = false;
    do {
        cin >> userType;
        if (userType == 1 || userType == 0) {
            isCorrectChoice = true;
        } else {
            cout << "Incorrect value entered. Please try again." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!isCorrectChoice); //Checking the inserted value

    int option;
    if (static_cast<UserType>(userType) != ADMIN) {
        cout << "\t\t     1.Login" << endl;
        cout << "\t\t     2.Register" << endl;
        cin >> option;
    }

    switch (static_cast<UserType>(userType)){
        case ADMIN:
            adminInterface();
            break;
        case READER:
            readerInterface(option);
            break;
        case AUTHOR:
            authorInterface(option);
            break;
    }
    return 0;
}


int main(int argc, char const *argv[]) {
    runner();
    /* Password usage example
    string pass = "hash_this_password";
    Password hashed(pass);
    std::cout << hashed.calculate_hash() << std::endl;
    std::cout << "System reached the end of execution" << std::endl;
     */
    return 0;
}
