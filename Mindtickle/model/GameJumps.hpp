//
//  GameJumps.hpp
//  Mindtickle
//
// Snake and Ladder are groupes as Game Jumps. Ideally, all the classes should have separate files but they are kept here for readability and for quickly looking
// at the inheritance.

#ifndef GameJumps_hpp
#define GameJumps_hpp

#include <unordered_map>

using namespace std;

struct Jump {
    int startPosition;
    int endPosition;
    
    Jump(int iStartPosition, int iEndPosition) {
        startPosition = iStartPosition;
        endPosition = iEndPosition;
    }
};

class GameJumps {
public:
    virtual int processJumps(int iPosition) = 0;
};

class Snakes : public GameJumps {
    unordered_map<int, int> snakes;
    
public:
    void addSnake(Jump iJump) {
        snakes.insert({iJump.startPosition, iJump.endPosition});
    }
    
    int processJumps(int iFromPosition) override {
        if(snakes.find(iFromPosition) == snakes.end())
            return iFromPosition;
        return snakes[iFromPosition];
    }
};

class Ladders : public GameJumps {
    unordered_map<int, int> ladders;
    
public:
    void addLadder(Jump iJump) {
        ladders.insert({iJump.startPosition, iJump.endPosition});
    }
    
    int processJumps(int iFromPosition) override {
        if(ladders.find(iFromPosition) == ladders.end())
            return iFromPosition;
        return ladders[iFromPosition];
    }
};
#endif /* GameJumps_hpp */

/*
 - happy case
 - After validation checks are added, we will need to test all those.
 - Check if position of any jump causes the game to go in infinite loop.
 */
