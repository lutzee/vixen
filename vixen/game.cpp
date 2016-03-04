//
//  game.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "game.hpp"

Game::Game(SDL_Renderer *renderer){
    this->renderer = renderer;
}

int Game::Run(){
    world.init(renderer);
    
    SDL_Event e;
    bool quit = false;
    while (!quit){
        // Event polling
        while (SDL_PollEvent(&e)){
            //If user closes the window
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        world.loop();
    }
    
    return 0;
}