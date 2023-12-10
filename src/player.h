#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "elo.h"

using std::string;

const int START_ELO = 1200;

class player{
    private:
    string name;
    elo rating;

    public:
    //constructors
    player(string nm): name{nm}, rating{elo(START_ELO)}{};
    player(string nm, int sc): name{nm}, rating{elo(sc)}{};
    player(string nm, elo e1): name{nm}, rating{e1}{};

    player(const player& other): name{other.getName()}, rating{other.getRating()}{};

    //accessors
    string getName() const;
    elo getRating() const;

    //modifiers
    void setName(string nm);
    void setRating(int sc);
    void setRating(elo e1);

    //deconstructor
    ~player() = default;
};

#endif