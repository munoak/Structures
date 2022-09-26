#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"

class Book {
private:

    std::string title = "";
    std::string author = "";
    Date loan_date;
    Date due_date;
    bool available = true;

public:
    Book (const std::string& title, const std::string& author);
    void print();
    void loan(Date&);
    void renew();
    void give_back();
};

#endif // BOOK_HH
