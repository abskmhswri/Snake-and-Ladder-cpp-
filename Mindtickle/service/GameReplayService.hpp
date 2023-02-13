//
//  GameReplayService.hpp
//  Mindtickle
//
//This class stores all the moves made in the game and can replay them at any point.

#ifndef GameReplayService_hpp
#define GameReplayService_hpp

#include <iostream>
#include "../model/GameMove.hpp"
#include <vector>

using namespace std;

class GameReplayService {
    vector<GameMove> gameMoveLog;
    
public:
    void addGameMoveLog(GameMove iGameMove) {
        gameMoveLog.push_back(iGameMove);
    }
    
    void replayGame() {
        if(gameMoveLog.size() == 0)
            return;
        
        cout << " \n\n\n======= Showing Quick Game Replay ======= \n";
        cout << " All the players are at 0 \n";
        
        for(auto &it : gameMoveLog) {
            cout << "Player named: " << it.getMovedPlayer()->getPlayerName()
            << "  rolled dice. Value of dice: " << it.getDiceRollValue()
            << ".  Moved from position: " << it.getJump().startPosition
            << "  to position: " << it.getJump().endPosition << endl;
            
            if(it.getDidWinGame())
                cout << "Player named: " << it.getMovedPlayer()->getPlayerName() << " won in this move \n";
        }
    }
};
#endif /* GameReplayService_hpp */

/*
 - try to replay for empty gameMoveLog.
 - try happy case
 */
