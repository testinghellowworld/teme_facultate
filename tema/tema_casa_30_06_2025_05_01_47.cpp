#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    string isbn;
    string title;
    string author;
    double price;
    int loanInterval; // in days
    bool isLoaned;

    Book(const string& isbn, const string& title, const string& author, double price, int loanInterval)
        : isbn(isbn), title(title), author(author), price(price), loanInterval(loanInterval), isLoaned(false) {}
};

class Library {
    vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    bool removeBook(const string& isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b){ return b.isbn == isbn; });
        if(it != books.end()) {
            books.erase(it);
            return true;
        }
        return false;
    }

    Book* findBook(const string& isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b){ return b.isbn == isbn; });
        return it != books.end() ? &*it : nullptr;
    }

    vector<Book> listAll() const {
        return books;
    }

    bool loanBook(const string& isbn) {
        Book* b = findBook(isbn);
        if(b && !b->isLoaned) {
            b->isLoaned = true;
            return true;
        }
        return false;
    }

    bool returnBook(const string& isbn) {
        Book* b = findBook(isbn);
        if(b && b->isLoaned) {
            b->isLoaned = false;
            return true;
        }
        return false;
    }
};

int main() {
    Library lib;
    int choice;
    do {
        cout << "\n1. Add Book\n2. Remove Book\n3. List Books\n4. Loan Book\n5. Return Book\n0. Exit\nChoice: ";
        cin >> choice;
        if(choice == 1) {
            string isbn, title, author;
            double price;
            int interval;
            cout << "ISBN: "; cin >> isbn;
            cin.ignore();
            cout << "Title: "; getline(cin, title);
            cout << "Author: "; getline(cin, author);
            cout << "Price: "; cin >> price;
            cout << "Loan Interval (days): "; cin >> interval;
            lib.addBook(Book(isbn, title, author, price, interval));
        } else if(choice == 2) {
            string isbn;
            cout << "ISBN to remove: "; cin >> isbn;
            cout << (lib.removeBook(isbn) ? "Removed\n" : "Not found\n");
        } else if(choice == 3) {
            auto all = lib.listAll();
            for(const auto& b : all) {
                cout << "ISBN: " << b.isbn << ", Title: " << b.title
                     << ", Author: " << b.author << ", Price: " << b.price
                     << ", Interval: " << b.loanInterval
                     << ", Loaned: " << (b.isLoaned ? "Yes" : "No") << "\n";
            }
        } else if(choice == 4) {
            string isbn;
            cout << "ISBN to loan: "; cin >> isbn;
            cout << (lib.loanBook(isbn) ? "Loaned\n" : "Cannot loan\n");
        } else if(choice == 5) {
            string isbn;
            cout << "ISBN to return: "; cin >> isbn;
            cout << (lib.returnBook(isbn) ? "Returned\n" : "Cannot return\n");
        }
    } while(choice != 0);
    return 0;
}