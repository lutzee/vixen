//
//  coord.hpp
//  vixen
//
//  Created by Jamie Flint on 29/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#ifndef coord_hpp
#define coord_hpp

#include <cmath>
#include <assert.h>

struct Coord
{
    Coord() {}
    Coord( double x, double y )
    : x(x)
    , y(y)
    {}
    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    
    const double operator[](const int idx) const
    {
        if (idx == 0) return x;
        if (idx == 1) return y;
        if (idx == 2) return w;
        
        assert(0);
    }
};


#endif /* coord_hpp */
