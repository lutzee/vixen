//
//  aabb.cpp
//  vixen
//
//  Created by Jamie Flint on 04/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include <stdio.h>
#include "coord.hpp"
struct AABB
{
    AABB() : c(), r() {}
    
    AABB(const Coord & center, const Coord & halfwidths)
    : c(center)
    , r(halfwidths)
    {}
    
    Coord c;        // center point
    Coord r;        // halfwidths
};

double makepos(double a)
{
    return std::fabs(a);
}

bool checkColision(const AABB &a, const AABB &b)
{
    if ( makepos(a.c[0] - b.c[0]) > (a.r[0] + b.r[0]) ) return false;
    if ( makepos(a.c[1] - b.c[1]) > (a.r[1] + b.r[1]) ) return false;
    if ( makepos(a.c[2] - b.c[2]) > (a.r[2] + b.r[2]) ) return false;
    
    // We have an overlap
    return true;
};