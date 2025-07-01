#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <optional>
#include <chrono>

struct DateInterval {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
};

struct Book {
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    DateInterval interval;
};

class Library {
public:
    void addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    std::optional<Book> findBook(const std::string& isbn) const;
    void listBooks() const;

private:
    std::vector<Book> books;
};

#endif // LIBRARY_H

// Implementation file: library.cpp
#include "library.h"
#include <iostream>

void Library::addBook(const Book& book) {
    books.push_back(book);
}

bool Library::removeBook(const std::string& isbn) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->isbn == isbn) {
            books.erase(it);
            return true;
        }
    }
    return false;
}

std::optional<Book> Library::findBook(const std::string& isbn) const {
    for (const auto& b : books) {
        if (b.isbn == isbn) return b;
    }
    return std::nullopt;
}

void Library::listBooks() const {
    for (const auto& b : books) {
        auto start = std::chrono::system_clock::to_time_t(b.interval.start);
        auto end = std::chrono::system_clock::to_time_t(b.interval.end);
        std::cout << "ISBN: " << b.isbn
                  << ", Name: " << b.name
                  << ", Author: " << b.author
                  << ", Price: " << b.price
                  << ", Interval: [" << std::ctime(&start)
                  << " - " << std::ctime(&end)
                  << "]" << std::endl;
    }
}