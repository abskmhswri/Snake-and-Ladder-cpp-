//
//  main.cpp
//  Mindtickle
//
// Main class.

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "service/GameService.hpp"
using namespace::std;

int main(int argc, const char * argv[]) {
    vector<Player*> listOfPlayers;
//    Player *p1 = new HumanPlayer("John");
//    Player *p2 = new HumanPlayer("Jeff");
//    Player *p3 = new ComputerPlayer();
//    Player *p4 = new ComputerPlayer();
    Player *p5 = new ComputerPlayer();
    Player *p6 = new ComputerPlayer();
    
//    listOfPlayers.push_back(p1);
//    listOfPlayers.push_back(p2);
//    listOfPlayers.push_back(p3);
//    listOfPlayers.push_back(p4);
    listOfPlayers.push_back(p5);
    listOfPlayers.push_back(p6);
   
    GameService gameService(listOfPlayers, 10);
    
    if(!gameService.startGame()) {
        cout << "Error occured \n";
    }
    
    //gameService.replayGame();
    return 0;
}
