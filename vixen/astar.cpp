//
//  astar.cpp
//  vixen
//
//  Created by Jamie Flint on 18/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "astar.hpp"

Astar::Astar(std::vector< std:: vector< int > > worldGrid){
    this->worldGrid = worldGrid;
}

Astar::Astar(Coord start, Coord end){
    openSet.push_back(start);
}

double Astar::calculateDistance(Coord start, Coord end){
    return sqrt(pow(start.x-end.x,2.0) + pow(start.y-end.y,2.0));
    //return start.dst(end);
}

Coord Astar::get_lowest_f_score(){
    Coord currentNode;
    Coord finalNode;
    double lowestFScore = 0x0FFFFFFF; // lowest needs to be set to a very high value so it can take the next lower value
    for(int i = 0 ; i < openSet.size() ; ++i){
        currentNode = openSet.at(i);
        if(f_score.get(currentNode) < lowestFScore){ // if current < lowest save to lowest, not the other way arround
            lowestFScore = f_score.get(currentNode);
            finalNode = currentNode;
        }
    }
    return finalNode;
}

void Astar::CreatePath(Coord start, Coord end){
    openSet.push_back(start);
    Coord current;
    double tentative_g_score;
    std::vector<Coord> neighbours;
    g_score.put(start, 0.0);
    f_score.put(start, g_score.get(start) + calculateDistance(start, end));
    
    
    while(!openSet.empty()){
        current = get_lowest_f_score();
        if(current.equals(end)){
            return reconstruct_path(came_from, end);
        }
        openSet.erase(find(openSet.begin(), openSet.end(),current));
        closedSet.push_back(current);
        
        neighbours = GetNeighbours(current);
        
        for(int i = 0 ; i < neighbours.size() ; ++i){
            if(find(closedSet.begin(), closedSet.end(),neighbours.at(i)) != closedSet.end()){
                continue;
            }
            tentative_g_score = g_score.get(current) + calculateDistance(current, neighbours.at(i));
            if(find(closedSet.begin(), closedSet.end(),neighbours.at(i)) != closedSet.end() || tentative_g_score < g_score.get(neighbours.at(i))){
                came_from.put(neighbours.at(i),current);
                g_score.put(neighbours.at(i), tentative_g_score);
                f_score.put(neighbours.at(i), g_score.get(neighbours.at(i)) + calculateDistance(neighbours.at(i), end));
                if(find(openSet.begin(), openSet.end(),neighbours.at(i)) != openSet.end()){
                    openSet.push_back(neighbours.at(i));
                }
            }
        }
    }
}

std::vector<Coord> Astar::GetNeighbours(Coord current) {
    std::vector<Coord> neighbours;
    
    Coord neighbour = current;
    neighbour.x -=1;
    if(neighbour.x >= 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.x +=1;
    if(neighbour.x < worldGrid.size() && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.y -=1;
    if(neighbour.y >= 0 && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.y +=1;
    if(neighbour.y < worldGrid[0].size() && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.x -=1;
    neighbour.y -=1;
    if(neighbour.x >= 0 && neighbour.y >= 0 && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.x +=1;
    neighbour.y -=1;
    if(neighbour.x < worldGrid.size() && neighbour.y >= 0 && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.x -=1;
    neighbour.y +=1;
    if(neighbour.x >= 0 && neighbour.y < worldGrid[0].size() && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    neighbour = current;
    neighbour.x +=1;
    neighbour.y +=1;
    if(neighbour.x < worldGrid.size() && neighbour.y < worldGrid[0].size() && worldGrid[(int) neighbour.x][(int) neighbour.y] == 0){
        neighbours.push_back(neighbour);
    }
    
    return neighbours;
}

std::vector<Coord> reconstruct_path(std::unordered_map<Coord, Coord> came_from, Coord end) {
    if(came_from.find(end) != came_from.end()){
        std::vector<Coord> p = reconstruct_path(came_from, came_from.at(end));
        p.push_back(end);
        return p;
    } else {
        std::vector<Coord> p;
        p.push_back(end);
        return p;
    }
}

