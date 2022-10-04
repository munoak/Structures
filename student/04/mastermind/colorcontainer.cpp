#include "colorcontainer.hh"
#include<random>
#include <iostream>


ColorContainer::ColorContainer(std::string col): entered_colors{col}
{

}

void ColorContainer::fill_series_randomly(int & seed)
{

        std::vector<char> color {'b', 'r', 'y', 'g', 'o', 'v'};
        static std::uniform_int_distribution<int> distr(b, v);
        static std::default_random_engine gen(seed);
        for (uint i= 0; i < SIZE; i++)
        {
            int d =distr(gen);
            entered_colors.push_back(color.at(d));
        }

}

void ColorContainer::fill_list()
{
    std::cin >> entered_colors;
}

bool ColorContainer::fill_series_manually()
{
    bool accepted = false;
    while(not accepted)
    {
    std::cout << "Enter four colors (four letters without spaces): ";
    fill_list();
    if(not check_length())
        {
            std::cout << "Wrong size"<< std::endl;
        }
    else
        {
             if(not check_colors())
                {
                    std::cout << "Unknown color"<< std::endl;
                }
             else
             {
                 accepted = true;
             }
        }

    }
    return true;
}
bool ColorContainer::check_colors(){
    std::string given_colors = "brygov";
    int i=0;
        for (char c : entered_colors)
        {

            for(char d: given_colors)
            {
            if(c==d)
                 i++;
            }

        }
        return i==SIZE;

}

bool ColorContainer::check_length()
{
    return (entered_colors.length() == SIZE);
}


std::string ColorContainer::get_series()
{
    return entered_colors;
}


ColorContainer::~ColorContainer()
{

}
