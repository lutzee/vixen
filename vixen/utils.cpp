//
//  utils.cpp
//  vixen
//
//  Created by Jamie Flint on 29/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include <stdio.h>
#include "coord.hpp"

float Dist(Coord p)
{
    // Compute the distance from the origin
    return sqrt(p.x*p.x + p.y*p.y);
}


void SortCoords(Coord pt[], int size)
{
    bool doMore = true;
    while (doMore)
    {
        doMore = false;  // Assume no more passes unless exchange made.
        for (int i=0; i<size-1; i++)
        {
            if (Dist(pt[i]) > Dist(pt[i+1]))
            {
                // Exchange elements
                Coord temp = pt[i]; pt[i] = pt[i+1]; pt[i+1] = temp;
                doMore = true;  // Exchange requires another pass.
            }
        }
    }
}

Coord PixelsToCoords(int x, int y)
{
    Coord coord;
    coord.x = x/50;
    coord.y = y/50;
    return coord;
}

