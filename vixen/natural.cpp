//
//  natural.cpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "natural.hpp"

template<typename T>
void fast_erase(std::vector<T>& v, size_t i)
{

}

Natural::Natural(SDL_Renderer * renderer)
{
    this->renderer = renderer;
}

Natural::~Natural()
{
    
}

double Natural::calculateDistance(Coord start, Coord end)
{
    return sqrt(pow(start.x-end.x,2.0) + pow(start.y-end.y,2.0));
}

std::vector<Coord> Natural::GetNeighbours(Coord current, std::vector< std::vector< int> > maze_vector)
{
    std::vector<Coord> neighbours;
    Coord neighbour1 = current;
    neighbour1.x -=1;
    if(neighbour1.x >= 0 && ((maze_vector[(int) neighbour1.x][(int) neighbour1.y] != 1)))
    {
        neighbours.push_back(neighbour1);
    }
    
    Coord neighbour2 = current;
    neighbour2.x +=1;
    
    if((neighbour2.x < maze_vector.size()) && ((maze_vector[(int) neighbour2.x][(int) neighbour2.y] != 1)))
    {
        neighbours.push_back(neighbour2);
    }
    
    Coord neighbour3 = current;
    neighbour3.y -=1;
    
    if(neighbour3.y >= 0 && ((maze_vector[(int) neighbour3.x][(int) neighbour3.y] != 1)))
    {
        neighbours.push_back(neighbour3);
    }
    
    Coord neighbour4 = current;
    neighbour4.y +=1;
    if(neighbour4.y < maze_vector[0].size() && ((maze_vector[(int) neighbour4.x][(int) neighbour4.y] != 1)))
    {
        neighbours.push_back(neighbour4);
    }
 
    return neighbours;
}

void Natural::PrintOut(std::vector<std::vector<int> > maze, Coord current){
    for(int i = 0 ; i < maze.size() ; ++i){
        for(int j = 0 ; j < maze[i].size() ; ++j)
        {
            if(current.y == i && current.x == j)
            {
                std::cout << "CC";
            }
            else
            {
                if(maze[j][i] == 0)
                {
                    std::cout << "  ";
                }
                else if (maze[j][i] == 2)
                {
                    std::cout << "SS";
                }
                else if (maze[j][i] == 3)
                    std::cout << "EE";
                else
                {
                    std::cout << "██";
                }
            }
        }
        std::cout << std::endl;
    }
}

bool Natural::canMoveTowardsEnd(Coord current, std::vector<Coord> neighbours)
{
    for(int i = 0 ; i < neighbours.size() ; ++i)
    {
        if(neighbours[i].x == current.x+1 && neighbours[i].y == current.y)
        {
            return true;
        }
        if( neighbours[i].x == current.x && neighbours[i].y == current.y+1)
        {
            return true;
        }
    }
    return false;
}

