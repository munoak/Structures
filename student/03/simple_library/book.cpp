#include <iostream>
#include "book.hh"
#include "date.hh"

Book::Book(const std::string& title, const std::string& author)
    : title(title), author(author), loan_date(Date()), due_date(Date())
{

}
void Book::print() const
{
    std::cout << title << " : " << author << std::endl;
    if(is_loaned)
    {
        std::cout << "- loaned: ";
        loan_date.print();
        std::cout << "- to be returend: ";
        due_date.print();
    }
    else std::cout << "- available" << std::endl;

}
void Book::loan(Date& date)
{
    if(is_loaned) std::cout << "Already loaned: cannot be loaned " << std::endl;
    else
    {
        loan_date = date;
        due_date = loan_date;
        due_date.advance(28);
        is_loaned = true;
    }

}
void Book::renew(){
if(is_loaned)
    due_date.advance(28);
else
    std::cout << "Not loaned: cannot be renewed" << std::endl;



}
void Book::give_back()
{
is_loaned = false;
}
