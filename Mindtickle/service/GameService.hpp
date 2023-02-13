//
//  GameService.hpp
//  Mindtickle
//
//This class takes care of running the game

#ifndef GameService_hpp
#define GameService_hpp

#include "../model/Player.hpp"
#include "../model/GameBoard.hpp"
#include "GameReplayService.hpp"
#include "DiceService.hpp"
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

enum GameStatus {
    ACTIVE,
    FINISHED,
    ABORTED
};

class GameService {
    queue<Player*> playersQueue;
    Player* currentPlayer;
    GameBoard gameBoard;
    DiceService diceService;
    GameStatus gameStatus;
    GameReplayService gameReplayService;
    vector<string> winnersList;
    unordered_map<string, Player*> allPlayers;
    
    GameStatus shouldAbortGame() {
        //shall we only consider human players? if only computer players are left, then abort?
        auto totalPlayersWonSoFar = winnersList.size();
        if(totalPlayersWonSoFar == Constants::runGameTillXWinners || playersQueue.size() <= 1)
            return FINISHED;
        return ACTIVE;
    }
    
    bool didPlayerWin(Player* iCurrentPlayer) {
        return (gameBoard.getPositionForPlayerId(iCurrentPlayer->getPlayerId()) == gameBoard.getSize());
    }
    
    int processAllJumps(int iPosition) {
        int positionBeforeJump = iPosition;
        bool isJumpProcessed = false;
        
        while(!isJumpProcessed) {
            positionBeforeJump = iPosition;
            for(auto &it : gameBoard.getGameJumps()) {
                iPosition = it->processJumps(iPosition);
            }
            if(positionBeforeJump == iPosition)
                isJumpProcessed = true;
        }
        return iPosition;
    }
    
    void makeMove(Player* iCurrentPlayer, int iDiceRollValue) {
        int oldPosition = gameBoard.getPositionForPlayerId(iCurrentPlayer->getPlayerId());
        int newPosition = oldPosition + iDiceRollValue;
        int boardSize = gameBoard.getSize();
        
        if(newPosition > boardSize) {
            newPosition = oldPosition;
        } else {
            newPosition = processAllJumps(newPosition);
        }
        
        gameBoard.setPositionForPlayerId(iCurrentPlayer->getPlayerId(), newPosition);
    }
    
    void getUserInputForDiceRoll(string iPlayerName) {
        char inputKey;
        cout << "Press 'R' key to roll the dice for player " << iPlayerName << endl;
        //Validate input and make the game abort?
        cin >> inputKey;
    }
    
    /* Utility functions for printing data to console*/
    void printBoardState() {
        cout << "==== Board state ==== \n";
        
        for(auto &it : gameBoard.getPiecePositions()) {
            cout << "Player : " << allPlayers[it.first]->getPlayerName() << "|| is at cell number: " << it.second << endl;
        }
        
        cout << " ================== \n\n";
    }
    
    void printLeaderBoard() {
        cout << "\n ====== Final Results ===== \n";
        for(int iterator = 0; iterator < winnersList.size(); iterator++) {
            cout << "\n Rank: " << (iterator + 1) << " || " << allPlayers[winnersList[iterator]]->getPlayerName() << endl;
        }
    }
    
    void declareWinner(Player* iCurrentPlayer) {
        cout << iCurrentPlayer->getPlayerName() << " won \n\n";
    }
    
public:
    GameService(vector<Player*> iPlayersList, int iBoardSize = Constants::defaultBoardSize) : diceService(DiceService(Constants::defaultNumberOfDice)) {
        for(auto &it : iPlayersList) {
            playersQueue.push(it);
            allPlayers.insert({it->getPlayerId(), it});
        }
        
        shared_ptr<Snakes> snakes(new Snakes());
        snakes->addSnake(Jump(9, 1));
        snakes->addSnake(Jump(4, 2));
        //Validate snake and ladder values? or they will always be valid?
        //snakes->addSnake(Jump(10, 0));
        
        shared_ptr<Ladders> ladders(new Ladders());
        ladders->addLadder(Jump(1,3));
        
        vector<shared_ptr<GameJumps>> gameJumps;
        gameJumps.push_back(snakes);
        gameJumps.push_back(ladders);
        
        gameBoard = GameBoard(iBoardSize, gameJumps);
        gameStatus = ACTIVE;
    }
    
    bool startGame() {
        if(allPlayers.size() <= 1)
            return false;
        while(gameStatus == ACTIVE) {
            //get current player from queue
            currentPlayer = playersQueue.front();
            playersQueue.pop();
            
            //if player is human type then ask user to roll the dice
            if(dynamic_cast<HumanPlayer*>(currentPlayer) != nullptr) {
                getUserInputForDiceRoll(currentPlayer->getPlayerName());
            }
            
            //roll the dice and make the move
            int diceRollValue = diceService.rollDice();
            cout << "Dice roll for player: " << currentPlayer->getPlayerName() << " value: " << diceRollValue << endl;
            int currentPlayerPositionBeforeMove = gameBoard.getPositionForPlayerId(currentPlayer->getPlayerId());
            makeMove(currentPlayer, diceRollValue);
            int currentPlayerPositionAfterMove = gameBoard.getPositionForPlayerId(currentPlayer->getPlayerId());
            
            //check if the current player won and update accordingly
            bool didCurrentPlayerWin = didPlayerWin(currentPlayer);
            if(didCurrentPlayerWin) {
                winnersList.push_back(currentPlayer->getPlayerId());
                gameStatus = shouldAbortGame();
            } else {
                playersQueue.push(currentPlayer);
            }
            
            //print information after each iteration
            printBoardState();
            if(didCurrentPlayerWin)
                declareWinner(currentPlayer);
        
            //add logs for game iteration. This will be used for replaying the game
            gameReplayService.addGameMoveLog(GameMove(currentPlayer, diceRollValue, Jump(currentPlayerPositionBeforeMove, currentPlayerPositionAfterMove), didCurrentPlayerWin));
        }
        
        printLeaderBoard();
        return true;
    }
    
    void replayGame() {
        gameReplayService.replayGame();
    }
    
    vector<Player*> getWinnersList() {
        //TBD
        return {};
    }
};

#endif /* GameService_hpp */


/*
 Test cases -
 - replayGame() - check if replay service function was called
 - check for cases like - no player, single player, two player.
 - In case if only computers are left and we do not want to continue the game - check cases for that with difference combo of human and computer
 */
