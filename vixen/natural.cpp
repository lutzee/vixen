//
//  natural.cpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "natural.hpp"

Natural::Natural(SDL_Renderer * renderer){
    this->renderer = renderer;
}

Natural::~Natural(){
    
}

double Natural::calculateDistance(Coord start, Coord end){
    return sqrt(pow(start.x-end.x,2.0) + pow(start.y-end.y,2.0));
}

std::vector<Coord> Natural::GetNeighbours(Coord current, std::vector< std::vector< int> > maze_vector) {
    std::vector<Coord> * neighbours = new std::vector<Coord>();
    Coord neighbour1 = current;
    neighbour1.x -=1;
    if(neighbour1.x >= 0 && ((maze_vector[(int) neighbour1.x][(int) neighbour1.y] != 1))){
        neighbours->push_back(neighbour1);
    }
    
    Coord neighbour2 = current;
    neighbour2.x +=1;
    
    if((neighbour2.x < maze_vector.size()) && ((maze_vector[(int) neighbour2.x][(int) neighbour2.y] != 1))){
        neighbours->push_back(neighbour2);
    }
    
    Coord neighbour3 = current;
    neighbour3.y -=1;
    
    if(neighbour3.y >= 0 && ((maze_vector[(int) neighbour3.x][(int) neighbour3.y] != 1))){
        neighbours->push_back(neighbour3);
    }
    
    Coord neighbour4 = current;
    neighbour4.y +=1;
    if(neighbour4.y < maze_vector[0].size() && ((maze_vector[(int) neighbour4.x][(int) neighbour4.y] != 1))){
        neighbours->push_back(neighbour4);
    }
 
    return *neighbours;
}

void Natural::PrintOut(std::vector<double> weights, std::vector<std::vector<int> > maze, Coord current){
    for(int i = 0 ; i < maze.size() ; ++i){
        for(int j = 0 ; j < maze[i].size() ; ++j){
            if(current.y == i && current.x == j){
                std::cout << "CC";
            }else {
            if(maze[j][i] == 0){
                int distance = weights[(i*maze.size())+j];
                if(distance > 1.0)
                    if(distance < 10.0)
                        std::cout << " " << (int)distance;
                    else
                        std::cout << distance;
                else if (distance == 1.0){
                    std::cout << " 1";
                }
                else
                    std::cout << distance;
            }
            else if (maze[j][i] == 2)
                std::cout << "SS";
            else if (maze[j][i] == 3)
                std::cout << "EE";
            else{
                std::cout << "██";
            }
            }
        }
        std::cout << std::endl;
    }
}

bool Natural::canMoveTowardsEnd(Coord current, std::vector<Coord> neighbours){
    for(int i = 0 ; i < neighbours.size() ; ++i){
        if(neighbours[i].x == current.x+1 && neighbours[i].y == current.y){
            return true;
        }
        if( neighbours[i].x == current.x && neighbours[i].y == current.y+1){
            return true;
        }
    }
    return false;
}

bool Natural::canMoveAwayFromEnd(Coord current, std::vector<Coord> neighbours){
    for(int i = 0 ; i < neighbours.size() ; ++i){
        if(neighbours[i].x == current.x-1 && neighbours[i].y == current.y){
            return true;
        }
        if( neighbours[i].x == current.x && neighbours[i].y == current.y-1){
            return true;
        }
    }
    return false;
}

std::vector<Coord> Natural::calculatePath(std::vector<std::vector<int> > maze, Coord start, Coord end){
    std::stack<Coord> currentpath;
    
    Coord current = start;
    Coord previous;
    bool backtrack = false;
    currentpath.push(current);
    while(!current.equals(end)){
        if(backtrack){
            Coord prevback = current;
            if(!currentpath.empty()){
                current = currentpath.top();
                currentpath.pop();
                bool isStart = current.equals(start);
                size_t nsize = GetNeighbours(current, maze).size();
                if(isStart && (nsize== 2)){
                    backtrack = false;
                    maze[prevback.x][prevback.y] = 1;
                    continue;
                } else if(isStart && (nsize == 1)){
                    backtrack = false;
                    continue;
                } 
                if(nsize > 2){
                    backtrack = false;
                    maze[prevback.x][prevback.y] = 1;
                    continue;
                }
            } else {
                currentpath.push(start);
                backtrack = false;
            }
            continue;
        }
        std::vector<Coord> neighbours = GetNeighbours(current, maze);
        if(!current.equals(start)){
            auto toErase = find(neighbours.begin(),neighbours.end(),previous);
            if(toErase != neighbours.end()){
                neighbours.erase(toErase);
            }
        }
        if(neighbours.size() > 1){
            if(canMoveTowardsEnd(current, neighbours)){
                std::vector<int> ndist;
                for(int i = 0 ; i < neighbours.size() ; ++i){
                    if(neighbours[i].x == current.x+1 && neighbours[i].y == current.y){
                        ndist.push_back(calculateDistance(current, end));
                    }
                    if( neighbours[i].x == current.x && neighbours[i].y == current.y+1){
                        ndist.push_back(calculateDistance(current, end));
                    }
                }
            
                int smallestdist = (1<<20);
                int smallestdistindex = 0;
                for( int i = 0 ; i < ndist.size() ; ++i){
                    if(ndist[i] < smallestdist){
                        smallestdist = ndist[i];
                        smallestdistindex = i;
                    }
                }
            
                previous = current;
                currentpath.push(current);
                current = neighbours[smallestdistindex];
            } else if(canMoveAwayFromEnd(current, neighbours)){
                for(int i = 0 ; i < neighbours.size() ; ++i){
                    if(neighbours[i].x == current.x-1 && neighbours[i].y == current.y){
                        previous = current;
                        currentpath.push(current);
                        current = neighbours[i];
                        break;
                    }
                    if( neighbours[i].x == current.x && neighbours[i].y == current.y-1){
                        previous = current;
                        currentpath.push(current);
                        current = neighbours[i];
                        break;
                    }
                }
            }
        }else if (neighbours.size() == 0){
            if(!current.equals(start))
                backtrack = true;
        } else if (neighbours.size() == 1) {
            previous = current;
            currentpath.push(current);
            current = neighbours[0];
        }
    }
    
    std::vector<Coord> path;
    while(!currentpath.empty()){
        path.push_back(currentpath.top());
        currentpath.pop();
    }
    
    return path;
}