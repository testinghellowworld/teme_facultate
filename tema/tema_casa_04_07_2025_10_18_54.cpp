#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Book {
    std::string isbn;
    std::string name;
    std::string author;
    double price;
    int loanDays;
};

class Library {
    std::vector<Book> books;
public:
    void addBook(const Book& book) { books.push_back(book); }
    bool removeBookByISBN(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(),
            [&](const Book& b) { return b.isbn == isbn; });
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
    void listBooks() const {
        for (const auto& b : books) {
            std::cout << "ISBN: " << b.isbn
                      << ", Name: " << b.name
                      << ", Author: " << b.author
                      << ", Price: " << b.price
                      << ", Loan Days: " << b.loanDays
                      << "\n";
        }
    }
};

int main() {
    Library lib;
    lib.addBook({"978-1234567890", "Example Book", "Author Name", 29.99, 14});
    lib.listBooks();
    return 0;
}