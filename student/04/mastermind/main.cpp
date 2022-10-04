/* Mastermind
 *
 * Desc:
 *   This program implements a Mastermind game. First a secret series of
 * four colors is either given or drawn. The series can have several
 * identical colors, but none of the four positions can be empty.
 * The user tries to guess which colors the secret series has and in which
 * order they occur there. For this purpose, the user gives their own
 * series of four colors, and the program tells how many colors in the
 * guess was totally correct (correct color in correct position) and how
 * many of them were correct in color (but incorrect in position). After
 * that the user guesses again and so on.
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn colors, or with user-given ones. (The latter way is not
 * very sensible, but it is useful in testing purposes.) In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input four colors (the first
 * letters of the colors, i.e. a string consisting of four characters).
 *   On each round, the user is asked for a new guess. The player wins if
 * all colors in the guess are totally correct. The player loses if they
 * have used the maximum number (10) of guesses without the right one.
 *   The program checks if the user-given colors are among accepted ones.
 * When the game ends, the program tells if the player won or lost.
 *
 * Program author
 * Name: Noman Akbar
 * Student number: 150596134
 * UserID: mknoak
 * E-Mail: noman.akbar@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */
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
//const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;
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





// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
void start_game(ColorContainer sec_series, ColorContainer user_given_series){
    bool accepted = false;
    int cm {};
    int tm {};
    for(uint i=1 ;not accepted && i<=GUESS_MAX; i++ )
    {

    std::vector<std::string> retain_colors;
    std::cout << "ROW> ";
    user_given_series.fill_list();
    if (not (user_given_series.get_series() == "q" || user_given_series.get_series() == "Q"))
     {
        if(user_given_series.check_length())
        {
            if(user_given_series.check_colors())
            {
                cm= correct_match(sec_series, user_given_series);
                if(cm==4)
                {
                accepted = true;
                }
                else{
                std::string x = "";
                std::string user_input= user_given_series.get_series();
                for (int i=0; i<(int)user_input.size();i++)
                  {
                    x += toupper(user_input.at(i));
                    x += " ";
                  }
                retain_colors.push_back("| "+x+"| "+std::to_string(cm)+" | "+std::to_string(tm)+" |");
                std::cout<< "==================="<<std::endl;
                for(int i=0; i< (int)retain_colors.size(); i++)

                {
                   std::cout << retain_colors.at(i) << std::endl;
                }
                std::cout<< "==================="<<std::endl;
                }
            }
            else {std::cout << "Unknown color"<< std::endl;}
        }
     else {std::cout << "Wrong size"<< std::endl;}

    }
    else
    {
        abort();
    }
    }
    if (accepted)
      {
        std::cout << "You won: Congratulations!"<<std::endl;
      }
    else
        std::cout << "You lost: Maximum number of guesses done"<<std::endl;
}

int total_match(ColorContainer sec_series, ColorContainer user_given_series)
{
    int tm = 0;
    std::string game_clr = user_given_series.get_series();
    std::string ref_clr = sec_series.get_series();
    for (int i=0; i < 4 ;i++)
    {
        for (int j=0; j < 4 ; j++ )
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
