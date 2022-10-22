#include <iostream>
#include <string>
//bool is_palindrome(std::string str, int start, int end)
//{
//    if(start==end)
//        return true;
//    if(str[start]!=str[end])
//        return false;
//    if(start<end+1)
//    {
//        return is_palindrome(str, start+1, end-1);
//    }
//    return true;
//}

#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
//  int n= 0;
//  //int f = 0;
//  n = s.size();
//     if(n!=0)
//     {
//         return is_palindrome(s, 0 , n-1);
//     }
//     return false;
    int x=0;
    int n = s.size();
    if(n==0)
        return true;
    if(s.at(x) != s.at(n-1))
    {
        return false;
    }
    if(s.at(x) == s.back())
    {
        std::string r = s.substr(x+1, n-2);
        return palindrome_recursive(r);
    }
    return true;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
