//
//  XtoZero.cpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/8/24.
//

#include "XtoZero.hpp"
#include <stdint.h>
#include <vector>
#include <unordered_map>


typedef uint8_t u8;
typedef uint32_t u32;


XtoZero::XtoZero(u32 start, std::vector<u32> m) {
    this -> startingValue = start;
    this -> moves = m;
}
u8 XtoZero::changePlayer(u8 player) {
    return player;
}
u32 XtoZero::makeMove(u32 position, u32 move) {
    return position - move;
}
std::vector<u32> XtoZero::genMoves(u32 position, u8 player) {
    std::vector<u32> possibleMoves;
    for (u32 move : this -> moves) {
        if (move <= position) {
            possibleMoves.push_back(move);
        }
    }
    return possibleMoves;
}
u8 XtoZero::primitiveValue(u32 position, u8 player) {
    if (position == XtoZero::END) {
        return XtoZero::LOSE | XtoZero::PRIMITIVE;
    } else {
        return XtoZero::NOT_PRIMITIVE;
    }
}
bool XtoZero::isPrimitive(u8 res) {
    return res & XtoZero::PRIMITIVE;
}
bool XtoZero::isWin(u8 res) {
    return res & XtoZero::WIN;
}
bool XtoZero::isTie(u8 res) {
    return false;
}
bool XtoZero::isLoss(u8 res) {
    return res & XtoZero::LOSE;
}
u8 XtoZero::getRem(u8 res) {
    return res >> 3;
}
u8 XtoZero::getWin() {
    return XtoZero::WIN;
}
u8 XtoZero::getTie() {
    return XtoZero::TIE;
}
u8 XtoZero::getLoss() {
    return XtoZero::LOSE;
}
void XtoZero::addCache(u32 position, u8 outcome) {
    this -> cache.insert({position, outcome});
}
bool XtoZero::checkCache(u32 position) {
    return this -> cache.contains(position);
}
u8 XtoZero::getCache(u32 position) {
    return this -> cache.at(position);
}
