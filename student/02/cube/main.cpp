#include <iostream>

using namespace std;

int main()
{
    int number {};
    int cube {};
    cout << "Enter a number: ";
    cin >> number;
    cube = number * number * number;
    if(cube > 0  && cube < (2e3))
        cout << "The cube of " << number << " is " << cube << endl;
    else
        cout << "Error! The cube of " << number << " is not " << cube << endl;

    return 0;
}
