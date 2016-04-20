//
//  player.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "player.hpp"


Player::Player()
{
    x = y = 20;
    w = h = 20;
    coord.x = 0;
    coord.y = 0;
}

int Player::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    std::cout << "player init" << std::endl;
    this->playerSurface = SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/up.bmp");
    if(this->playerSurface != nullptr)
        std::cout << "player surface created" << std::endl;
    return 0;
}

void Player::update()
{
    

}

void Player::render(SDL_Renderer *r)
{
    SDL_Texture *player = SDL_CreateTextureFromSurface(renderer, playerSurface);
    //SDL_RenderClear(renderer); //clears the renderer
    SDL_Rect texture_rect;
    texture_rect.x = x;
    texture_rect.y = y;
    texture_rect.w = w;
    texture_rect.h = h;
    SDL_RenderCopyEx(renderer, player, NULL, &texture_rect, 180, NULL,SDL_FLIP_NONE);
    
    SDL_RenderPresent(renderer); //updates the renderer
}