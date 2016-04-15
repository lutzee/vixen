//
//  natural.cpp
//  vixen
//
//  Created by Jamie Flint on 15/04/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//
//  This is the stuff of nightmares, its terrible code and doesn't currently work, to be investigated another day
//

#include "natural.hpp"

Natural::Natural(SDL_Renderer * renderer){
    this->renderer = renderer;
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

std::vector<Coord> Natural::calculatePath(std::vector<std::vector<int> > maze, Coord start, Coord end){
    std::vector<Coord> path;
    std::vector<double> weights;
    
    for(int i = 0 ; i < maze.size() ; ++i){
        for( int j = 0 ; j < maze[i].size() ; ++j){
            if(maze[j][i] != 1){
                weights.push_back(1.0);
            }
            else if(maze[j][i] == 1){
                weights.push_back(-1.0);
            }
        }
    }
    
    weights[(int)((start.y*maze.size())+start.x)] = calculateDistance(start, end);
    
    Coord current = start;
    Coord previous;
    double smallest_dist = (1<<20);
    double previous_dist;
    Coord next;
    bool backtrack = false;
    
    int steps = 0;

    while(!current.equals(end)){
        std::vector<Coord> neighbours = GetNeighbours(current, maze);
        if(backtrack){
            std::cout << "backtracking" << std::endl;
            std::cout << "current (" << current.x << "," << current.y << ")" << std::endl;
            for(int i = 0 ; i < neighbours.size() ; ++i){
                double next_dist = weights[(int)((neighbours[i].y*maze.size())+neighbours[i].x)];
                double current_dist = weights[(int)((current.y*maze.size())+current.x)];
                std::cout << "next (" << neighbours[i].x << "," << neighbours[i].y << ")" << std::endl;
                std::cout << "next val " << weights[(int)((neighbours[i].y*maze.size())+neighbours[i].x)] << std::endl;
                std::cout << "next dist " << next_dist << std::endl;
                if(weights[(int)((neighbours[i].y*maze.size())+neighbours[i].x)] == 1.0){
                    backtrack = false;
                    next = neighbours[i];
                    steps--;
                    weights[(int)((next.y*maze.size())+next.x)] = steps;
                    std::cout << "Stopping backtracking" << std::endl;
                    break;
                }
                if(next_dist < current_dist){
                    smallest_dist = next_dist;
                    next = neighbours[i];
                    steps--;
                    weights[(int)((next.y*maze.size())+next.x)] = steps;
                }
            }
        } else {
            for(int i = 0 ; i < neighbours.size() ; ++i)
            {
                double next_dist = calculateDistance(neighbours[i], end);
                if(neighbours.size() == 1 && weights[(int)((neighbours[i].y*maze.size())+neighbours[i].x)] > 1.0){
                    backtrack = true;
                    std::cout << "starting backtracking" << std::endl;
                    break;
                }
            
                if(weights[(int)((neighbours[i].y*maze.size())+neighbours[i].x)] == 1.0){
                        smallest_dist = next_dist;
                        next = neighbours[i];
                        steps++;
                        weights[(int)((next.y*maze.size())+next.x)] = steps;
                }
            }
        }
        previous_dist = smallest_dist;
        previous = current;
        current = next;
        path.push_back(previous);
        std::cout << "adding (" << previous.x << "," << previous.y << ")" << std::endl;
        std::cout << "small :" << smallest_dist << std::endl;
        std::cout << "prev :" << previous_dist << std::endl;
        PrintOut(weights, maze, current);
    }
    
    
    
    return path;
}