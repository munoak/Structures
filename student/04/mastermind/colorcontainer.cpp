#include "colorcontainer.hh"
#include<random>
#include <iostream>

ColorContainer::ColorContainer()
{

}

void ColorContainer::fill_series(int& seed)
{
    for (uint i= 0; i < SIZE; i++)
    {
        enum color {B =1,R =2 ,Y =3 ,G = 4,O =5,V =6};
        static std::uniform_int_distribution<int> distr(B, V);
        static std::default_random_engine gen(seed);
        entered_colors.push_back(distr(gen));
    }
}

std::string& ColorContainer::fill_list()
{
    std::cout << "Enter four colors (four letters without spaces): ";
    std::cin >> entered_colors;
    return entered_colors;
}
bool ColorContainer::check_colors(){
    std::string given_colors = "brygov";
        //for (char& c : entered_colors) {

            if (given_colors.find(entered_colors) != std::string::npos)
            {
                return true;
            }
        //}
        return false;
}

bool ColorContainer::check_length()
{
    return (entered_colors.length() == SIZE);
}
