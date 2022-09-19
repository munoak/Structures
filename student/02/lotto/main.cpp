#include <iostream>
#include<math.h>

int probability(int t_numbers, int D_numbers);
long fact(int n);

using namespace std;

long fact(int num)
{
    long f = 1;
    for (int i=1; i<= num; i++)
        f *= i;
    return f;
}

int probability(int TNumbers, int DNumbers)
{
    long int combinations {};
   //combinations = (fact(TNumbers - DNumbers));
    combinations = fact(TNumbers) / (fact(TNumbers - DNumbers) * fact(DNumbers));

    return combinations;
}

int main()
{
    int TotalNumbers {1};
    cout << "Enter the total number of lottery balls: " ;
    cin >> TotalNumbers;

    int DrawnNumbers {1};
    cout << "Enter the number of drawn balls: ";
    cin >> DrawnNumbers;

    if(DrawnNumbers >0 && TotalNumbers >0)
    {
        if(DrawnNumbers > TotalNumbers)
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        else
            cout << "The probability of guessing all " << DrawnNumbers << " balls correctly is 1/" << probability(TotalNumbers, DrawnNumbers) << endl;


    }
    else
        cout << "The number of balls must be a positive number." << endl;


    return 0;

}
