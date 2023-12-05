#ifndef ELO_H
#define ELO_H

#include <compare>

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