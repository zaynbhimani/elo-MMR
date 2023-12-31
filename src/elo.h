#ifndef ELO_H
#define ELO_H

#include <compare>
#include <cmath>

class elo{
    private:
    int score = 0;
    int eVal = 400;
    int kVal = 32;

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

    //other functions
    double winChance(const elo& other);

    //deconstructor
    ~elo() = default;

    //operator overloaders
    elo& operator=(const elo& rhs);

    auto operator==(const elo& rhs) const;
    auto operator<(const elo& rhs) const;
    auto operator>(const elo& rhs) const;
    auto operator<=(const elo& rhs) const;
    auto operator>=(const elo& rhs) const;

    int operator-(const elo& rhs) const;
    int operator+(const elo& rhs) const;

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
    score = score + kVal*(1 - winChance(other));
}

void elo::lose(const elo& other){
    score = score + kVal*(0 - winChance(other));

    if(score < 0)
        score = 0;
}

/**
 * OTHER FUNCTIONS
*/
double elo::winChance(const elo& other){
    double eloDiff = (other.getElo() - score)/eVal;

    double eA = 1/(1 + pow(10, eloDiff)); //probability of win

    return eA;
}

/**
 * OPERATORS
*/
elo& elo::operator=(const elo& rhs){
    score = rhs.score;

    return *this;
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

int elo::operator-(const elo& rhs) const{
    return getElo() - rhs.getElo();
}
int elo::operator+(const elo& rhs) const{
    return getElo() + rhs.getElo();
}

#endif