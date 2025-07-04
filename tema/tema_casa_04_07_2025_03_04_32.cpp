#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Book {
public:
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    int loanIntervalDays;

    Book(const std::string& isbn, const std::string& name, const std::string& author, double price, int loanIntervalDays)
        : isbn(isbn), name(name), author(author), price(price), loanIntervalDays(loanIntervalDays) {}
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    bool removeBookByISBN(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b){ return b.isbn == isbn; });
        if (it != books.end()) {
            books.erase(it, books.end());
            return true;
        }
        return false;
    }

    Book* findBookByISBN(const std::string& isbn) {
        for (auto& b : books) {
            if (b.isbn == isbn) return &b;
        }
        return nullptr;
    }

    std::vector<Book> listBooks() const {
        return books;
    }
};