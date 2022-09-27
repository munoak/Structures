#include "player.hh"

Player::Player(std::string const &name):
    points(0), name(name)
{


}

std::string Player::get_name() const
{
    return name;
}

int Player::get_points() const
{
    return points;
}

void Player::add_points(int points)
{
    points += points;
    if(points > full_scr)
    {
        points= half_scr;
    }
}

bool Player::has_won()
{
    return points== full_scr;
}
