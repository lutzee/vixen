//
//  player.hpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>

class Player {
private:
    int x,y,w,h;
    
public:
    Player();
    int init();
    void update();
    
};


#endif /* player_hpp */
