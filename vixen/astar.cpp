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

Coord* Astar::get_lowest_f_score(){
    Coord * currentNode;
    Coord * finalNode = nullptr;
    double lowestFScore = 0x0FFFFFFF; // lowest needs to be set to a very high value so it can take the next lower value
    for(int i = 0 ; i < openSet.size() ; ++i){
        currentNode = &openSet.at(i);
        auto currentFscore = f_score.find(*currentNode);
        if((*currentFscore).second < lowestFScore){ // if current < lowest save to lowest, not the other way arround
            lowestFScore = (*currentFscore).second;
            finalNode = currentNode;
        }
    }
    return finalNode;
}


std::vector<Coord> Astar::reconstruct_path(std::unordered_map<Coord, Coord> &came_from, Coord end) {
    auto t = came_from.find(end);
    if(t == came_from.end()){
        std::vector<Coord> p = reconstruct_path(came_from, came_from.at(end));
        p.push_back(end);
        return p;
    } else {
        std::vector<Coord> p;
        p.push_back(end);
        return p;
    }
}

std::vector<Coord> Astar::CreatePath(Coord start, Coord end){
    openSet.push_back(start);
    Coord * current;
    double tentative_g_score;
    std::vector<Coord> neighbours;
    g_score.insert(std::make_pair(start, 0.0));
    f_score.insert(std::make_pair(start, (*g_score.find(start)).second + calculateDistance(start, end)));
    
    
    while(!openSet.empty())
    {
        current = get_lowest_f_score();
        std::cout << "Current x: " << current->x << " y: " << current->y << std::endl;
        if(current->x == end.x && current->y == end.y)
        {
            return reconstruct_path(came_from, end);
        }
        openSet.erase(find(openSet.begin(), openSet.end(),*current));
        closedSet.push_back(*current);
        
        neighbours = GetNeighbours(*current);
        
        for(int i = 0 ; i < neighbours.size() ; ++i)
        {
            if(find(closedSet.begin(), closedSet.end(),neighbours.at(i)) != closedSet.end())
            {
                continue;
            }
            tentative_g_score = (*g_score.find(*current)).second + calculateDistance(*current, neighbours.at(i));
            auto nb = neighbours.at(i);
            std::pair<Coord, double> second;
            if(g_score.find(nb) != g_score.end()){
                 second = (*g_score.find(nb));
            }
            auto look = find(closedSet.begin(), closedSet.end(),nb) ;
            if(look == closedSet.end() || tentative_g_score < second.second)
            {
                came_from.insert(std::make_pair(neighbours.at(i), *current));
                g_score.insert(std::make_pair(neighbours.at(i), tentative_g_score));
                f_score.insert(std::make_pair(neighbours.at(i), (*g_score.find(neighbours.at(i))).second + calculateDistance(neighbours.at(i), end)));
                if(find(openSet.begin(), openSet.end(),(neighbours.at(i))) == openSet.end())
                {
                    openSet.push_back(neighbours.at(i));
                }
            }
        }
    }
    return std::vector<Coord>();
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



