//
//  Game.hpp
//  CPPSolve
//
//  Created by Michael Setchko Palmerlee on 2/7/24.
//

#ifndef Game_hpp
#define Game_hpp

class Game {
public:
    Game();
    ~Game();
    virtual unsigned makeMove() = 0;
    virtual unsigned genMoves() = 0;
    virtual unsigned primitiveValue() = 0;
};

#endif /* Game_hpp */
