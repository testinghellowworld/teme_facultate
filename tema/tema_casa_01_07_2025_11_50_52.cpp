#include <iostream>
#include <string>
#include <vector>
#include <optional>

struct Book {
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    int borrowInterval; // in days
    bool borrowed = false;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    bool removeBook(const std::string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->isbn == isbn && !it->borrowed) {
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    std::optional<Book*> findBook(const std::string& isbn) {
        for (auto& book : books) {
            if (book.isbn == isbn) {
                return &book;
            }
        }
        return std::nullopt;
    }

    bool borrowBook(const std::string& isbn) {
        auto opt = findBook(isbn);
        if (opt && !(*opt).value()->borrowed) {
            (*opt).value()->borrowed = true;
            return true;
        }
        return false;
    }

    bool returnBook(const std::string& isbn) {
        auto opt = findBook(isbn);
        if (opt && (*opt).value()->borrowed) {
            (*opt).value()->borrowed = false;
            return true;
        }
        return false;
    }

    void listBooks() const {
        for (const auto& b : books) {
            std::cout << "ISBN: " << b.isbn << ", Name: " << b.name
                      << ", Author: " << b.author << ", Price: " << b.price
                      << ", Interval: " << b.borrowInterval << " days"
                      << (b.borrowed ? " [Borrowed]" : "") << std::endl;
        }
    }

private:
    std::vector<Book> books;
};

int main() {
    Library lib;
    // Example usage:
    Book b1{"978-0131103627", "The C Programming Language", "Kernighan & Ritchie", 59.99, 14};
    lib.addBook(b1);
    lib.listBooks();
    return 0;
}