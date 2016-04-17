//
//  main.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"

int main(int argc, const char * argv[]) {
    // SDL Init
    SDL_Window* sdl2_window = 0;
    //SDL_GLContext opengl3_context;
    SDL_Init(SDL_INIT_VIDEO);
    
    // set the opengl context version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // turn on double buffering set the depth buffer to 24 bits
    // you may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    // create the sdl2 window
    sdl2_window = SDL_CreateWindow("Vixen", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, 820, 820,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    // create the opengl3 context
    //opengl3_context = SDL_GL_CreateContext(sdl2_window);
    
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    SDL_Renderer *renderer = SDL_CreateRenderer(sdl2_window, -1, SDL_RENDERER_SOFTWARE);
    
    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    
    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);
    
    
    Game game = *new Game(renderer);
    game.Run();
    
    return 0;
}