bool Natural::canMoveAwayFromEnd(Coord current, std::vector<Coord> neighbours)
{
    for(int i = 0 ; i < neighbours.size() ; ++i){
        if(neighbours[i].x == current.x-1 && neighbours[i].y == current.y)
        {
            return true;
        }
        if( neighbours[i].x == current.x && neighbours[i].y == current.y-1)
        {
            return true;
        }
    }
    return false;
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


std::vector<Coord> Natural::calculatePath(std::vector<std::vector<int> > maze, Coord start, Coord end, sqlite3 * db, int series)
{
    std::vector<Coord> currentpath;
    
    Coord current = start;
    Coord previous;
    bool backtrack = false;
    bool justStoppedBacktracking = false;
    currentpath.push_back(current);
    int it;
    int bit, fit = 0;
    int n0, n1, n1a, no1 = 0;
    while(!current.equals(end))
    {
        ++it;
        if(backtrack)
        {
            bit++;
            Coord prevback = current;
            if(!currentpath.empty())
            {
                current = currentpath.back();

                std::vector<Coord> neighbours = GetNeighbours(current, maze);
                std::vector<Coord>::iterator toErase = find(neighbours.begin(),neighbours.end(),prevback);

                if(toErase != neighbours.end())
                {
                    neighbours.erase(toErase);
                }
                size_t nsize = neighbours.size();
                
                bool isStart = current.equals(start);
                
                if(!isStart)
                {
                    maze[prevback.x][prevback.y] = 1;
                    if(nsize == 1)
                    {
                        currentpath.pop_back();
                        continue;
                    }
                    else if(nsize > 1)
                    {
                        backtrack = false;
                        justStoppedBacktracking = true;
                        continue;
                    }
                }
                else
                {
                    backtrack = false;
                    justStoppedBacktracking = true;
                    maze[prevback.x][prevback.y] = 1;
                    continue;
                }
                
                currentpath.push_back(start);
                backtrack = false;
                justStoppedBacktracking = true;
                continue;
            }
        }
        fit++;
        std::vector<Coord> neighbours = GetNeighbours(current, maze);
        if(!current.equals(start))
        {
            if(justStoppedBacktracking){
                auto toErase = find(neighbours.begin(),neighbours.end(),currentpath.back());
                if(toErase != neighbours.end())
                {
                    neighbours.erase(toErase);
                }
                justStoppedBacktracking = false;
            }
            auto toErase = find(neighbours.begin(),neighbours.end(),previous);
            if(toErase != neighbours.end())
            {
                neighbours.erase(toErase);
            }
        }
        if(neighbours.size() > 1)
        {
            no1++;
            if(canMoveTowardsEnd(current, neighbours))
            {
                std::vector<int> ndist;
                std::vector<Coord> nextavail;
                for(int i = 0 ; i < neighbours.size() ; ++i)
                {
                    if(neighbours[i].x == current.x+1 && neighbours[i].y == current.y)
                    {
                        ndist.push_back(calculateDistance(neighbours[i], end));
                        nextavail.push_back(neighbours[i]);
                    }
                    if( neighbours[i].x == current.x && neighbours[i].y == current.y+1)
                    {
                        ndist.push_back(calculateDistance(neighbours[i], end));
                        nextavail.push_back(neighbours[i]);
                    }
                }
            
                int smallestdist = (1<<20);
                int smallestdistindex = 0;
                for( int i = 0 ; i < ndist.size() ; ++i)
                {
                    if(ndist[i] < smallestdist)
                    {
                        smallestdist = ndist[i];
                        smallestdistindex = i;
                    }
                }
            
                previous = current;
                if(find(currentpath.begin(),currentpath.end(),current) == currentpath.end())
                {
                    currentpath.push_back(current);
                }
                current = nextavail[smallestdistindex];
            }
            else if(canMoveAwayFromEnd(current, neighbours))
            {
                for(int i = 0 ; i < neighbours.size() ; ++i)
                {
                    if(neighbours[i].x == current.x-1 && neighbours[i].y == current.y)
                    {
                        previous = current;
                        if(find(currentpath.begin(),currentpath.end(),current) == currentpath.end())
                        {
                            currentpath.push_back(current);
                        }
                        current = neighbours[i];
                        break;
                    }
                    else if( neighbours[i].x == current.x && neighbours[i].y == current.y-1)
                    {
                        previous = current;
                        if(find(currentpath.begin(),currentpath.end(),current) == currentpath.end())
                        {
                            currentpath.push_back(current);
                        }
                        current = neighbours[i];
                        break;
                    }
                }
            }
        }
        else if (neighbours.size() == 0)
        {
            n0++;
            if(!current.equals(start))
                backtrack = true;
        }
        else if (neighbours.size() == 1)
        {
            n1++;
            previous = current;
            if(find(currentpath.begin(),currentpath.end(),current) == currentpath.end())
            {
                n1a++;
                currentpath.push_back(current);
            }
            current = neighbours[0];
        }
    }
    
    std::stringstream nss;
    
    nss << "insert into iterations (resulttype, iterations, series) values ('natural', " << it << ", " << series << ");";
    
    auto nstr = nss.str();
    sqlite3_exec(db, nstr.c_str() , callback, 0, &zErrMsg);

    return currentpath;
}