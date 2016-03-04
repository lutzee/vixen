//
//  wall.hpp
//  vixen
//
//  Created by Jamie Flint on 04/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef wall_hpp
#define wall_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "coord.hpp"

class Wall {
private:
    int x,y,w,h;
    Coord coord;
    SDL_Surface *playerSurface;
public:
    SDL_Renderer *renderer;
    Wall();
    int init(SDL_Renderer *renderer);
    void render(SDL_Renderer *r);
};

#endif /* wall_hpp */
