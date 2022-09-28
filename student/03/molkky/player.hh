#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

#include <string>

const int MAX_SCORE=50,
          HALFWAY_SCORE=25;

class Player
{
public:
    Player(std::string const &name);
    std::string get_name() const;
    int get_points() const;
    void add_points (int points);
    bool has_won();

private:
    int points_;
    std::string name_;
};

#endif // PLAYER_HH
