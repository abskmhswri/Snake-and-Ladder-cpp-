//
//  Constants.h
//  Mindtickle
//
// This class has all the constants. These should ideally be configurations.

#ifndef Constants_h
#define Constants_h

#include <string>

class Constants {
public:
    static inline int defaultBoardSize = 100;
    static inline int defaultNumberOfDice = 1;
    static inline int numberOfFacesOnDice = 6;
    static inline int runGameTillXWinners = 3;
    static inline std::string computerPlayerNamePrefix = "Computer";
    static inline std::string humanPlayerIdPrefix = "H";
    static inline std::string computerPlayerIdPrefix = "C";
};

#endif /* Constants_h */
