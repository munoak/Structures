#include "book.hh"

Book::Book()
{

}

Book::Book(const std::string &title, const std::string &author)
{
    title_ = title;
    author_ = author;
    is_loaned = false;
}

void Book::print()
{
    cout << title_ << " : " << author_ << '\n';
    if(is_loaned){
        cout << "- loaned: ";
        loaning_date.print();
        cout << "- to be returned: ";
        due_date.print();
    }
    else
        cout << "- available\n";
}

void Book::loan(Date &date)
{
    if(!is_loaned){
        Date due_date_ = date;
        due_date_.advance(28);
        loaning_date = date;
        due_date = due_date_;
        is_loaned = true;
    }
    else
        cout << "Already loaned: cannot be loaned\n";
}

void Book::renew()
{
    if(!is_loaned)
        cout << "Not loaned: cannot be renewed\n";
    else{
        due_date.advance(28);
    }

}

void Book::give_back()
{
    is_loaned = false;
}
