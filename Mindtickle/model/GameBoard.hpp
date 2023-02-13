//
//  GameBoard.hpp
//  Mindtickle
//
// This class is about game board. It has board size, game jumps and positions of all pieces.

#ifndef GameBoard_hpp
#define GameBoard_hpp

#include "GameJumps.hpp"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class GameBoard {
    int boardSize;
    vector<shared_ptr<GameJumps>> gameJumps;
    unordered_map<string, int> piecePositions;
    
public:
    GameBoard() {}
    GameBoard(int iBoardSize, vector<shared_ptr<GameJumps>> iGameJumps) {
        boardSize = iBoardSize;
        gameJumps = iGameJumps;
    }
    
    int getPositionForPlayerId(string iPlayerId) {
        if(piecePositions.find(iPlayerId) == piecePositions.end())
            return 0;
        return piecePositions[iPlayerId];
    }
    
    void setPositionForPlayerId(string iPlayerId, int iPosition) {
        piecePositions[iPlayerId] = iPosition;
    }
    
    int getSize() {
        return boardSize;
    }
    
    vector<shared_ptr<GameJumps>> getGameJumps() {
        return gameJumps;
    }
    
    unordered_map<string, int> getPiecePositions() {
        return piecePositions;
    }
};
#endif /* GameBoard_hpp */

/*
 - out of boound jumps or pieces. Invalidate them.
 - Negative board size is invalid.
 */
