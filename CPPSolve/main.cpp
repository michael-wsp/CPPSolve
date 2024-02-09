//
//  main.cpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#include <iostream>
#include <chrono>

#include "Game.hpp"
#include "Solver.hpp"
#include "TTT.hpp"

int main() {
    TTT ttt = TTT(true);
    
    Solver::solve(TTT::BOARD_EMPTY, TTT::PLAYER_X, ttt);
    
    /*
    for (auto kv : ttt.cache) {
        std::cout << (std::bitset<8>)(kv.second) << std::endl;
    }
     */
    
    Solver::GameOutcome result = Solver::GameOutcome(ttt.cache, ttt.MAX_REM);
    
    result.print();
    
    return 0;
}
