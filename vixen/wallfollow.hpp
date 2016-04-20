//
//  wallfollow.hpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef wallfollow_hpp
#define wallfollow_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <sqlite3.h>
#include <chrono>
#include <thread>

#include "Coord.hpp"
enum edirection
{
    right = 1,
    down = 2,
    left = 3,
    up = 4
};

class Wallfollow
{
private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
public:
    Wallfollow();
    std::vector<Coord> calculatePath(std::vector< std::vector< int > > maze, Coord start, Coord end, sqlite3 * db, int series);
    bool canTurnRight(Coord current, std::vector< std::vector< int > > maze, edirection dir);
    bool canMoveForwards(Coord current, std::vector< std::vector< int > > maze, edirection dir);
    bool canTurnLeft(Coord current, std::vector< std::vector< int > > maze, edirection dir);
    edirection turnRight(edirection dir);
    edirection turnLeft(edirection dir);
    edirection turnBack(edirection dir);
    void PrintOut(std::vector< std::vector< int > > maze, std::vector<int> visited);
    Coord moveForwards(Coord current, edirection dir);
};

#endif /* wallfollow_hpp */
