//
//  astar.hpp
//  vixen
//
//  Created by Jamie Flint on 18/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef astar_hpp
#define astar_hpp

#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <cmath>

#include "coord.hpp"

class Astar {
private:
    std::vector< std::vector< int > > worldGrid;
    std::vector<Coord> openSet;
    std::vector<Coord> closedSet;
    std::unordered_map<Coord, Coord> came_from;
    std::unordered_map<Coord, double> g_score;
    std::unordered_map<Coord, double> f_score;

    std::vector<Coord> reconstruct_path(std::unordered_map<Coord, Coord> came_from, Coord end);
    double calculateDistance(Coord start, Coord end);
    Coord get_lowest_f_score();
public:
    Astar(std::vector< std::vector< int > > worldGrid);
    Astar(Coord start, Coord end);
    
    std::vector<Coord> CreatePath(Coord start, Coord end);
    std::vector<Coord> GetNeighbours(Coord coord);
};
#endif /* astar_hpp */
