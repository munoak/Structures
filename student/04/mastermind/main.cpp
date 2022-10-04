// TODO: Include your header file of the class describing a series of four colors
#include "colorcontainer.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

int total_match(ColorContainer, ColorContainer);
int correct_match(ColorContainer, ColorContainer);


using namespace std;


const unsigned int GUESS_MAX = 10; // Not in use, yet
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;
bool input_validated = false;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";


// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.
void get_input(ColorContainer& sec_series)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        sec_series.fill_series_randomly(seed); // Fill color series randomly based on the seed value
        input_validated = true;
    }
    else if(input_str == "L" or input_str == "l")
    {
        if(sec_series.fill_series_manually())
            {
               input_validated = true;
            }
    }
    else{
        cout << "Bad input" << endl;
        get_input(sec_series);
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}



// Prints all color series.
// (Not called in the template code.)
void print_all(std::vector<std::string> retain_colors)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    for(auto c=0; retain_colors.size(); c++)

    {
       std::cout << retain_colors[c] << std::endl;
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
void start_game(ColorContainer sec_series, ColorContainer user_given_series){
    bool accepted = false;
    uint i = 0;
    int cm {};
    int tm {};
    while(not accepted && i <= GUESS_MAX)
    {
        std::vector<std::string> retain_colors;

    std::cout << "ROW> ";
    user_given_series.fill_list();
    if (user_given_series.get_series() == "q" || user_given_series.get_series() == "Q")
          {
          abort();
          }
    else if(user_given_series.check_length())
        {
            if(user_given_series.check_colors())
            {
                cm= correct_match(sec_series, user_given_series);
                if(cm==4)
                {
                accepted = true;
                }
                std::string x = "";
                std::string b= user_given_series.get_series();
                for (int i=0; i<(int)b.size();i++)
                  {
                    x += toupper(b.at(i));
                    x += " ";
                  }
                retain_colors.push_back("| "+x+"| "+std::to_string(cm)+" | "+std::to_string(tm)+" |");
                print_all(retain_colors);
            }
            else {std::cout << "Unknown color"<< std::endl;}
        }
     else {std::cout << "Wrong size"<< std::endl;}

    }
    if(accepted)
    {
        cout << "colors matched";
    }
}
int total_match(ColorContainer sec_series, ColorContainer user_given_series)
{
    int tm = 0;
    std::string game_clr = user_given_series.get_series();
    std::string ref_clr = sec_series.get_series();
    for (int i=0; i < (int) SIZE ;i++)
    {
        for (int j=0; j < (int)SIZE ; j++ )
          {
            if(game_clr.at(i) == ref_clr.at(j))
              {
                ref_clr[j]='x';
                tm++;
                break;
              }
          }
    }

    return tm;
}
int correct_match(ColorContainer sec_series, ColorContainer user_given_series)
{
    int cm = 0;
    std::string a= sec_series.get_series();
    std::string b= user_given_series.get_series();
    for(int i=0; i < 4 ; i++){
       if(a.at(i) == b.at(i)){
                cm++;
                }
        }

    return cm;
}
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    ColorContainer sec_series {"rrrr"};
    //sec_series.set_sec_series()
    get_input(sec_series);
    ColorContainer user_given_series {"oooo"};
    if(input_validated){
            start_game(sec_series, user_given_series);
    }

    return 0;
}
