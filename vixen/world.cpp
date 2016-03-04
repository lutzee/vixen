//
//  world.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "world.hpp"

World::World(){

}

int World::init(SDL_Renderer *renderer){
    this->renderer = renderer;
    Player player = *new Player();
    player.init(renderer);
    playerList.push_back(player);
    // Generate Maze
    
    return 0;
}

void World::loop(){
    for ( Player &p : playerList ){
        // Update player
        p.update();
        
        // Render Player
        p.render(renderer);
        
        // Check win condition
    }
}

