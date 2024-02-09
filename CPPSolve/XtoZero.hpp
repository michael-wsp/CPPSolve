//
//  XtoZero.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/8/24.
//

#ifndef XtoZero_hpp
#define XtoZero_hpp

#include <stdint.h>
#include <vector>
#include <unordered_map>

#include "Game.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

class XtoZero : public Game {
private:
    static const u8 WIN = 0b01;
    static const u8 LOSE = 0b10;
    static const u8 TIE = 0b00;
    static const u8 PRIMITIVE = 0b11;
    static const u8 WL_MASK = 0b11;
    
    u32 startingValue;
    std::vector<u32> moves;
    
public:
    XtoZero(u32 start, std::vector<u32> m);
     u8 changePlayer(u8);
     u32 makeMove(u32, u32);
     std::vector<u32> genMoves(u32, u8);
     u8 primitiveValue(u32, u8);
     bool isPrimitive(u8);
     bool isWin(u8);
     bool isTie(u8);
     bool isLoss(u8);
     u8 getRem(u8);
     u8 getWin();
     u8 getTie();
     u8 getLoss();
     void addCache(u32, u8);
     bool checkCache(u32);
     u8 getCache(u32);
};

#endif /* XtoZero_hpp */
