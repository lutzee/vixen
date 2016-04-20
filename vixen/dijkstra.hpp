//
//  dijkstra.hpp
//  vixen
//
//  Created by Jamie Flint on 28/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef dijkstra_hpp
#define dijkstra_hpp

#include <stdio.h>
#include <vector>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>

#include "Coord.hpp"

class Dijkstra
{
private:
public:
    Dijkstra();
    std::vector<Coord> GetNeighbours(Coord current, std::vector< std::vector<int> > maze_vector);
    double calculateDistance(Coord start, Coord end);
    std::vector<Coord> getShortestPath(std::vector< std::vector< int > > maze, Coord start, Coord end, std::vector<int> dist);
    std::vector<Coord> calculatePath(Coord start, Coord end, std::vector< std::vector<int> > maze);
    void PrintOut(std::vector< std::vector< int > > maze_vector, std::vector<int> dist);
};


#endif /* dijkstra_hpp */
