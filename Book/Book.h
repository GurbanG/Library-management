#pragma once
#include <string>
#include <iostream>

class MakeRequest;

class Book{
protected:
    int num_of_votes;
    int sum_of_votes;
    std::string name;
    std::string genre;
    std::string author;
    int price;
    double rating; // calculated as average of given votes (sum of votes / number of votes)
public:

    class BookDTO{
        public:
            std::string name;
            std::string author;
            std::string genre;
            int price;
            double rating;
            int num_of_votes;
            int sum_of_votes;
            int id;

            BookDTO(std::string name, std::string author, std::string genre, int price, double rating,
                    int num_of_votes, int sum_of_votes);
    };

    Book(){}

    Book(std::string name, std::string genre, std::string author, int price);

    void buy();

    void rate(int vote);

    MakeRequest makeRequest();

    bool operator==(const Book& other) const;
};
