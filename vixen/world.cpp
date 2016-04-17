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
    //Player player = *new Player();
    //player.init(renderer);
    //playerList.push_back(player);
    // Generate Maze
    this->pathSurface = SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/path.bmp");
    
    maze->GenerateThree();
    printf("maze generated\n");
    maze->PrintOut();
    maze->render(renderer);
    
    Astar astar = *new Astar(maze->maze_vector, renderer);

    auto begin = std::chrono::high_resolution_clock::now();
    path = astar.CreatePath(maze->start, maze->end);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "A* took: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << "us" << std::endl;
    
    Dijkstra dj = *new Dijkstra();
    begin = std::chrono::high_resolution_clock::now();
    
    path = dj.calculatePath(maze->start, maze->end, maze->maze_vector);

    end = std::chrono::high_resolution_clock::now();
    std::cout << "Dijkstra took: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << "us" << std::endl;

    Wallfollow wf = *new Wallfollow();
    begin = std::chrono::high_resolution_clock::now();
    
    path = wf.calculatePath(maze->maze_vector, maze->start, maze->end);
    
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Wall Follow took: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << "us" << std::endl;
    
    
    Natural n = Natural(renderer);
    begin = std::chrono::high_resolution_clock::now();

    path = n.calculatePath(maze->maze_vector, maze->start, maze->end);
    
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Natural took: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << "us" << std::endl;
    
    
    
    renderPath(renderer, path);
    //delete n;
    
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

