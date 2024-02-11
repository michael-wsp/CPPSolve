//
//  Solver.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.

#ifndef Solver_hpp
#define Solver_hpp

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include "Game.hpp"
#include "TTT.hpp"

typedef uint8_t u8;
typedef uint32_t u32;

namespace Solver {
    template <typename T> u8 solve(T position, u8 player, Game& game) {
        if (game.checkCache(position)) {
            return game.getCache(position);
        }
        u8 gameResult = game.primitiveValue(position, player);
        if (!game.isPrimitive(gameResult)) {
            u8 res;
            bool win = false;
            bool tie = false;
            u8 wRem = 0b11111;
            u8 tRem = 0b11111;
            u8 lRem = 0;
            u8 rem = 0;
            for (unsigned move : game.genMoves(position, player)) {
                res = solve(game.makeMove(position, move),
                            game.changePlayer(player), game);
                if (game.isLoss(res)) {
                    win = true;
                    rem = game.getRem(res);
                    if (rem < wRem) {
                        wRem = rem;
                    }
                }
                else if (game.isTie(res)) {
                    tie = true;
                    rem = game.getRem(res);
                    if (rem < tRem) {
                        tRem = rem;
                    }
                }
                else {
                    rem = game.getRem(res);
                    if (rem > lRem) {
                        lRem = rem;
                    }
                }
            }
            if (win) {
                gameResult = game.getWin() | ((wRem + 1) << 3);

            }
            else if (tie) {
                gameResult = game.getTie() | ((tRem + 1) << 3);
            }
            else {
                gameResult = game.getLoss() | ((lRem + 1) << 3);
            }
        }
        game.addCache(position, gameResult);
        return gameResult;
    }

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
            explicit Result(u8 outcome);
            [[nodiscard]] u8 getVal() const;
            [[nodiscard]] bool isPrimitive() const;
            [[nodiscard]] u8 getRemote() const;
        };
        static const u8 WIN = 0b01;
        static const u8 TIE = 0b00;
        static const u8 LOSE = 0b10;
        std::vector<std::vector<u32>> results;
        u8 maxRem;
    public:
        explicit GameOutcome(const std::unordered_map<u32, u8>& cache);
        u32 sumRow(u8 row);
        u32 sumCol(u8 col);
        void print();
    };
}
#endif /* Solver_hpp */
