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
#include "XtoZero.hpp"

int main() {
    TTT ttt = TTT(false);
    
    Solver::solve(TTT::BOARD_EMPTY, TTT::PLAYER_X, ttt);
    
    Solver::GameOutcome result = Solver::GameOutcome(ttt.cache);
    
    result.print();
    
    XtoZero xzero = XtoZero(10, {1, 2});
    
    Solver::solve(xzero.startingValue, 1, xzero);
    
    Solver::GameOutcome res2 = Solver::GameOutcome(xzero.cache);
    
    res2.print();
    
    return 0;
}
