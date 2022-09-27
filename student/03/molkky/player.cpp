#include "player.hh"

int half_pts =25;
int full_pts = 50;

Player::Player (std::string const &name): name(name), score(0)
{

}

std::string Player::get_name() const
{
    return name;
}

int Player::get_points() const
{
    return score;
}

void Player::add_points(int score)
{
    score += score;
        if(score > full_pts)
        {
            score= half_pts;
        }
}

bool Player::has_won()
{
    return score == full_pts;
}
