#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
class Player
{
private:
    std::string name= "";
    int score {};
public:
    Player(std::string const &name);
    std::string get_name() const;
    int get_points() const;
    void add_points(int score);
    bool has_won();

};
#endif // PLAYER_HH
