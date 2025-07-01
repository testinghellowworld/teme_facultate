#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    int loanPeriod; // zile
public:
    Book(const std::string& isbn, const std::string& name, const std::string& author, double price, int loanPeriod)
        : isbn(isbn), name(name), author(author), price(price), loanPeriod(loanPeriod) {}
    const std::string& getISBN() const { return isbn; }
    const std::string& getName() const { return name; }
    const std::string& getAuthor() const { return author; }
    double getPrice() const { return price; }
    int getLoanPeriod() const { return loanPeriod; }
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book) { books.push_back(book); }
    bool removeBookByISBN(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(),
                                 [&](const Book& b){ return b.getISBN() == isbn; });
        if (it != books.end()) {
            books.erase(it, books.end());
            return true;
        }
        return false;
    }
    Book* findBookByISBN(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
                               [&](const Book& b){ return b.getISBN() == isbn; });
        return it != books.end() ? &*it : nullptr;
    }
    std::vector<Book> listBooks() const { return books; }
};

#endif // LIBRARY_H