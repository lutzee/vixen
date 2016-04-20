//
//  player.hpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "coord.hpp"

class Player
{
private:
    int x,y,w,h;
    Coord coord;
    SDL_Surface *playerSurface;
public:
    SDL_Renderer *renderer;
    Player();
    int init(SDL_Renderer *renderer);
    void update();
    void render(SDL_Renderer *r);
};


#endif /* player_hpp */
