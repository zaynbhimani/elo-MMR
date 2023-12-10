#include <iostream>

#include "main.h"

using std::cout;
using std::endl;

int main(){
    
    pseudoVector<player> players;
        players.push_back(player("john", 1200));
        players.push_back(player("jack", 1450));
        players.push_back(player("jerry", 1040));
        players.push_back(player("jennifer", 980));
        players.push_back(player("janet", 1655));
        players.push_back(player("jamie", 1430));

    pseudoVector<match> matchList = matchmaker(players);

    for(auto& match : matchList){
        cout << "\nMatch" << endl;
        cout << match.player1.getName() << endl;
        cout << "  " << match.player1.getRating().getElo() << endl;

        cout << match.player2.getName() << endl;
        cout << "  " << match.player2.getRating().getElo() << endl;
    }

    return 0;
}