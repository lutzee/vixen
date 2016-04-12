//
//  maze.hpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <string>
#include <random>
#include <cmath>
#include <stack>
#include <algorithm>
#include <SDL2/SDL.h>

#include "coord.hpp"

enum direction{
	north=0,
	south=1,
	east=2,
	west=3
};

class Maze {
private:
	int width, height;
	int Id(int x, int y);
	int X(int x);
	int Y(int y);
    SDL_Surface *mazeSurface;
public:
    Coord start,end;
	std::vector< std::vector<int> > maze_vector;
	Maze(int width, int height);
	void GenerateOne();
	void GenerateTwo();
    void GenerateThree();
	void PrintOut();
    void render(SDL_Renderer * renderer);
};

#endif /* maze_hpp */
