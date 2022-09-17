#include <iostream>

using namespace std;

int main()
{
    double temp {};
    double celsius {};
    double frnht {};
    cout << "Enter a temperature: ";
    cin >> temp;
    frnht = (temp * 1.8) + 32;
    celsius = (temp -32) * 5/9;
    cout << temp << " degrees Celsius is " << frnht << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << celsius << " degrees Celsius" << endl;

    return 0;
}
