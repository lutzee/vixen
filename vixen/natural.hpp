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
#include <SDL2/SDL.h>
#include <iostream>

#include "coord.hpp"

class Natural {
private:
    SDL_Renderer *renderer;
public:
    Natural(SDL_Renderer * renderer);
    double calculateDistance(Coord start, Coord end);
    std::vector<Coord> GetNeighbours(Coord current, std::vector< std::vector< int> > maze_vector);
    std::vector<Coord> calculatePath(std::vector< std::vector< int > > maze, Coord start, Coord end);
    void PrintOut(std::vector< double > weights, std::vector< std::vector< int > > maze, Coord current);
};


#endif /* natural_hpp */
