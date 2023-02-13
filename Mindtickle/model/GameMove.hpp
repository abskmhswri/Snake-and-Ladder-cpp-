//
//  GameMove.hpp
//  Mindtickle
//
//This class stores the data about each move played in the game.

#ifndef GameMove_hpp
#define GameMove_hpp

#include "GameJumps.hpp"
#include "Player.hpp"

class GameMove {
    Player* movedPlayer;
    int diceRollValue;
    Jump jump;
    bool didWinGame;
    //add time stamp?
   
public:
    GameMove(Player* iMovedPlayer, int iDiceRollValue, Jump iJump, bool iDidWinGame = false) : jump(iJump) {
        movedPlayer = iMovedPlayer;
        diceRollValue = iDiceRollValue;
        didWinGame = iDidWinGame;
    }
    
    Player* getMovedPlayer() {
        return movedPlayer;
    }
    
    int getDiceRollValue() {
        return diceRollValue;
    }
    
    bool getDidWinGame() {
        return didWinGame;
    }
    
    Jump getJump() {
        return jump;
    }
};
#endif /* GameMove_hpp */
