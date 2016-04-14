//
//  idastar.hpp
//  vixen
//
//  Created by Jamie Flint on 13/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef idastar_hpp
#define idastar_hpp

#include <stdio.h>

#include "coord.hpp"

class Idastar {
    /*
private:
    std::vector< std::vector< int > > worldGrid;
    std::vector<Coord> openSet;
    std::vector<Coord> closedSet;
    std::unordered_map<Coord, Coord> came_from;
    std::unordered_map<Coord, double> g_score;
    std::unordered_map<Coord, double> f_score;
    std::vector<Coord> reconstruct_path(std::unordered_map<Coord, Coord> &came_from, Coord end);
    double calculateDistance(Coord start, Coord end);
    Coord get_lowest_f_score();
    SDL_Surface *tileSurface;
    SDL_Renderer *renderer;
public:
    Astar(std::vector< std::vector< int > > worldGrid, SDL_Renderer *renderer);
    Astar(Coord start, Coord end);
    
    std::vector<Coord> CreatePath(Coord start, Coord end);
    std::vector<Coord> GetNeighbours(Coord coord);
    void renderTile(SDL_Renderer *renderer, Coord coord);
    */
};
#endif /* idastar_hpp */
