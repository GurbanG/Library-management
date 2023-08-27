#include "MakeRequest.h"

std::string MakeRequest::insert() {
    std::string sql = "INSERT INTO BOOKS (ID,NAME,AUTHOR,GENRE,PRICE,RATING,NUM_OF_VOTES,SUM_OF_VOTES) "  \
                "VALUES (" + std::to_string(book.id) + ", '" + book.name + "', '" + book.author + "',"
                                                                                                  "'" + book.genre +
                      "', " + std::to_string(book.price) + ", " + std::to_string(book.rating) + ", "
                                                                                                "" +
                      std::to_string(book.num_of_votes) + ", " + std::to_string(book.sum_of_votes) + " ); ";
    return sql;
}

std::string MakeRequest::remove() {
    std::string sql = "DELETE from BOOKS where ID=" + std::to_string(book.id) + "; " \
                        "SELECT * from BOOKS";
    return sql;
}

//Is it good enough considering SOLID principles?
std::string MakeRequest::update(Commands command) {
    std::string sql;
    switch (command) {
        case RATING:
            sql = "UPDATE BOOKS SET RATING = " + std::to_string(book.rating)
                  + ", NUM_OF_VOTES = " + std::to_string(book.num_of_votes)
                  + ", SUM_OF_VOTES = " + std::to_string(book.sum_of_votes) + " where ID=" + std::to_string(book.id) +
                  "; " \
                "SELECT * from BOOKS";
            break;
        case AUTHOR_CHANGE:
            sql = "UPDATE BOOKS SET AUTHOR = " + book.author + " where ID=" + std::to_string(book.id) + "; " \
                "SELECT * from BOOKS";
            break;
        case NAME_CHANGE:
            sql = "UPDATE BOOKS SET NAME = " + book.name + " where ID=" + std::to_string(book.id) + "; " \
                "SELECT * from BOOKS";
            break;
        case PRICE:
            sql = "UPDATE BOOKS SET PRICE = " + std::to_string(book.price) + " where ID=" + std::to_string(book.id) +
                  "; " \
                "SELECT * from BOOKS";
            break;
        case GENRE:
            sql = "UPDATE BOOKS SET GENRE = " + book.genre + " where ID=" + std::to_string(book.id) + "; " \
                "SELECT * from BOOKS";
            break;
    }
    return sql;
}