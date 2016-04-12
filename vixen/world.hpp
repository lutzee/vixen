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
#include "astar.hpp"

class World {
private:
    Maze *maze = new Maze(40,40);
    std::vector<Player> playerList;
    std::vector<Coord> path;
    SDL_Surface *pathSurface;
public:
    SDL_Renderer *renderer;
    World();
    int init(SDL_Renderer *renderer);
    void loop();
    void renderPath(SDL_Renderer *renderer, std::vector<Coord> path);
};

#endif /* world_hpp */
