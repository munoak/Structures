#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>
#include <string>
#include "date.hh"

using namespace std;

class Book
{
private:
    std::string title_;
    std::string author_;
    bool is_loaned;
    Date loaning_date;
    Date due_date;

public:
    Book();
    Book(const std::string& title, const std::string& author);
    void print();
    void loan(Date &date);
    void renew();
    void give_back();
};

#endif // BOOK_HH
