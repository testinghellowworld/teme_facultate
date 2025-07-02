#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    double price;
    std::pair<int,int> loanInterval; // days interval
    Book(const std::string &i, const std::string &t, const std::string &a, double p, const std::pair<int,int> &li)
        : isbn(i), title(t), author(a), price(p), loanInterval(li) {}
};

class Library {
    std::vector<Book> books;
public:
    void addBook(const Book &b) { books.push_back(b); }
    bool removeBook(const std::string &isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book &b){ return b.isbn == isbn; });
        if (it == books.end()) return false;
        books.erase(it, books.end());
        return true;
    }
    Book* findBook(const std::string &isbn) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book &b){ return b.isbn == isbn; });
        return it != books.end() ? &*it : nullptr;
    }
    void listBooks() const {
        for (const auto &b : books) {
            std::cout << "ISBN: " << b.isbn
                      << " Title: " << b.title
                      << " Author: " << b.author
                      << " Price: " << b.price
                      << " Loan Interval: [" << b.loanInterval.first << "," << b.loanInterval.second << "]\n";
        }
    }
};