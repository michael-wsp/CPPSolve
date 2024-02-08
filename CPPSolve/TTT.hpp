//
//  TTT.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

/*
 **Ported to C++ because Python bitwise operation speed is awful :(**
 
 I have chosen represent the board state with 18 bit integers
 (As a bit of a challenge to see if I could optimize speed and memory usage).
 Each square on the board is 2 bits, as defined below.
 This is not completely efficient (0b11 is not used) but it allows me to use
 bitwise operators to compare and modify game states.
 This game state uses slightly more than half the space a 9-char string
 would! (28 vs 50 bytes, according to sys.getsizeof())
 I also implemented this in C++ where this string would use 10 bytes and
 an unsigned int uses 4 bytes, which is even better.
 ---
 Game outcomes are also represented with integers, with a primitive state
 "modifier" as defined below
 ---
 X and 0 "Tokens" are also represented with 2 bits as defined below.
 I also defined a comparison token which allows me to use certain bitwise
 operations with tokens and game boards.
 */

#ifndef TTT_hpp
#define TTT_hpp

#include <stdint.h>
#include "Game.hpp"

class TTT: public Game {
private:
    static const unsigned BOARD_EMPTY = 0;
    
    static const uint8_t PLAYER_X = 0b01;
    static const uint8_t PLAYER_Y = 0b10;
    static const uint8_t PLAYER_MASK = 0b11;
    
    static const uint8_t WIN = 0b01;
    static const uint8_t TIE = 0b00;
    static const uint8_t LOSE = 0b10;
    static const uint8_t WL_MASK = 0b11;
    static const uint8_t PRIMITIVE = 0b100;
    
    // ' delimiter in binary ints represents rows on the board.
    
    // Bit masks for mirror operations
    static const unsigned L_MASK = 0b110000'110000'110000;
    static const unsigned M_MASK = 0b001100'001100'001100;
    static const unsigned R_MASK = 0b000011'000011'000011;
    
    
    // Bit masks for rotation operations
    static const unsigned R1_MASK = 0b110000'000011'000000;
    static const unsigned R2_MASK = 0b001100'000000'000000;
    static const unsigned R3_MASK = 0b000011'000000'000000;
    static const unsigned R4_MASK = 0b000000'001100'000000;
    static const unsigned R5_MASK = 0b000000'110000'000011;
    
public:
    TTT();
    ~TTT();
    
    
};

#endif /* TTT_hpp */
