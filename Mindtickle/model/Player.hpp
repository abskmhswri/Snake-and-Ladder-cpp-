//
//  Player.hpp
//  Mindtickle
//
// There are two types of players - Human and Computer. This can be extended to other player types as well. Ideally, all the classes should have separate files but they are kept here for readability and for quickly looking
// at the inheritance.

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include "../utils/Constants.hpp"

using namespace std;

class Player {
protected:
    string playerId;
    string playerName;
    bool isHuman;
    static int idCounter;
public:
    virtual ~Player() {} // This is required to make the Player polymorphic.
    string getPlayerId() {
        return  playerId;
    }
    
    string getPlayerName() {
        return playerName;
    }
};

int Player::idCounter = 1;

class HumanPlayer : public Player{
public:
    HumanPlayer(string iPlayerName) {
        playerId = Constants::humanPlayerIdPrefix + to_string(idCounter++);
        playerName = iPlayerName;
        isHuman = true;
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer() {
        playerId = Constants::computerPlayerIdPrefix + to_string(idCounter++);
        playerName = Constants::computerPlayerNamePrefix + " " + playerId;
        isHuman = false;
    }
};

#endif /* Player_hpp */

/*
 - Check Id assignment for Human and Computer player
 - Check if name is correctly assigned to Computer player with correct prefix
 */
