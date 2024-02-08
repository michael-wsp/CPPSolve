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

#include "Game.hpp"
#include "TTT.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

namespace Solver {
    void solve(u32 position, u8 player, const Game& game);
    
    class GameOutcome {
    private:
        class Result {
        private:
            std::string value;
            bool primitive;
        public:
            Result(u8 outcome);
            std::string getVal();
            bool isPrimitive();
        };
    };
}

#endif /* Solver_hpp */
