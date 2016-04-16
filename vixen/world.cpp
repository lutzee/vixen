//
//  world.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "world.hpp"
#include "dijkstra.hpp"

World::World(){

}

int World::init(SDL_Renderer *renderer){
    this->renderer = renderer;
    Player player = *new Player();
    player.init(renderer);
    playerList.push_back(player);
    // Generate Maze
    this->pathSurface = SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/path.bmp");
    
    maze->GenerateThree();
    printf("maze generated\n");
    maze->PrintOut();
    maze->render(renderer);
    
    //Astar astar = *new Astar(maze->maze_vector, renderer);
    //path = astar.CreatePath(maze->start, maze->end);

    //Dijkstra dj = *new Dijkstra();
    //path = dj.calculatePath(maze->start, maze->end, maze->maze_vector);
    
    Natural n = *new Natural(renderer);
    path = n.calculatePath(maze->maze_vector, maze->start, maze->end);
    
    //Wallfollow wf = *new Wallfollow();
    //path = wf.calculatePath(maze->maze_vector, maze->start, maze->end);
    
    renderPath(renderer, path);
    
    return 0;
}

void World::renderPath(SDL_Renderer *renderer, std::vector<Coord> path){
    SDL_Texture *pathTex = SDL_CreateTextureFromSurface(renderer, pathSurface);
    
    for(auto &path : path){
        SDL_Rect texture_rect;
        texture_rect.x = path.x*20;
        texture_rect.y = path.y*20;
        texture_rect.w = 20;
        texture_rect.h = 20;
        SDL_RenderCopy(renderer, pathTex, NULL, &texture_rect);
    }
    
    SDL_RenderPresent(renderer); //updates the renderer
}

void World::loop(){
    maze->render(renderer);
    
    for ( Player &p : playerList ){
        // Update player
        p.update();
        
        // Render Player
        p.render(renderer);
        
        // Check win condition
    }
}

