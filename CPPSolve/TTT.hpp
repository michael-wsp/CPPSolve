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
#include <vector>

#include "Game.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

class TTT: public Game {
private:
    bool ALLOW_SYMMETRY;
    
    static const u8 PLAYER_MASK = 0b11;
    
    static const u8 WIN = 0b01;
    static const u8 TIE = 0b00;
    static const u8 LOSE = 0b10;
    static const u8 WL_MASK = 0b11;
    static const u8 PRIMITIVE = 0b100;
    static const u8 NOT_PRIMITIVE = 0b11;
    static const u8 REM_MASK = 0b11111000;
    
    // ' delimiter in binary ints represents rows on the board.
    
    // Bit masks for mirror operations
    static const u32 L_MASK  = 0b110000'110000'110000;
    static const u32 MV_MASK = 0b001100'001100'001100;
    static const u32 R_MASK  = 0b000011'000011'000011;
    
    /*
    static const u32 T_MASK  = 0b111111'000000'000000;
    static const u32 MH_MASK = 0b000000'111111'000000;
    static const u32 B_MASK  = 0b000000'000000'111111;
     */
    
    // Bit masks for rotation operations
    static const u32 R1_MASK = 0b110000'000011'000000;
    static const u32 R2_MASK = 0b001100'000000'000000;
    static const u32 R3_MASK = 0b000011'000000'000000;
    static const u32 R4_MASK = 0b000000'001100'000000;
    static const u32 R5_MASK = 0b000000'110000'000011;
    static const u32 R6_MASK = 0b000000'000000'110000;
    static const u32 R7_MASK = 0b000000'000000'001100;
    
    /*
    static const u32 L1_MASK = 0b110000'000000'000000;
    static const u32 L2_MASK = 0b001100'000000'110000;
    static const u32 L3_MASK = 0b000000'110000'000000;
    static const u32 L4_MASK = 0b000000'001100'000000;
    static const u32 L5_MASK = 0b000011'000000'001100;
    static const u32 L6_MASK = 0b000000'000011'000000;
    static const u32 L7_MASK = 0b000000'000000'000011;
     */
    
public:
    static const u32 BOARD_EMPTY = 0;
    static const u8 PLAYER_X = 0b01;
    static const u8 PLAYER_O = 0b10;
    
    std::unordered_map<u32, u8> cache;
    
    TTT(bool sym);
    
    u32 mirrorV(u32 position);
    
    u32 mirrorH(u32 position);
    
    u32 rotateR(u32 position);
    
    u32 rotateL(u32 postion);
    
    bool checkWin(u32 position, u8 player);
    
    bool checkFull(u32 position);
    
    u8 changePlayer(u8 player);
    
    u32 makeMove(u32 position, u32 move);
    
    std::vector<u32> genMoves(u32 position, u8 player);
    
    u8 primitiveValue(u32 position, u8 player);
    
    bool isPrimitive(u8 res);
    
    bool isWin(u8 res);
    
    bool isTie(u8 res);
    
    bool isLoss(u8 res);
    
    u8 getRem(u8 res);
    
    u8 getWin();
    
    u8 getTie();
    
    u8 getLoss();
    
    u32 getCanon(u32 position);
    
    void addCache(u32 position, u8 outcome);
    
    bool checkCache(u32 position);
    
    u8 getCache(u32 position);
    
    char playerToChar(u8 player);
    
    void printBoard(u32 position);
};

#endif /* TTT_hpp */
