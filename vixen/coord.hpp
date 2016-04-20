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
#include <string>
#include <sstream>

class Coord
{
public:
    Coord * parent;
    
    
    const double operator[](const int idx) const
    {
        if (idx == 0) return x;
        if (idx == 1) return y;
        if (idx == 2) return w;
        
        assert(0);
    }
    
    static int compareTo(int coord1, int coord2);
    

    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    
    Coord() {}
    Coord( double x, double y )
    : x(x)
    , y(y)
    {}
    
    Coord( double x, double y, Coord * parent )
    : x(x)
    , y(y)
    , parent(parent)
    {}
    
    static Coord * Opposite(Coord coord);
    bool equals(Coord coord);
    
    //bool operator==(const Coord &other) const
    //{
    //    return (x == other.x && y == other.y);
    //}
    
    friend bool operator==(const Coord &c1, const Coord &c2);

};

bool operator== ( const Coord &c1, const Coord &c2);


namespace std
{
    template<> struct hash<Coord>
    {
        typedef Coord argument_type;
        typedef std::size_t result_type;
        result_type operator() (argument_type const& coord) const
        {
            result_type const h1 ( std::hash<double>()(coord.x) );
            result_type const h2 ( std::hash<double>()(coord.y) );
            
            return h1 ^ (h2 << 1);
        }
    };
}

#endif /* coord_hpp */
