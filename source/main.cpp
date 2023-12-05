#include "main.h"

int main(){
    elo playerA;
    elo playerB;

    elo playerC(1500);
    elo playerD(1500);

    for(int i = 0; i<20; i++)
        battle(playerC, playerD);

    return 0;
}