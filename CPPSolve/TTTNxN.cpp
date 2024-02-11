//
// Created by Michael Setchko Palmerlee on 2/10/24.
//

#include "TTTNxN.h"
#include <bitset>
#include <cmath>
#include <vector>

typedef std::bitset<TTTNxN::size> state;

TTTNxN::TTTNxN(bool sym) {
    ALLOW_SYMMETRY = sym;
}

state TTTNxN::rotateR(state position) {
    state newPos;
    int shift;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            shift = (size - 1) * (x + 1) - y * (size + 1);
            if (shift >= 0) {
                newPos |= (position & (PLAYER_MASK << (2 * (x + 5 * y)))) << (2 * abs(shift));
            } else {
                newPos |= (position & (PLAYER_MASK << (2 * (x + 5 * y)))) >> (2 * abs(shift));
            }
        }
    }
    return newPos;
}

state TTTNxN::mirrorV(state position) {
    state newPos;
    for (int x = 0; x < floor(size / 2); x++) {
        newPos |= (position & (PLAYER_MASK << (2 * x))) << (2 * (size - x - 1)) |
                (position & PLAYER_MASK << (2 * (size - x - 1))) >> (2 * x);
    }
    return newPos;
}

u8 TTTNxN::changePlayer(u8 player) const {
    return player ^ TOKEN_MASK;
}

state TTTNxN::makeMove(state position, state move) const {
    return position | move;
}

std::vector<state> TTTNxN::genMoves(state position, state player) const {
    state move = player;
    std::vector<state> moves;
    for (int i = 0; i < size * size; i++) {
        if ((position & move).none()) {
            moves.push_back(move);
        }
        move <<= 2;
    }
    return moves;
}

