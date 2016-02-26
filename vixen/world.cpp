//
//  world.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "world.hpp"

World::World(){
    Player player = *new Player();
    player.init();
    playerList.push_back(player);
}

int World::init(SDL_Window *sdl2_window){
    this->sdl2_window = sdl2_window;
    // Generate Maze
    
    return 0;
}

void World::loop(){
    for ( Player &p : playerList ){
        // Update player
        p.update();
        
        // Render Player
        // Check win condition
        
    }
    
}

