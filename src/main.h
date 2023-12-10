#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "elo.h"
#include "player.h"
#include "pseudoList.h"

using namespace PSEUDOLIST;

struct match{
    player player1;
    player player2;

    match(player p1, player p2): player1{p1}, player2{p2}{};
};

pseudoList<match> matchmaker(pseudoList<player>& playerLobby){

    
}

#endif