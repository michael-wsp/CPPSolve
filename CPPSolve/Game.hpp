//
//  Game.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdint.h>

typedef uint8_t u8;
typedef uint32_t u32;

class Game {
public:
    Game();
    ~Game();
    virtual u32 makeMove() = 0;
    virtual u32* genMoves() = 0;
    virtual u32 primitiveValue() = 0;
    virtual void addCache() = 0;
    virtual u8 getCache() = 0;
};

#endif /* Game_hpp */
