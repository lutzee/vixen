//
//  dijkstra.cpp
//  vixen
//
//  Created by Jamie Flint on 28/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "dijkstra.hpp"

#define INF = (1<<20)
#define pii std::pair< Coord, int >

Dijkstra::Dijkstra(){
    
}

int Dijkstra::findSmallestDist(std::vector<Coord> coords){
    int index = 0;
    for(int i = 0 ; i < coords.size() ; ++i){
        if(coords[i].w < calculateDistance(coords[i], dest)){
            smallest = coords[i].w;
            index = i;
        }
    }
    return index;
}

std::vector<Coord> * Dijkstra::GetNeighbours(Coord current, std::vector< std::vector<int> > maze_vector) {
    std::vector<Coord> * neighbours = new std::vector<Coord>();
    Coord neighbour1 = current;
    neighbour1.x -=1;
    if(neighbour1.x >= 0 && ((maze_vector[(int) neighbour1.x][(int) neighbour1.y] == 0)||(maze_vector[(int) neighbour1.x][(int) neighbour1.y] == 3))){
        neighbours->push_back(neighbour1);
    }
    
    Coord neighbour2 = current;
    neighbour2.x +=1;
    
    if((neighbour2.x < maze_vector.size()) && ((maze_vector[(int) neighbour2.x][(int) neighbour2.y] == 0)||(maze_vector[(int) neighbour2.x][(int) neighbour2.y] == 3))){
        neighbours->push_back(neighbour2);
    }
    
    Coord neighbour3 = current;
    neighbour3.y -=1;
    
    if(neighbour3.y >= 0 && ((maze_vector[(int) neighbour3.x][(int) neighbour3.y] == 0)||(maze_vector[(int) neighbour3.x][(int) neighbour3.y] == 3))){
        neighbours->push_back(neighbour3);
    }
    
    Coord neighbour4 = current;
    neighbour4.y +=1;
    if(neighbour4.y < maze_vector[0].size() && ((maze_vector[(int) neighbour4.x][(int) neighbour4.y] == 0)||(maze_vector[(int) neighbour4.x][(int) neighbour4.y] ==3))){
        neighbours->push_back(neighbour4);
    }
    
    
    return neighbours;
}

double Dijkstra::calculateDistance(Coord start, Coord end){
    return sqrt(pow(start.x-end.x,2.0) + pow(start.y-end.y,2.0));
    //return start.dst(end);
}


struct comp {
    bool operator() (const pii &a, const pii &b) {
        return a.second > b.second;
    }
};

std::vector<Coord> Dijkstra::getShortestPath(std::vector< std::vector< int > > maze, Coord start, Coord end, std::vector<int> dist){
    std::vector<Coord> path;
    int smallest_dist = (1<<20)+1;
    Coord next = end;
    path.push_back(end);
    while(!next.equals(start)){
        std::vector<Coord> *neighbours = GetNeighbours(next, maze);
        
        for( int i = 0 ; i < neighbours->size() ; ++i){
            int nui = (int)((neighbours->at(i).y*maze.size())+neighbours->at(i).x);
            if(dist.at(nui) < smallest_dist){
                smallest_dist = dist.at(nui);
                next = neighbours->at(i);
            }
        }
        if(find(path.begin(), path.end(), next) == path.end()){
            path.push_back(next);
        }
        //std::cout << "adding: (" << next.x << "," << next.y << ") to path" << std::endl;
    }
    
    return path;
}


void Dijkstra::PrintOut(std::vector< std::vector< int > > maze_vector, std::vector<int> dist){
    for(int i = 0 ; i < maze_vector.size() ; ++i){
        std::cout << "[";
        for(int j = 0 ; j < maze_vector[i].size() ; ++j){
            if(maze_vector[j][i] == 0){
                int distance = dist[(j*maze_vector.size())+i];
                if(distance < 10)
                    std::cout << " " << distance;
                else
                    std::cout << distance;
            }
            else if (maze_vector[j][i] == 2)
                std::cout << "SS";
            else if (maze_vector[j][i] == 3)
                std::cout << "EE";
            else
                std::cout << "██";
        }
        std::cout << "]" << std::endl;
    }
}

std::vector<Coord> Dijkstra::calculatePath(Coord start, Coord end, std::vector< std::vector<int> > maze) {
    std::priority_queue<pii, std::vector<pii>, comp> unvisitedq;
    std::vector< pii > unvisited[10001];
    std::vector<int> dist;
    bool f[10001];
    
    for(int i = 0 ; i < maze.size() ; ++i){
        for( int j = 0 ; j < maze[i].size() ; ++j) {
            // for each node
            // get valid neighbours
            // push valid edges onto unvisited
            Coord current = *new Coord((double)i, (double)j);
            std::vector<Coord> neighbours = *GetNeighbours(current, maze);
            dist.push_back(1<<20);
            for(int i = 0 ; i < neighbours.size() ; ++i){
                //connect current to neighbour and neighbour to current
                unvisited[(int)((j*maze.size())+i)].push_back(std::make_pair(neighbours[i],1));
                unvisited[(int)((neighbours[i].y*maze.size())+neighbours[i].x)].push_back(std::make_pair(current,1));
            }
        }
    }
    
    dist.at((int)((start.y*maze.size())+start.x)) = 0;
    
    unvisitedq.push(pii(start,0));
    
    while(!unvisitedq.empty()){
        Coord u = unvisitedq.top().first;
        unvisitedq.pop();
        int ui = (int)((u.y*maze.size())+u.x);
        if(f[ui]) continue;
        
        unsigned long size = unvisited[ui].size();
        for(int i = 0 ; i < size ; ++i){
            Coord v = unvisited[ui][i].first;
            int w = unvisited[ui][i].second;
            int vi =(int)((v.y*maze.size())+v.x);
            std::cout << dist.at(ui)+w << " " << dist.at(vi) << std::endl;
            if(!f[vi] && (dist.at(ui)+w < dist.at(vi))) {
                dist.at(vi) = dist.at(ui) + w;
                std::cout << "dist " << dist.at(ui) + w << std::endl;
                unvisitedq.push(pii(v, dist.at(vi)));
            }
        }
        f[ui] = 1;
    }
    
    PrintOut(maze, dist);
    /*for( int i = 0 ; i < dist.size() ; ++i){
        std::cout << dist[i] << std::endl;
    }
    */
    //*dest = end;
    //int dest_index = (int)((end.x*maze.size())+end.y);
    
    
    /*dest = end;
    //std::vector<int> dist;
    std::vector<Coord> visited;
    
    
    //dist[(start.x*maze.size())+start.y] = 0;
    while(!unvisited.empty()){
        int u = findSmallestDist(unvisited);
        Coord uc = unvisited[u];
        //int distu = dist[u];
        
        if(uc.equals(end)){
            visited.push_back(uc);
            break;
        }
        
        //dist.erase(dist.begin()+u-1);
        unvisited.erase(unvisited.begin()+u-1);
        
        std::vector<Coord> neighbours = GetNeighbours(uc, maze);
        for(int v = 0 ; v < neighbours.size() ; ++v){
            int alt = uc.w + calculateDistance(neighbours[v], uc);
            if( alt < neighbours[v].w){
                Coord * working = &unvisited[(neighbours[v].x*unvisited.size())+neighbours[v].y];
                working->w = alt;
                visited.push_back(uc);
                std::cout << "visited: (" << uc.x << "," << uc.y << ")" << std::endl;
            }
        }
    }
    */
    
    std::vector<Coord> path;
    return getShortestPath(maze, start, end, dist);
}


