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
    elo(const elo& other);

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

#endif