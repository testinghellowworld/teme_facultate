#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    double price;
    int borrowDays;
};

class Library {
private:
    std::vector<Book> books;

public:
    bool addBook(const Book& book) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b) {
            return b.isbn == book.isbn;
        });
        if (it != books.end())
            return false;
        books.push_back(book);
        return true;
    }

    bool removeBook(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b) {
            return b.isbn == isbn;
        });
        if (it == books.end())
            return false;
        books.erase(it, books.end());
        return true;
    }

    Book* findBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b) {
            return b.isbn == isbn;
        });
        if (it != books.end())
            return &(*it);
        return nullptr;
    }

    void listBooks() const {
        for (const auto& b : books) {
            std::cout << "ISBN: " << b.isbn
                      << ", Title: " << b.title
                      << ", Author: " << b.author
                      << ", Price: " << b.price
                      << ", Borrow Interval: " << b.borrowDays << " days\n";
        }
    }
};