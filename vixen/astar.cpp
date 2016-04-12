//
//  astar.cpp
//  vixen
//
//  Created by Jamie Flint on 18/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "astar.hpp"

Astar::Astar(std::vector< std:: vector< int > > worldGrid, SDL_Renderer *renderer){
    this->worldGrid = worldGrid;
    this->renderer = renderer;
    this->tileSurface= SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/path.bmp");
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
        auto currentFscore = f_score.find(currentNode);
        if((*currentFscore).second < lowestFScore){ // if current < lowest save to lowest, not the other way arround
            lowestFScore = (*currentFscore).second;
            finalNode = currentNode;
        }
    }
    return finalNode;
}


std::vector<Coord> Astar::reconstruct_path(std::unordered_map<Coord, Coord> &came_from, Coord end) {
    auto t = came_from.find(end);
    if(t != came_from.end()){
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
    Coord current;
    double tentative_g_score;
    std::vector<Coord> neighbours;
    g_score.insert(std::make_pair(start, 0.0));
    f_score.insert(std::make_pair(start, (*g_score.find(start)).second + calculateDistance(start, end)));
    
    std::cout << "end x: " << end.x << " y: " << end.y << std::endl;

    while(!openSet.empty())
    {
        std::cout << "openset size " << openSet.size() << std::endl;
        current = get_lowest_f_score();
        std::cout << "Current x: " << current.x << " y: " << current.y << std::endl;

        if(current.equals(end)){
            return reconstruct_path(came_from, end);
        }
        openSet.erase(find(openSet.begin(), openSet.end(),current));
        closedSet.push_back(current);
        neighbours = GetNeighbours(current);
        
        for(int i = 0 ; i < neighbours.size() ; ++i)
        {
            if(find(closedSet.begin(), closedSet.end(),neighbours.at(i)) != closedSet.end())
            {
                continue;
            }
            tentative_g_score = (*g_score.find(current)).second + calculateDistance(current, neighbours.at(i));
            auto nb = neighbours.at(i);
            std::pair<Coord, double> second;
            if(g_score.find(nb) != g_score.end()){
                 second = (*g_score.find(nb));
            }
            auto look = find(closedSet.begin(), closedSet.end(),nb) ;
            if(look == closedSet.end() || tentative_g_score < second.second)
            {
                came_from.insert(std::make_pair(neighbours.at(i), current));
                g_score.insert(std::make_pair(neighbours.at(i), tentative_g_score));
                f_score.insert(std::make_pair(neighbours.at(i), (*g_score.find(neighbours.at(i))).second + calculateDistance(neighbours.at(i), end)));
                if(find(openSet.begin(), openSet.end(),neighbours.at(i)) == openSet.end())
                {
                    auto toadd = neighbours.at(i);
                        std::cout << "Adding (" << toadd.x << "," << toadd.y << ")" << std::endl;
                        openSet.push_back(toadd);
                }
            }
        }
    }
    return std::vector<Coord>();
}

std::vector<Coord> Astar::GetNeighbours(Coord current) {
    std::vector<Coord> neighbours;
    Coord neighbour1 = current;
    neighbour1.x -=1;
    if(neighbour1.x >= 0){
        neighbours.push_back(neighbour1);
    }
    
    Coord neighbour2 = current;
    neighbour2.x +=1;

    if((neighbour2.x < worldGrid.size()) && ((worldGrid[(int) neighbour2.x][(int) neighbour2.y] == 0)||(worldGrid[(int) neighbour2.x][(int) neighbour2.y] == 3))){
        neighbours.push_back(neighbour2);
    }
    
    Coord neighbour3 = current;
    neighbour3.y -=1;

    if(neighbour3.y >= 0 && ((worldGrid[(int) neighbour3.x][(int) neighbour3.y] == 0)||(worldGrid[(int) neighbour3.x][(int) neighbour3.y] == 3))){
        neighbours.push_back(neighbour3);
    }
    
    Coord neighbour4 = current;
    neighbour4.y +=1;
    if(neighbour4.y < worldGrid[0].size() && ((worldGrid[(int) neighbour4.x][(int) neighbour4.y] == 0)||(worldGrid[(int) neighbour4.x][(int) neighbour4.y] ==3))){
        neighbours.push_back(neighbour4);
    }
    
    Coord neighbour5 = current;
    neighbour5.x -=1;
    neighbour5.y -=1;
    if(neighbour5.x >= 0 && neighbour5.y >= 0 && worldGrid[(int) neighbour5.x][(int) neighbour5.y] == 0){
        neighbours.push_back(neighbour5);
    }
    
    Coord neighbour6 = current;
    neighbour6.x +=1;
    neighbour6.y -=1;
    if(neighbour6.x < worldGrid.size() && neighbour6.y >= 0 && worldGrid[(int) neighbour6.x][(int) neighbour6.y] == 0){
        neighbours.push_back(neighbour6);
    }
    
    Coord neighbour7 = current;
    neighbour7.x -=1;
    neighbour7.y +=1;
    if(neighbour7.x >= 0 && neighbour7.y < worldGrid[0].size() && worldGrid[(int) neighbour7.x][(int) neighbour7.y] == 0){
        neighbours.push_back(neighbour7);
    }
    
    Coord neighbour8 = current;
    neighbour8.x +=1;
    neighbour8.y +=1;
    if(neighbour8.x < worldGrid.size() && neighbour8.y < worldGrid[0].size() && worldGrid[(int) neighbour8.x][(int) neighbour8.y] == 0){
        neighbours.push_back(neighbour8);
    }
    
    return neighbours;
}

void Astar::renderTile(SDL_Renderer *renderer, Coord coord){
    SDL_Texture *pathTex = SDL_CreateTextureFromSurface(renderer, tileSurface);
    
        SDL_Rect texture_rect;
        texture_rect.x = coord.x*20;
        texture_rect.y = coord.y*20;
        texture_rect.w = 20;
        texture_rect.h = 20;
        SDL_RenderCopy(renderer, pathTex, NULL, &texture_rect);

    
    SDL_RenderPresent(renderer); //updates the renderer
}



