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
#include <vector>

#include "renderer.hpp"
#include "player.hpp"
#include "maze.hpp"

class World {
private:
    Maze *maze = new Maze(40,40);
    std::vector<Player> playerList;
public:
    SDL_Renderer *renderer;
    World();
    int init(SDL_Renderer *renderer);
    void loop();

};

#endif /* world_hpp */
