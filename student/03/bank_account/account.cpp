#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit): owner(owner), has_credit(has_credit)
{
    Account::generate_iban();
}
void Account::set_credit_limit(int limit){
    if(this -> has_credit)
        credit_limit = limit;
    else
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
}
void Account::transfer_to(Account &Acc, double amount){
    if(((balance +credit_limit) - amount ) < 0){
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }
    else
    {
    this -> balance -=amount;
    Acc.balance += amount;
    std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance << " euros " << std::endl;
    }
}
void Account::save_money(double amount) {
    balance += amount;
}
void Account::take_money(double amount) {


    if (((this -> balance + credit_limit) - amount) < 0 )
       std::cout << "Cannot take money: balance underflow" << std::endl;
    else
    {
    balance -= amount;
    std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance << " euros " << std::endl;
    }
}
void Account::print() const
{
std::cout << owner << " : " << iban_ << " : " << balance << " euros" << std::endl;
}
// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
