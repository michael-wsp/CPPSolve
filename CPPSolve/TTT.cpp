//
//  TTT.cpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
#include "TTT.hpp"
#include <stdint.h>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef uint8_t u8;
typedef uint32_t u32;

TTT::TTT(bool sym) {
    this -> ALLOW_SYMMETRY = sym;
}
u32 TTT::mirrorV(u32 position) {
    return (position & TTT::L_MASK) >> 4 |
           (position & TTT::MV_MASK) |
           (position & TTT::R_MASK) << 4;
}
u32 TTT::rotateR(u32 position) {
    return (position & TTT::R1_MASK) >> 4 |
           (position & TTT::R2_MASK) >> 8 |
           (position & TTT::R3_MASK) >> 12 |
           (position & TTT::R4_MASK) |
           (position & TTT::R5_MASK) << 4 |
           (position & TTT::R6_MASK) << 12 |
           (position & TTT::R7_MASK) << 8;
}
bool TTT::checkWin(u32 position, u8 player) {
    u32 WIN1 = 0b000000'000000'010101;
    u32 WIN2 = 0b000001'000001'000001;
    u32 WIN3 = 0b010000'000100'000001;
    u32 WIN4 = 0b000001'000100'010000;
    if (player == TTT::PLAYER_O) {
        WIN1 <<= 1;
        WIN2 <<= 1;
        WIN3 <<= 1;
        WIN4 <<= 1;
    }
    for (int i = 0; i < 3; i++) {
        if ((position & WIN1) == WIN1 ||
            (position & WIN2) == WIN2) {
            return true;
        }
        WIN1 <<= 6;
        WIN2 <<= 2;
    }
    if ((position & WIN3) == WIN3 ||
        (position & WIN4) == WIN4) {
        return true;
    }
    return false;
}
bool TTT::checkFull(u32 position) {
    for (int i = 0; i < 9; i++) {
        if (!(position & TTT::PLAYER_MASK)) {
            return false;
        }
        position >>= 2;
    }
    return true;
}
u8 TTT::changePlayer(u8 player) {
    return player ^ TTT::PLAYER_MASK;
}
u32 TTT::makeMove(u32 position, u32 move) {
    return position | move;
}
std::vector<u32> TTT::genMoves(u32 position, u8 player) {
    u32 move = player;
    u32 mvMask = TTT::PLAYER_MASK;
    std::vector<unsigned> moves;
    for (int i = 0; i < 9; i++) {
        if (!(mvMask  & position)) {
            moves.push_back(move);
        }
        mvMask <<= 2;
        move <<= 2;
    }
    return moves;
}
u8 TTT::primitiveValue(u32 position, u8 player) {
    if (TTT::checkWin(position, TTT::changePlayer(player))) {
        return TTT::LOSE | TTT::PRIMITIVE;
    }
    else if (TTT::checkFull(position)) {
        return TTT::TIE | TTT::PRIMITIVE;
    }
    else {
        return NOT_PRIMITIVE;
    }
}
bool TTT::isPrimitive(u8 res) {
    return res & TTT::PRIMITIVE;
}
bool TTT::isWin(u8 res) {
    return res & TTT::WIN;
}
bool TTT::isTie(u8 res) {
    return !(res & TTT::WL_MASK);
}
bool TTT::isLoss(u8 res) {
    return res & TTT::LOSE;
}
u8 TTT::getRem(u8 res) {
    return res >> 3;
}
u8 TTT::getWin() {
    return TTT::WIN;
}
u8 TTT::getTie() {
    return TTT::TIE;
}
u8 TTT::getLoss() {
    return TTT::LOSE;
}
u32 TTT::getCanon(u32 position) {
    if (this -> cache.contains(position)) {
        return position;
    }
    u32 v = TTT::mirrorV(position); // Covers vertical mirror
    u32 r = TTT::rotateR(position); // Covers 1 rotation right
    u32 sym;
    if (this -> cache.contains(v)) {
        return v;
    }
    if (this -> cache.contains(r)) {
        return r;
    }
    sym = TTT::mirrorV(r); // covers 1 right rotation + vertical mirror
    if (this -> cache.contains(sym)) {
        return sym;
    }
    sym = TTT::rotateR(r); // covers 2 rotations right
    if (this -> cache.contains(sym)) {
        return sym;
    }
    sym = TTT::mirrorV(sym); // covers horizontal mirror
    if (this -> cache.contains(sym)) {
        return sym;
    }
    sym = TTT::rotateR(v); // covers vertical mirror + 1 right rotation
    if (this -> cache.contains(sym)) {
        return sym;
    }
    sym = TTT::mirrorV(sym); // covers 1 left rotation
    if (this -> cache.contains(sym)) {
        return sym;
    }
    return position;
}
void TTT::addCache(u32 position, u8 outcome) {
    this -> cache.insert({position, outcome});
}
bool TTT::checkCache(u32 position) {
    if (this -> ALLOW_SYMMETRY) {
        return this -> cache.contains(position);
    } else {
        if (this -> cache.contains(position)) {
            return true;
        } else {
            return TTT::getCanon(position) != position;
        }
    }
}
u8 TTT::getCache(u32 position) {
    if (this -> ALLOW_SYMMETRY) {
        return this -> cache.at(position);
    } else {
        return this -> cache.at(getCanon(position));
    }
}
char TTT::playerToChar(u8 player) {
    if (player == TTT::PLAYER_X) {
        return 'X';
    } else if (player == TTT::PLAYER_O) {
        return 'O';
    } else {
        return '_';
    }
}
void TTT::printBoard(u32 position) {
    std::vector<char> board;
    for (int i = 0; i < 9; i++) {
        board.insert(board.begin(), TTT::playerToChar(position & TTT::PLAYER_MASK));
        position >>= 2;
    }
    for (int i = 0; i < 3; i++) {
        std::cout << board[3 * i] << board[3 * i + 1] << board[3 * i + 2] << std::endl;
    }
}
