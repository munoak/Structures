#include <iostream>
#include "book.hh"
#include "date.hh"

Book::Book(const std::string& title, const std::string& author): title(title), author(author)
{

}
void Book::print() const
{
    std::cout << title << " : " << author << std::endl;
    if(available)
        std::cout << "- available" << std::endl;
    else
    {
        std::cout << "- loaned: ";
        loan_date.print();
        std::cout << "- to be returend: ";
        due_date.print();
    }

}
void Book::loan(Date& date)
{
    if(available)
    {
        loan_date = date;
        due_date = loan_date;
        due_date.advance(28);
        available = false;
    }
    else
        std::cout << "Already loaned: cannot be loaned " << std::endl;
}
void Book::renew(){
if(available)
    std::cout << "Not loaned: cannot be renewed" << std::endl;
else
    due_date.advance(28);

}
void Book::give_back()
{
available = true;
}
