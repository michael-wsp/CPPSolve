//
//  TTT.cpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#include "TTT.hpp"

#include <stdint.h>
#include <iostream>
#include <unordered_map>

typedef uint8_t u8;
typedef uint32_t u32;

u32 TTT::mirror(u32 position) {
    return (position & TTT::L_MASK) >> 4 |
           (position & TTT::M_MASK) |
           (position & TTT::R_MASK) << 4;
}

u32 TTT::rotateR(u32 position) {
    
}

u32 TTT::makeMove(u32 position, u32 move) {
    return position | move;
}

u8 TTT::changePlayer(u8 player) {
    return player ^ TTT::PLAYER_MASK;
}
