//
//  Solver.cpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#include "Solver.hpp"

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <bitset>

#include "Game.hpp"
#include "TTT.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

namespace Solver {
    GameOutcome::Result::Result(u8 outcome) {
        value = outcome & VAL_MASK;
        primitive = (outcome & PRIM_MASK) >> 2;
        remoteness = (outcome & REM_MASK) >> 3;
    }
    
    u8 GameOutcome::Result::getVal() const {
        return this -> value;
    }
    
    bool GameOutcome::Result::isPrimitive() const {
        return this -> primitive;
    }
    
    u8 GameOutcome::Result::getRemote() const {
        return this -> remoteness;
    }
    
    GameOutcome::GameOutcome(const std::unordered_map<u32, u8>& cache) {
        u8 remStore = 0;
        u8 remTmp;
        for (auto kv : cache) {
            Result res = Result(kv.second);
            remTmp = res.getRemote();
            if (remTmp > remStore) {
                remStore = remTmp;
            }
            while (remTmp >= results.size()) {
                results.push_back({0, 0, 0});
            }
            results[remTmp][res.getVal()]++;
        }
        this -> maxRem = remStore;
    }
    
    u32 GameOutcome::sumRow(u8 row) {
        u32 sum = 0;
        for (u32 n : this -> results[row]) {
            sum += n;
        }
        return sum;
    }
    
    u32 GameOutcome::sumCol(u8 col) {
        u32 sum = 0;
        for (std::vector<u32> row : results) {
            sum += row[col];
        }
        return sum;
    }
    
    void GameOutcome::print() {
        u32 wins = this -> sumCol(1);
        u32 ties = this -> sumCol(0);
        u32 losses = this -> sumCol(2);
        std::cout << "Remote    Win       Tie       Lose      Total     " << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        for (u8 r = maxRem; r != (u8) - 1; r--) {
            std::cout << std::setfill(' ') << std::setw(10) << std::left << (int)r <<
            std::setfill(' ') << std::setw(10) << std::left << results[r][1] <<
            std::setfill(' ') << std::setw(10) << std::left << results[r][0] <<
            std::setfill(' ') << std::setw(10) << std::left << results[r][2] <<
            std::setfill(' ') << std::setw(10) << std::left << this -> sumRow(r) << std::endl;
        }
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Total     " <<
        std::setfill(' ') << std::setw(10) << std::left << wins <<
        std::setfill(' ') << std::setw(10) << std::left << ties <<
        std::setfill(' ') << std::setw(10) << std::left << losses <<
        std::setfill(' ') << std::setw(10) << std::left << wins + ties + losses << std::endl;
    }
}
