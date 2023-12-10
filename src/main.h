#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "player.h"
#include "pseudoVector.h"

using namespace pVec;

// match
struct match{
    player player1;
    player player2;

    match() = default;
    match(player p1, player p2): player1{p1}, player2{p2}{};

    match(const match& other): player1{other.player1}, player2{other.player2}{};
};

//sorting functions
int partition(pseudoVector<player>& A, int low, int high){

    int i = low;
    int j = high + 1;
    player P = A[low];

    while(true){
        //scanning from left to right
        while(A[++i].getRating()<P.getRating()){
            if(i == high)
                break;
        }
        //scanning from right to left
        while(A[--j].getRating()>P.getRating()){
            if(j == low)
                break;
        }
        //scanned entire range condition
        if(i>=j)
            break;

        swap(A[i], A[j]); //swap both sides of key
    }

    swap(A[low], A[j]);
    return j;
}

void quickSort(pseudoVector<player>& A, int low, int high){
    if(high <= low)
        return;
    
    int p{};
    p = partition(A, low, high);

    quickSort(A, low, p-1);
    quickSort(A, p+1, high);
}

//matchmaker function
    //fix: if odd number, one person doesn't get matched
pseudoVector<match> matchmaker(pseudoVector<player>& playerLobby){

    pseudoVector<match> matches;

    //TESTING
    for(auto& player : playerLobby){
        cout << player.getName() << endl;
        cout << "  " << player.getRating().getElo() << endl;
    }
    //TESTING

    quickSort(playerLobby, 0, playerLobby.getSize() - 1);

    //TESTING
    for(auto& player : playerLobby){
        cout << player.getName() << endl;
        cout << "  " << player.getRating().getElo() << endl;
    }
    //TESTING

    while(playerLobby.getSize() >= 2){
        player p1 = playerLobby.back();
            playerLobby.pop_back();
        player p2 = playerLobby.back();
            playerLobby.pop_back();

        matches.push_back(match(p1, p2));
    }
    

    return matches;
}

#endif