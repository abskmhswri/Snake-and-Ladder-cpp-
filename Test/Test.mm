//
//  Test.m
//  Test
//
// Test class with sample tests.

#import <XCTest/XCTest.h>
#import "DiceService.hpp"
#import "GameJumps.hpp"
#import "GameMove.hpp"
#import "GameBoard.hpp"
#import "Player.hpp"
#import "Constants.hpp"
#import "GameJumps.hpp"

@interface Test : XCTestCase

@end

- (void)testDiceService {
    int numberOfDiceFaces = 6;
    DiceService diceService(1);
    XCTAssertGreaterThanOrEqual(numberOfDiceFaces, diceService.rollDice());
}

- (void)testGameJumpsWhenJumpIsUnavailable{
    Snakes* snakes = new Snakes();
    snakes->addSnake(Jump(3, 1));
    
    XCTAssertEqual(1, snakes->processJumps(1));
}

- (void)testGameJumpsWhenJumpIsAvailable{
    Snakes* snakes = new Snakes();
    snakes->addSnake(Jump(3, 1));
    
    XCTAssertEqual(1, snakes->processJumps(3));
}

- (void)testGameMove{
    GameMove gameMove(new ComputerPlayer(), 2, Jump(3,5));
    
    XCTAssertFalse(gameMove.getDidWinGame());
}

- (void)testGameBoard{
    GameBoard gameBoard(10, {});
    
    XCTAssertEqual(0, gameBoard.getGameJumps().size());
}

- (void)testHumanPlayer{
    string playerName = "Jeff";
    Player *humanPlayer = new HumanPlayer(playerName);
    
    XCTAssertEqual(playerName, humanPlayer->getPlayerName());
    string playerId = humanPlayer->getPlayerId();
    
    XCTAssertNotEqual(std::string::npos, playerId.find(Constants::humanPlayerIdPrefix));
}

- (void)testComputerPlayer{
    Player *computerPlayer = new ComputerPlayer();
    
    string playerId = computerPlayer->getPlayerId();
    XCTAssertNotEqual(std::string::npos, playerId.find(Constants::computerPlayerIdPrefix));
}

@end
