#ifndef BOOK_LIBRARY_H
#define BOOK_LIBRARY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

struct Book {
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    int loanIntervalDays;
    bool isLoaned = false;
};

class Library {
private:
    std::unordered_map<std::string, Book> books;
public:
    bool addBook(const Book& book) {
        auto [it, inserted] = books.emplace(book.isbn, book);
        return inserted;
    }
    bool removeBook(const std::string& isbn) {
        return books.erase(isbn) > 0;
    }
    std::optional<Book> findBook(const std::string& isbn) const {
        auto it = books.find(isbn);
        if (it != books.end()) return it->second;
        return std::nullopt;
    }
    std::vector<Book> listBooks() const {
        std::vector<Book> result;
        result.reserve(books.size());
        for (const auto& kv : books) result.push_back(kv.second);
        return result;
    }
    bool loanBook(const std::string& isbn) {
        auto it = books.find(isbn);
        if (it != books.end() && !it->second.isLoaned) {
            it->second.isLoaned = true;
            return true;
        }
        return false;
    }
    bool returnBook(const std::string& isbn) {
        auto it = books.find(isbn);
        if (it != books.end() && it->second.isLoaned) {
            it->second.isLoaned = false;
            return true;
        }
        return false;
    }
};

#endif // BOOK_LIBRARY_H