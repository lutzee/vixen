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
    SDL_GLContext opengl3_context;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    // set the opengl context version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    // turn on double buffering set the depth buffer to 24 bits
    // you may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    // create the sdl2 window
    sdl2_window = SDL_CreateWindow("Vixen", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, 1280, 720,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    // create the opengl3 context
    opengl3_context = SDL_GL_CreateContext(sdl2_window);
    
    Game game = *new Game(sdl2_window);
    game.Run();
    
    return 0;
}
