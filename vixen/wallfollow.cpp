//
//  wallfollow.cpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "wallfollow.hpp"

Wallfollow::Wallfollow(){
    
}

bool Wallfollow::canTurnRight(Coord current, std::vector< std::vector< int > > maze, edirection dir)
{
    switch(dir)
    {
        case right:
            if(maze[current.x][current.y+1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case down:
            if(maze[current.x-1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case left:
            if(maze[current.x][current.y-1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case up:
            if(maze[current.x+1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
    }
    return false;
}

bool Wallfollow::canMoveForwards(Coord current, std::vector< std::vector< int > > maze, edirection dir)
{
    switch(dir)
    {
        case right:
            if(maze[current.x+1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case down:
            if(maze[current.x][current.y+1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case left:
            if(maze[current.x-1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case up:
            if(maze[current.x][current.y-1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
    }
    return false;
}

bool Wallfollow::canTurnLeft(Coord current, std::vector< std::vector< int > > maze, edirection dir)
{
    switch(dir)
    {
        case right:
            if(maze[current.x][current.y-1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case down:
            if(maze[current.x+1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case left:
            if(maze[current.x][current.y+1] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        case up:
            if(maze[current.x-1][current.y] != 1)
            {
                return true;
            }
            else
            {
                return false;
            }

    }
    return false;
}

Coord Wallfollow::moveForwards(Coord current, edirection dir)
{
    switch(dir)
    {
        case right:
            return Coord(current.x+1, current.y);
        case down:
            return Coord(current.x, current.y+1);
        case left:
            return Coord(current.x-1, current.y);
        case up:
            return Coord(current.x, current.y-1);
    }
}

edirection Wallfollow::turnRight(edirection dir)
{
    switch(dir)
    {
        case right:
            return down;
        case down:
            return left;
        case left:
            return up;
        case up:
            return right;
    }
}


edirection Wallfollow::turnLeft(edirection dir)
{
    switch(dir)
    {
        case right:
            return up;
        case down:
            return right;
        case left:
            return down;
        case up:
            return left;
    }
}



edirection Wallfollow::turnBack(edirection dir)
{
    switch(dir)
    {
        case right:
            return left;
        case down:
            return up;
        case left:
            return right;
        case up:
            return down;
    }
}

void Wallfollow::PrintOut(std::vector< std::vector< int > > maze, std::vector<int> visited)
{
    for(int i = 0 ; i < maze.size() ; ++i)
    {
        for(int j = 0 ; j < maze[i].size() ; ++j)
        {
            if(maze[j][i] == 0)
            {
                if(visited[(i*maze.size())+j] == 1)
                {
                    std::cout << "VV";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            else if (maze[j][i] == 2)
            {
                std::cout << "SS";
            }
            else if (maze[j][i] == 3)
            {
                std::cout << "EE";
            }
            else
            {
                std::cout << "██";
            }
        }
        std::cout << std::endl;
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

std::vector<Coord> Wallfollow::calculatePath(std::vector<std::vector<int> > maze, Coord start, Coord end, sqlite3 * db, int series)
{
    std::vector<int> visited;
    std::vector<Coord> path;
    edirection dir = right;
    Coord current = start;
    for(int i = 0 ; i < maze.size() ; ++i)
    {
        for(int j = 0 ; j < maze[i].size() ; ++j)
        {
            visited.push_back(0);
        }
    }
    
    int it = 0;
    
    while(!current.equals(end))
    {
        it++;
        if(canTurnRight(current, maze, dir))
        {
            dir = turnRight(dir);
            visited[(current.y*maze.size())+current.x] = 1;
            path.push_back(current);
            current = moveForwards(current, dir);
        }
        else if(canMoveForwards(current, maze, dir))
        {
            visited[(current.y*maze.size())+current.x] = 1;
            path.push_back(current);
            current = moveForwards(current, dir);
        }
        else if(canTurnLeft(current, maze, dir))
        {
            dir = turnLeft(dir);
            visited[(current.y*maze.size())+current.x] = 1;
            path.push_back(current);
            current = moveForwards(current, dir);
        }
        else
        {
            dir = turnBack(dir);
            visited[(current.y*maze.size())+current.x] = 1;
            path.push_back(current);
            current = moveForwards(current, dir);
        }
    }
    path.push_back(end);
    std::stringstream nss;
    
    nss << "insert into iterations (resulttype, iterations, series) values ('wallfollow', " << it << ", " << series << ");";
    
    auto nstr = nss.str();
    sqlite3_exec(db, nstr.c_str() , callback, 0, &zErrMsg);

    
    return path;
}