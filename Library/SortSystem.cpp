#include "SortSystem.h"

SortSystem::SortSystem(DATABASE *db) {
    this->db = db;
}

void SortSystem::sortByName() {
    std::string sql = "SELECT * FROM BOOKS ORDER BY NAME ASC";
    std::vector<std::vector<std::string>> answer = db->bookTableQuery(sql);
    std::cout << "Available books in alphabetical order: " << std::endl;
    for (auto book: answer) {
        for (auto j: book) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
};

void SortSystem::sortByGenre() {
    std::string sql = "SELECT * FROM BOOKS ORDER BY GENRE ASC";
    std::vector<std::vector<std::string>> answer = db->bookTableQuery(sql);
    std::cout << "Available books ordered by genres: " << std::endl;
    for (auto book: answer) {
        for (auto j: book) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void SortSystem::sortByPopularity() {
    std::string sql = "SELECT * FROM BOOKS ORDER BY RATING ASC";
    std::vector<std::vector<std::string>> answer = db->bookTableQuery(sql);
    std::cout << "Available books ordered by rating: " << std::endl;
    for (auto book: answer) {
        for (auto j: book) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
};
