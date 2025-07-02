#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    std::string isbn;
    std::string title;
    std::string author;
    double price;
    int loanInterval;

    Book(const std::string& isbn,
         const std::string& title,
         const std::string& author,
         double price,
         int loanInterval)
        : isbn(isbn), title(title), author(author), price(price), loanInterval(loanInterval) {}
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    bool removeBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
            [&](const Book& b){ return b.isbn == isbn; });
        if(it != books.end()) {
            books.erase(it);
            return true;
        }
        return false;
    }
    Book* findBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
            [&](const Book& b){ return b.isbn == isbn; });
        return it != books.end() ? &(*it) : nullptr;
    }
    void listBooks() const {
        for(const auto& b : books) {
            std::cout << "ISBN: " << b.isbn
                      << ", Title: " << b.title
                      << ", Author: " << b.author
                      << ", Price: " << b.price
                      << ", Loan Interval: " << b.loanInterval
                      << " days\n";
        }
    }
};

int main() {
    Library lib;
    lib.addBook(Book("978-0131103627", "The C Programming Language", "Kernighan & Ritchie", 45.0, 14));
    lib.addBook(Book("978-0201633610", "Design Patterns", "Gamma et al.", 50.0, 30));

    std::cout << "All books:\n";
    lib.listBooks();

    std::cout << "\nRemoving ISBN 978-0131103627\n";
    if(lib.removeBook("978-0131103627")) {
        std::cout << "Removed successfully.\n";
    } else {
        std::cout << "Book not found.\n";
    }

    std::cout << "\nAll books after removal:\n";
    lib.listBooks();

    return 0;
}