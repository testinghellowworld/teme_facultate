#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    double price;
    int borrowIntervalDays;
    bool isBorrowed = false;
};

class Library {
public:
    bool addBook(const Book& book) {
        if (std::any_of(books.begin(), books.end(), [&](const Book& b){ return b.isbn == book.isbn; }))
            return false;
        books.push_back(book);
        return true;
    }

    bool removeBook(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b){ return b.isbn == isbn; });
        if (it == books.end()) return false;
        books.erase(it, books.end());
        return true;
    }

    Book* findBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b){ return b.isbn == isbn; });
        return it != books.end() ? &*it : nullptr;
    }

    bool lendBook(const std::string& isbn) {
        Book* b = findBook(isbn);
        if (!b || b->isBorrowed) return false;
        b->isBorrowed = true;
        return true;
    }

    bool returnBook(const std::string& isbn) {
        Book* b = findBook(isbn);
        if (!b || !b->isBorrowed) return false;
        b->isBorrowed = false;
        return true;
    }

    void listBooks() const {
        for (const auto& b : books) {
            std::cout << "ISBN: " << b.isbn
                      << ", Title: " << b.title
                      << ", Author: " << b.author
                      << ", Price: " << b.price
                      << ", Borrow Interval: " << b.borrowIntervalDays << " days"
                      << ", Status: " << (b.isBorrowed ? "Borrowed" : "Available")
                      << std::endl;
        }
    }

private:
    std::vector<Book> books;
};