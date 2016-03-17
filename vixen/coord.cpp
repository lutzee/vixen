//
//  coord.cpp
//  vixen
//
//  Created by Jamie Flint on 29/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "coord.hpp"

 Coord * Coord::Opposite(Coord coord){
    if(coord.parent == NULL){
        return NULL;
    }
    if(compareTo(coord.x,coord.parent->x)!=0)
        return new Coord(coord.x+compareTo(coord.x,coord.parent->x),coord.y, &coord);
    if(compareTo(coord.y,coord.parent->y)!=0)
        return new Coord(coord.x,coord.y+compareTo(coord.y,coord.parent->y), &coord);
    return NULL;
}

int Coord::compareTo(int coord1, int coord2){
    if(coord1 > coord2){
        return 1;
    }else if (coord1 < coord2){
        return -1;
    }else{
        return 0;
    }
    return 0;
}

