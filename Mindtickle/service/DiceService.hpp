//
//  DiceService.hpp
//  Mindtickle
//
// All the functionalities related to die are housed here.

#ifndef DiceService_hpp
#define DiceService_hpp

#include <cstdlib>
#include "../utils/Constants.hpp"

class DiceService {
    int numberOfDice;
public:
    DiceService(int iNumberOfDice) {
        numberOfDice = iNumberOfDice;
    }
    
    int rollDice() {
        int totalDiceSum = 0;
        for(int i = 1; i <= numberOfDice; i++) {
            totalDiceSum += (rand() % Constants::numberOfFacesOnDice) + 1;
        }
        
        return totalDiceSum;
    }
};
#endif /* DiceService_hpp */

/*
 - check that rollDice() gives value within range
 - vary number of dice and check result
 */
