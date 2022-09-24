#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    int SeedVal {};
    cout << "Enter a seed value: ";
    cin >> SeedVal;
    default_random_engine gen(42);
    uniform_int_distribution<int> distr(lower, upper);

    char PressBtn {};
    do{
        cout <<"\n Your drawn random number is "<<distr(gen) << std::endl;
        cout << "Press q to quit or any other key to continue: ";
        cin >> PressBtn;
    } while(PressBtn != 'q' );
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
