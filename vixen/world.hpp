//
//  world.hpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <list>

#include "renderer.hpp"
#include "player.hpp"

class World {
private:
    SDL_Window *sdl2_window;
    Renderer renderer;
    std::list<Player> playerList;
public:
    World();
    int init(SDL_Window *sdl2_window);
    void loop();

};

#endif /* world_hpp */
