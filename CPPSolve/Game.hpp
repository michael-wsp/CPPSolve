//
//  Game.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdint.h>
#include <vector>
#include <unordered_map>

typedef uint8_t u8;
typedef uint32_t u32;

class Game {
public:
    std::unordered_map<u32, u8> cache;
    virtual u8 changePlayer(u8) = 0;
    virtual u32 makeMove(u32, u32) = 0;
    virtual std::vector<u32> genMoves(u32, u8) = 0;
    virtual u8 primitiveValue(u32, u8) = 0;
    virtual bool isPrimitive(u8) = 0;
    virtual bool isWin(u8) = 0;
    virtual bool isTie(u8) = 0;
    virtual bool isLoss(u8) = 0;
    virtual u8 getRem(u8) = 0;
    virtual u8 getWin() = 0;
    virtual u8 getTie() = 0;
    virtual u8 getLoss() = 0;
    virtual void addCache(u32, u8) = 0;
    virtual bool checkCache(u32) = 0;
    virtual u8 getCache(u32) = 0;
};

#endif /* Game_hpp */
