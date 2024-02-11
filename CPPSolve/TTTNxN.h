//
// Created by Michael Setchko Palmerlee on 2/10/24.
//

#ifndef CPPSOLVE_TTTNXN_H
#define CPPSOLVE_TTTNXN_H

#include "Game.hpp"
#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <vector>

typedef uint8_t u8;
typedef uint32_t u32;

class TTTNxN : public Game {
public:
    static const u32 size = 5;
    static const u32 to_win = 5;
    typedef std::bitset<size> state;
private:
    static const state BOARD_EMPTY;

    static const constexpr state PLAYER_X = state(0b01);
    static const constexpr state PLAYER_O = state(0b10);
    static const constexpr state PLAYER_EMPTY = state(0b00);
    static const constexpr state PLAYER_MASK = state(0b11);
    static const u8 TOKEN_MASK = 0b11;

    bool ALLOW_SYMMETRY;

public:
    explicit TTTNxN(bool);
    std::unordered_map<state, u8> cache;
    state rotateR(state);
    state mirrorV(state);
    [[nodiscard]] u8 changePlayer(u8) const;
    state makeMove(state, state) const;
    std::vector<state> genMoves(state, state) const;
    u8 primitiveValue(state, u8);
    bool isPrimitive(u8);
    bool isWin(u8);
    bool isTie(u8);
    bool isLoss(u8);
    u8 getRem(u8);
    u8 getWin();
    u8 getTie();
    u8 getLoss();
    void addCache(state, u8);
    bool checkCache(state);
    u8 getCache(u32);
};


#endif //CPPSOLVE_TTTNXN_H
