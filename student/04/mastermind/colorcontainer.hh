#ifndef COLORCONTAINER_H
#define COLORCONTAINER_H
#include <vector>
#include<string>

// Number of colors in a series
const unsigned int SIZE = 4;

//struct color {
//    int value_;
//    colorinuse given_series;
//    bool is_guessed;

//};

class ColorContainer
{
public:
    ColorContainer();
    void fill_series(int&);
    std::string& fill_list();
    bool check_colors();
    bool check_length();
    //enum colorinuse {B, R, Y, G, O, V};

private:
    std:: string entered_colors = "";
    std::vector<std::string> colors_;
};

#endif // COLORCONTAINER_H
