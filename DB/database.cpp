#include <vector>
#include "DB/sqlite3.h"
#include "database.h"

DATABASE::DATABASE() {
    std::cout << "Connecting to Database..." << std::endl;
    dp_return_code = sqlite3_open("data.dp", &DB);
    if(dp_return_code) {
        std::cerr<< "Error: Could not open database" << std::endl;
        exit(0);
    }
    std::cout<< "Database Opened successfully" << std::endl;
    /*
     * Table to store books
     *
     */

    std::cout << "Verifying books table" << std::endl;
    std::string command = "CREATE TABLE IF NOT EXISTS "\
     "BOOKS("\
        "id INT PRIMARY KEY, "\
        "name TEXT, "\
        "author TEXT, "\
        "genre TEXT, "\
        "price REAL, "\
        "copies INT, "\
        "num_of_votes INT, "\
        "sum_of_votes INT"\
    ");";

    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table Books." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Books table verified" << std::endl;

    /*
     * Table to store USERS
     *
     */

    std::cout << "Verifying users table" << std::endl;
    command = "CREATE TABLE IF NOT EXISTS "\
     "USERS("\
        "id INT PRIMARY KEY, "\
        "name TEXT, "\
        "password TEXT"\
    ");";
    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table USERS." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Users table verified" << std::endl;

    /*
     * Table to store which user owns what book
     *
     * */
    std::cout << "Verifying book ownership table (OWNED)" << std::endl;
    command = "CREATE TABLE IF NOT EXISTS "\
     "OWNED("\
        "username INT, "\
        "book_id TEXT"\
    ");";
    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table OWNED." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Table owned verified successfully" << std::endl;

    /*
     * Table to store Authors
     *
     */

    std::cout << "Verifying authors table" << std::endl;
    command = "CREATE TABLE IF NOT EXISTS "\
     "AUTHORS("\
        "id INT PRIMARY KEY, "\
        "mail TEXT, "\
        "password TEXT"\
    ");";
    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table Authors." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Authors table verified" << std::endl;

    std::cout << "Verifying Admin table" << std::endl;
    command = "CREATE TABLE IF NOT EXISTS "\
     "ADMINS("\
        "id INT PRIMARY KEY, "\
        "mail TEXT, "\
        "password TEXT, "\
        "UNIQUE(id, mail, password)"\
    ");";
    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table Admins." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Admins table verified" << std::endl;

    command = "INSERT OR IGNORE INTO ADMINS(id, mail, password) VALUES(0, ADMIN, NIMDA);";

    sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    std::cout << "Verifying requests table" << std::endl;
    command = "CREATE TABLE IF NOT EXISTS "\
     "REQUESTS("\
        "id INT PRIMARY KEY, "\
        "author TEXT, "\
        "book TEXT, "\
        "type INT"\
    ");";   // type: 0 for add book, 1 for remove book
    dp_return_code = sqlite3_exec(DB, command.c_str(), nullptr, 0, &zErrMsg);

    if(dp_return_code) {
        //TODO throw error
        std::cerr<< "Something went wrong" << std::endl;
        std::cerr<< "Could not find or create table requests." << std::endl;
        std::cerr<< "Exiting! .." <<std::endl;
        exit(0);
    }
    std::cout << "Requests table verified" << std::endl;
}
DATABASE::~DATABASE(){
    sqlite3_close(DB);
    std::cout<< "Database is closed" << std::endl;
}
void DATABASE::execute(std::string command) {
    dp_return_code = sqlite3_exec(
        DB,
        command.c_str(),

        [](void *NotUsed, int argc, char **argv, char **azColName) {
            for(int i = 0; i<argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }
            printf("\n");
            return 0;
    },

    0,
    &zErrMsg
    );
    std::cout << "Executed command, return code = " << dp_return_code << std::endl;
}
void DATABASE::observe() {
    std::cout<< "Tables currently in the database: " << std::endl;
    std::string command = "SELECT * FROM sqlite_master where type='table';";
    execute(command);
}
void DATABASE::dropAll() {
    std::string command = "PRAGMA writable_schema = 1;"\
    " delete from sqlite_master where type in ('table', 'index', 'trigger');"\
    " PRAGMA writable_schema = 0;";
    execute(command);
    command = "VACUUM;";
    execute(command);
    std::cout<< "Dropped all tables from database" << std::endl;
    std::cout<< "Checking integrity" << std::endl;
    command = "PRAGMA INTEGRITY_CHECK;";
    execute(command);
}
std::vector<std::vector<std::string>> DATABASE::bookTableQuery(std::string sql) {
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt* stmt;
    dp_return_code = sqlite3_prepare_v2(DB,  sql.c_str(), -1, &stmt, NULL);

    if( dp_return_code != SQLITE_OK ){
        std::cerr << "SQL error: could not retrieve books list" << std::endl;
        return result;
    }
    std::cout << "Statement compiled successfully" << std::endl;
    std::cout << "Getting books list" << std::endl;

    auto x = sqlite3_step(stmt);
    while(x == SQLITE_ROW) {
        // int ID = sqlite3_column_bytes(stmt, 0);
        std::string name = (const char *)sqlite3_column_text(stmt, 1);
        std::string author = (const char *)sqlite3_column_text(stmt, 2);
        std::string genre = (const char *)sqlite3_column_text(stmt, 3);
        std::string price = (const char *)sqlite3_column_text(stmt,4);
        std::string copies = (const char *) sqlite3_column_text(stmt, 5);
        // number of votes
        std::string NOV = (const char *)sqlite3_column_text(stmt, 6);
        // sum of votes
        std::string SOV = (const char *)sqlite3_column_text(stmt, 7);
        result.push_back({
            name,
            author,
            genre,
            price,
            copies,
            NOV,
            SOV
        });
        x = sqlite3_step(stmt);
    }
    if (x != SQLITE_DONE) {
      std::cerr << "Error reading database" << std::endl;
      return result;
    }
   sqlite3_finalize(stmt);
   return result;
}
std::vector<std::vector<std::string>> DATABASE::userTableQuery(std::string sql) {
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt* stmt;
    dp_return_code = sqlite3_prepare_v2(DB,  sql.c_str(), -1, &stmt, NULL);

    if( dp_return_code != SQLITE_OK ){
        std::cerr << "SQL error: could not retrieve users list" << std::endl;
        return result;
    }
    std::cout << "Statement compiled successfully" << std::endl;
    std::cout << "Getting users list" << std::endl;

    auto x = sqlite3_step(stmt);
    while(x == SQLITE_ROW) {
        // int ID = sqlite3_column_bytes(stmt, 0);
        std::string name = (const char *)sqlite3_column_text(stmt, 1);
        std::string password = (const char *)sqlite3_column_text(stmt, 2);
        result.push_back({
                                 name,
                                 password,
                         });
        x = sqlite3_step(stmt);
    }
    if (x != SQLITE_DONE) {
        std::cerr << "Error reading database" << std::endl;
        return result;
    }
    sqlite3_finalize(stmt);
    return result;
}
std::vector<std::vector<std::string>> DATABASE::adminTableQuery(std::string sql) {
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt* stmt;
    dp_return_code = sqlite3_prepare_v2(DB,  sql.c_str(), -1, &stmt, NULL);

    if( dp_return_code != SQLITE_OK ){
        std::cerr << "SQL error: could not retrieve admins list" << std::endl;
        return result;
    }
    std::cout << "Statement compiled successfully" << std::endl;
    std::cout << "Getting admins list" << std::endl;

    auto x = sqlite3_step(stmt);
    while(x == SQLITE_ROW) {
        // int ID = sqlite3_column_bytes(stmt, 0);
        std::string mail = (const char *)sqlite3_column_text(stmt, 1);
        std::string password = (const char *)sqlite3_column_text(stmt, 2);
        result.push_back({
                                 mail,
                                 password,
                         });
        x = sqlite3_step(stmt);
    }
    if (x != SQLITE_DONE) {
        std::cerr << "Error reading database" << std::endl;
        return result;
    }
    sqlite3_finalize(stmt);
    return result;
}

