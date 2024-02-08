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
 This game state uses 40% the space a 9-char string would.
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
#include <unordered_map>

#include "Game.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

class TTT: public Game {
private:
    static const u32 BOARD_EMPTY = 0;
    
    static const u8 PLAYER_X = 0b01;
    static const u8 PLAYER_Y = 0b10;
    static const u8 PLAYER_MASK = 0b11;
    
    static const u8 WIN = 0b01;
    static const u8 TIE = 0b00;
    static const u8 LOSE = 0b10;
    static const u8 WL_MASK = 0b11;
    static const u8 PRIMITIVE = 0b100;
    static const u8 NOT_PRIMITIVE = 0b11;
    
    // ' delimiter in binary ints represents rows on the board.
    
    // Bit masks for mirror operations
    static const u32 L_MASK = 0b110000'110000'110000;
    static const u32 M_MASK = 0b001100'001100'001100;
    static const u32 R_MASK = 0b000011'000011'000011;
    
    
    // Bit masks for rotation operations
    static const u32 R1_MASK = 0b110000'000011'000000;
    static const u32 R2_MASK = 0b001100'000000'000000;
    static const u32 R3_MASK = 0b000011'000000'000000;
    static const u32 R4_MASK = 0b000000'001100'000000;
    static const u32 R5_MASK = 0b000000'110000'000011;
    
    std::unordered_map<u32, u8> cache;
    
public:
    TTT();
    
    ~TTT();
    
    u32 mirror(u32 position);
    
    u32 rotateR(u32 position);
    
    bool checkWin(u32 position, u8 player);
    
    bool checkFull(u32 position);
    
    u8 changePlayer(u8 player);
    
    u32 makeMove(u32 position, u32 move);
    
    u32* genMoves(u32 position);
    
    u8 primitiveValue(u32 position);
    
    void addCache(u32 position, u8 outcome);
    
    u8 getCache(u32 position);
    
    void printBoard(u32 position);
};

#endif /* TTT_hpp */
