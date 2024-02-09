//
//  Solver.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#ifndef Solver_hpp
#define Solver_hpp

#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "Game.hpp"
#include "TTT.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

namespace Solver {
    u8 solve(u32 position, u8 player, Game& game);
    
    class GameOutcome {
    private:
        class Result {
        private:
            static const u8 VAL_MASK = 0b11;
            static const u8 PRIM_MASK = 0b100;
            static const u8 REM_MASK = 0b11111000;
            u8 value;
            bool primitive;
            u8 remoteness;
        public:
            Result(u8 outcome);
            u8 getVal();
            bool isPrimitive();
            u8 getRemote();
        };
        static const u8 WIN = 0b01;
        static const u8 TIE = 0b00;
        static const u8 LOSE = 0b10;
        std::vector<std::vector<u32>> results;
        u8 maxRem;
    public:
        GameOutcome(const std::unordered_map<u32, u8>& cache, u8 maxRemoteness);
        u32 sumRow(u8 row);
        u32 sumCol(u8 col);
        void print();
    };
}

#endif /* Solver_hpp */
