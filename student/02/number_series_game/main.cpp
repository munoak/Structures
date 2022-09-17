#include <iostream>

using namespace std;

int main()
{
    int numbers {};
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;
    for(int i=1; i<= numbers; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
