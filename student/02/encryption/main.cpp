#include <iostream>
#include<string>


void check_key(std::string key);
void letter_case_check(std::string key);
void check_letters(std::string key);
std::string encrypt_msg(std::string message, std::string key);

std::string encrypt_msg(std::string message, std::string key)
{
    std::string encryted_msg ("");
    for (uint i =0; i < message.length(); i++)
    {
        int a = (int) message.at(i) - (int) 'a';
        message.at(i) = key[a];
        encryted_msg += message.at(i);
    }
    return encryted_msg;
}

void check_letters(std::string key)
{
    for(int i =97; i <122; i++)
    {

        if(key.find(i) == std::string::npos){
            std::cout << "Error! The encryption key must contain all alphabets a-z." << std::endl;
            exit(1);}
    }

}

void letter_case_check(std::string key)
{
    for(auto i: key)
    {
        if(i< 97 || i>122){
            std::cout << "Error! The encryption key must contain only lower case characters." << std::endl;
        exit(1);}
    }

}

void check_key(std::string key)
{
        if(key.length() < 26){
            std::cout << "Error! The encryption key must contain 26 characters." << std::endl;
            exit(1);
        }
}
int main()
{
    std::string key ("");
    std::string message ("");

    std::cout << "Enter the Encryption key: ";
    std::cin >> key;
    check_key(key);
    letter_case_check(key);
    check_letters(key);
    std::cout << "Enter the Encryption message: ";
    std::cin >> message;

    std::cout << "Encrypted text: " << encrypt_msg(message, key)<< std::endl;

    return 0;
}
