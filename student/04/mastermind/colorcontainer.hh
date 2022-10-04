#ifndef COLORCONTAINER_HH
#define COLORCONTAINER_HH
#include <vector>
#include<string>

// Number of colors in a series
const unsigned int SIZE = 4;
enum color {b,r,y,g,o,v};

class ColorContainer
{
public:
    ColorContainer(std::string col = "none");
    void fill_series_randomly(int&);
    void fill_list();
    bool fill_series_manually();
    bool check_colors();
    bool check_length();
    std::string get_series();
    ~ColorContainer();



private:
    //bool is_guessed;
    std::string entered_colors {};
    std::vector<std::string> colors_retainer;
};

#endif // COLORCONTAINER_HH
