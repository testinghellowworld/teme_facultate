#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    std::string ISBN;
    std::string name;
    std::string author;
    double price;
    int loanInterval;
    Book(const std::string& isbn, const std::string& name, const std::string& author, double price, int loanInterval)
        : ISBN(isbn), name(name), author(author), price(price), loanInterval(loanInterval) {}
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    bool removeBookByISBN(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b){ return b.ISBN == isbn; });
        if(it != books.end()) {
            books.erase(it, books.end());
            return true;
        }
        return false;
    }
    Book* findBookByISBN(const std::string& isbn) {
        for(auto& b : books)
            if(b.ISBN == isbn)
                return &b;
        return nullptr;
    }
    void listBooks() const {
        for(const auto& b : books) {
            std::cout << "ISBN: " << b.ISBN
                      << "\nName: " << b.name
                      << "\nAuthor: " << b.author
                      << "\nPrice: " << b.price
                      << "\nLoan Interval: " << b.loanInterval << " days\n\n";
        }
    }
};

int main() {
    Library lib;
    lib.addBook(Book("978-3-16-148410-0","The Great Gatsby","F. Scott Fitzgerald",10.99,14));
    lib.addBook(Book("978-0-14-044913-6","Crime and Punishment","Fyodor Dostoevsky",12.50,21));
    lib.listBooks();
    std::string isbnToRemove = "978-3-16-148410-0";
    if(lib.removeBookByISBN(isbnToRemove)) {
        std::cout << "Removed book with ISBN: " << isbnToRemove << "\n\n";
    }
    lib.listBooks();
    return 0;
}