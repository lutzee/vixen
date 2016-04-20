//
//  natural.hpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef natural_hpp
#define natural_hpp

#include <stdio.h>
#include <vector>
#include <stack>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>
#include <sqlite3.h>
#include <chrono>
#include <thread>
#include <sstream>

#include "coord.hpp"

class Natural
{
private:
    SDL_Renderer *renderer;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
public:
    Natural(SDL_Renderer * renderer);
    ~Natural();
    double calculateDistance(Coord start, Coord end);
    std::vector<Coord> GetNeighbours(Coord current, std::vector< std::vector< int> > maze_vector);
    
    bool canMoveTowardsEnd(Coord current, std::vector<Coord> neighbours);
    bool canMoveAwayFromEnd(Coord current, std::vector<Coord> neighbours);
    std::vector<Coord> calculatePath(std::vector< std::vector< int > > maze, Coord start, Coord end, sqlite3 * db, int series);
    void PrintOut( std::vector< std::vector< int > > maze, Coord current);
};


#endif /* natural_hpp */
