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
    TTT ttt = TTT(true);
    
    Solver::solve(TTT::BOARD_EMPTY, TTT::PLAYER_X, ttt);
    
    Solver::GameOutcome result = Solver::GameOutcome(ttt.cache);
    
    result.print();
    
    std::cout << std::endl << std::endl;
    
    TTT tttSym = TTT(false);
    
    Solver::solve(TTT::BOARD_EMPTY, TTT::PLAYER_X, tttSym);
    
    Solver::GameOutcome result2 = Solver::GameOutcome(tttSym.cache);
    
    result2.print();
    
    // TTT was 5x faster after removing symmetries! 10ms -> 2ms
    
    std::cout << std::endl << std::endl;
    
    XtoZero xzero = XtoZero(10, {1, 2});
    
    Solver::solve(xzero.startingValue, 1, xzero);
    
    Solver::GameOutcome result3 = Solver::GameOutcome(xzero.cache);
    
    result3.print();
    
    return 0;
}
