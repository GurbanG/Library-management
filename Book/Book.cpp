#include "Book.h"
#include "MakeRequest.h"

Book::Book(std::string name, std::string genre, std::string author, int price) {
    this->name = name;
    this->genre = genre;
    this->author = author;
    this->price = price;
    this->sum_of_votes = 0;
    this->num_of_votes = 0;
    this->rating = 0.0;
}

void Book::buy() {
    //TODO Should it be right here? We do not change anything after buying book. We need only price of the book
    //give necessary contact info...
    // when calling this function, the book is available and the user has payed the amount
    std::cout << "Book: " << name << " has been successfully purchased!" << std::endl;
}

void Book::rate(int vote) { // vote is between 0..5
    num_of_votes++;
    sum_of_votes += vote;
    rating = (double) sum_of_votes / num_of_votes;
    std::string request = this->makeRequest().update(RATING);
    //TODO Putting new information in DB
}

MakeRequest Book::makeRequest() {
    BookDTO book(name, author, genre, price, rating, num_of_votes, sum_of_votes);
    MakeRequest request(book);
    return request;
}

bool Book::operator==(const Book &other) const {
    return name == other.name && genre == other.genre && author == other.author && price == other.price
           && rating == other.rating && num_of_votes == other.num_of_votes && sum_of_votes == other.sum_of_votes;
}

Book::BookDTO::BookDTO(std::string name, std::string author, std::string genre, int price, double rating,
                       int num_of_votes, int sum_of_votes) {
    this->rating = rating;
    this->num_of_votes = num_of_votes;
    this->sum_of_votes = sum_of_votes;
    this->name = name;
    this->price = price;
    this->author = author;
    this->genre = genre;
}