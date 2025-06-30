#include <string>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    double price;
    int loanIntervalDays;
    bool isLoaned;
public:
    Book(const std::string& isbn_,
         const std::string& title_,
         const std::string& author_,
         double price_,
         int loanIntervalDays_)
        : isbn(isbn_)
        , title(title_)
        , author(author_)
        , price(price_)
        , loanIntervalDays(loanIntervalDays_)
        , isLoaned(false)
    {}

    const std::string& getISBN() const { return isbn; }
    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    double getPrice() const { return price; }
    int getLoanIntervalDays() const { return loanIntervalDays; }
    bool getIsLoaned() const { return isLoaned; }

    void loan()   { if (!isLoaned) isLoaned = true; }
    void ret()    { if (isLoaned)  isLoaned = false; }
};

class Library {
private:
    std::vector<Book> books;
public:
    bool addBook(const Book& b) {
        auto it = std::find_if(books.begin(), books.end(),
            [&](const Book& x){ return x.getISBN() == b.getISBN(); });
        if (it != books.end()) return false;
        books.push_back(b);
        return true;
    }

    bool removeBook(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(),
            [&](const Book& x){ return x.getISBN() == isbn; });
        if (it == books.end()) return false;
        books.erase(it, books.end());
        return true;
    }

    Book* findBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
            [&](const Book& x){ return x.getISBN() == isbn; });
        return it != books.end() ? &(*it) : nullptr;
    }

    std::vector<Book> listBooks() const {
        return books;
    }

    bool loanBook(const std::string& isbn) {
        Book* b = findBook(isbn);
        if (!b || b->getIsLoaned()) return false;
        b->loan();
        return true;
    }

    bool returnBook(const std::string& isbn) {
        Book* b = findBook(isbn);
        if (!b || !b->getIsLoaned()) return false;
        b->ret();
        return true;
    }
};