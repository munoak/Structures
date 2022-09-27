#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

const int full_scr=50,
          half_scr=25;

class Player
{
private:
    int points;
    std::string name;

public:
    Player(std::string const &name);
    std::string get_name() const;
    int get_points() const;
    void add_points (int points);
    bool has_won();
};
#endif // PLAYER_HH
