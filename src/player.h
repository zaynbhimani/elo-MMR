#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "elo.h"

using std::string;

class player{
    private:
    string name;
    elo rating;
    int START_ELO = 1200;

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

/**
 * ACCESSORS
*/
string player::getName() const{
    return name;
}

elo player::getRating() const{
    return rating;
}

/**
 * MODIFIERS
*/
void player::setName(string nm){
    name = nm;
}

void player::setRating(int sc){
    rating = elo(sc);
}

void player::setRating(elo e1){
    rating = e1;
}


#endif