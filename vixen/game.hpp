//
//  game.hpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "world.hpp"

class Game {
private:
    World world;
public:
    SDL_Renderer *renderer;
    Game(SDL_Renderer *renderer);
    int Run();

};

#endif /* game_hpp */
