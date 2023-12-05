#ifndef ELO_H
#define ELO_H

#include <compare>
#include <cmath>

const int E_CONST = 400;
const int K_CONST = 32;

class elo{
    private:
    int score;

    public:
    //constructors
    elo() = default;
    elo(int sVal): score{sVal}{};
    elo(const elo& other): score{other.getElo()}{};

    //accessors
    int getElo() const;

    //modifiers
    void setElo(int sVal);

    void win(const elo& other);
    void lose(const elo& other);

    //deconstructor
    ~elo() = default;

    //operator overloaders
    elo& operator=(const elo& rhs);

    auto operator==(const elo& rhs) const;
    auto operator<(const elo& rhs) const;
    auto operator>(const elo& rhs) const;
    auto operator<=(const elo& rhs) const;
    auto operator>=(const elo& rhs) const;

};

/**
 * ACCESSORS
*/
int elo::getElo() const{
    return score;
}

/**
 * MODIFIERS
*/
void elo::setElo(int sVal){
    score = sVal;
}

void elo::win(const elo& other){
    double eloDiff = (other.getElo() - score)/E_CONST;

    double eA = 1/(1 + pow(10, eloDiff)); //probability of win

    score = score + K_CONST*(1 - eA);
}

void elo::lose(const elo& other){
    double eloDiff = (other.getElo() - score)/E_CONST;

    double eA = 1/(1 + pow(10, eloDiff)); //probability of win

    score = score + K_CONST*(0 - eA);
}

/**
 * OPERATORS
*/
elo& elo::operator=(const elo& rhs){
    score = rhs.score;
}

auto elo::operator==(const elo& rhs) const{
    return (score == rhs.score);
}
auto elo::operator<(const elo& rhs) const{
    return (score < rhs.score);
}
auto elo::operator>(const elo& rhs) const{
    return (score > rhs.score);
}
auto elo::operator<=(const elo& rhs) const{
    return (score <= rhs.score);
}
auto elo::operator>=(const elo& rhs) const{
    return (score >= rhs.score);
}

#endif