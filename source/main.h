#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "elo.h"

void battle(elo& winner, elo& loser){
    std::cout << "  Winner's starting elo: " << winner.getElo() << "\n";
    std::cout << "  Loser's starting elo: " << loser.getElo() << "\n";

    winner.win(loser);
    loser.lose(winner);

    std::cout << "  Winner's new elo: " << winner.getElo() << "\n";
    std::cout << "  Loser's new elo: " << loser.getElo() << "\n";
}

#endif