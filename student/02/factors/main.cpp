#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int number {0};
    vector <int> factors {};
    cout << "Enter a positive number: ";
    cin >> number;
    if(number <= 0)
        std::cout << "Only positive numbers accepted" << endl;
    else
    {
        for(int i=1; i <= number; i++)
        {
        if(number%i == 0)
            factors.push_back(i);
            }
        auto mid = factors.size()/2;
        if (factors.size() % 2 == 0)
        {
        cout << number << " = " << factors.at(mid-1) << " * " << factors.at(mid) << endl;
        }
        else
        {
        cout << number << " = " << factors.at(mid) << " * " << factors.at(mid) << endl;
        return 0;
        }
    }

}