std::vector<std::vector<std::string>> DATABASE::authorTableQuery(std::string sql) {
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt* stmt;
    dp_return_code = sqlite3_prepare_v2(DB,  sql.c_str(), -1, &stmt, NULL);

    if( dp_return_code != SQLITE_OK ){
        std::cerr << "SQL error: could not retrieve authors list" << std::endl;
        return result;
    }
    std::cout << "Statement compiled successfully" << std::endl;
    std::cout << "Getting authors list" << std::endl;

    auto x = sqlite3_step(stmt);
    while(x == SQLITE_ROW) {
        // int ID = sqlite3_column_bytes(stmt, 0);
        std::string mail = (const char *)sqlite3_column_text(stmt, 1);
        std::string password = (const char *)sqlite3_column_text(stmt, 2);
        result.push_back({
                                 mail,
                                 password,
                         });
        x = sqlite3_step(stmt);
    }
    if (x != SQLITE_DONE) {
        std::cerr << "Error reading database" << std::endl;
        return result;
    }
    sqlite3_finalize(stmt);
    return result;
}

std::vector<std::vector<std::string>> DATABASE::requestsTableQuery(std::string sql){
    std::vector<std::vector<std::string>> result;
    sqlite3_stmt* stmt;
    dp_return_code = sqlite3_prepare_v2(DB,  sql.c_str(), -1, &stmt, NULL);

    if( dp_return_code != SQLITE_OK ){
        std::cerr << "SQL error: could not retrieve requests list" << std::endl;
        return result;
    }
    std::cout << "Statement compiled successfully" << std::endl;
    std::cout << "Getting requests list" << std::endl;

    /*
     command = "CREATE TABLE IF NOT EXISTS "\
     "REQUESTS("\
        "id INT PRIMARY KEY, "\
        "author TEXT, "\
        "book TEXT, "\
        "type INT"\
    ");";

     */

    auto x = sqlite3_step(stmt);
    while(x == SQLITE_ROW) {
        // int ID = sqlite3_column_bytes(stmt, 0);
        std::string author = (const char *)sqlite3_column_text(stmt, 1);
        std::string book = (const char *)sqlite3_column_text(stmt, 2);
        std::string type = (const char *) sqlite3_column_text(stmt, 3);
        result.push_back({
                                 author,
                                 book,
                                 type
                         });
        x = sqlite3_step(stmt);
    }
    if (x != SQLITE_DONE) {
        std::cerr << "Error reading database" << std::endl;
        return result;
    }
    sqlite3_finalize(stmt);
    return result;
}