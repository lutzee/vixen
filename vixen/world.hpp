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
#include <sqlite3.h>

#include "renderer.hpp"
#include "player.hpp"
#include "maze.hpp"
#include "astar.hpp"
#include "dijkstra.hpp"
#include "natural.hpp"
#include "wallfollow.hpp"

class World
{
private:
    std::vector<Player> playerList;
    std::vector<Coord> path;
    SDL_Surface *pathSurface;
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
public:
    SDL_Renderer *renderer;
    World();
    int init(SDL_Renderer *renderer);
    void GenerateMaze(int sereies);
    void loop();
    void close();
    void renderPath(SDL_Renderer *renderer, std::vector<Coord> path);
};

#endif /* world_hpp */
