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

Dijkstra::Dijkstra()
{
    
}

std::vector<Coord> Dijkstra::GetNeighbours(Coord current, std::vector< std::vector<int> > maze_vector)
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

double Dijkstra::calculateDistance(Coord start, Coord end)
{
    return sqrt(pow(start.x-end.x,2.0) + pow(start.y-end.y,2.0));
}


struct comp
{
    bool operator() (const pii &a, const pii &b)
    {
        return a.second > b.second;
    }
};

std::vector<Coord> Dijkstra::getShortestPath(std::vector< std::vector< int > > maze_vector, Coord start, Coord end, std::vector<int> dist)
{
    std::vector<Coord> path;
    int smallest_dist = (1<<20)+1;
    Coord next = end;
    path.push_back(end);
    while(!next.equals(start))
    {
        std::vector<Coord> neighbours = GetNeighbours(next, maze_vector);
        for( int i = 0 ; i < neighbours.size() ; ++i)
        {
            int nui = (int)((neighbours.at(i).x*maze_vector.size())+neighbours.at(i).y);
            if(dist.at(nui) < smallest_dist)
            {
                smallest_dist = dist.at(nui);
                next = neighbours.at(i);
            }
        }
        if(find(path.begin(), path.end(), next) == path.end())
        {
            path.push_back(next);
        }
    }
    
    return path;
}


void Dijkstra::PrintOut(std::vector< std::vector< int > > maze_vector, std::vector<int> dist)
{
    for(int i = 0 ; i < maze_vector.size() ; ++i)
    {
        std::cout << "[";
        for(int j = 0 ; j < maze_vector[i].size() ; ++j)
        {
            if(maze_vector[j][i] == 0)
            {
                int distance = dist[(j*maze_vector.size())+i];
                if(distance < 10)
                    std::cout << " " << distance;
                else if(distance == 1048576)
                    std::cout << "##";
                else
                    std::cout << distance;
            }
            else if (maze_vector[j][i] == 2)
                std::cout << "SS";
            else if (maze_vector[j][i] == 3)
                std::cout << "EE";
            else
            {
                std::cout << "██";
            }
        }
        std::cout << "]" << std::endl;
    }
}

std::vector<Coord> Dijkstra::calculatePath(Coord start, Coord end, std::vector< std::vector<int> > maze_vector)
{
    //this->maze_vector = maze;
    std::priority_queue<pii, std::vector<pii>, comp> unvisitedq;
    std::vector< pii > unvisited[10001];
    std::vector<int> dist;
    std::vector<bool> f(10001,false);
    
    for(int i = 0 ; i < maze_vector.size() ; ++i)
    {
        for( int j = 0 ; j < maze_vector[i].size() ; ++j)
        {
            Coord current = Coord((double)i, (double)j);
            dist.push_back(1<<20);
            if(maze_vector[j][i] == 1)
            {
                continue;
            }
            std::vector<Coord> neighbours = GetNeighbours(current, maze_vector);
            for(int k = 0 ; k < neighbours.size() ; ++k)
            {
                if(maze_vector[neighbours[k].y][neighbours[k].x] == 1)
                {
                    continue;
                }
                auto npair = std::make_pair(neighbours[k],1);
                int uvi =(int)((j*maze_vector.size())+i);
                if(find(unvisited[uvi].begin(), unvisited[uvi].end(), npair) == unvisited[uvi].end())
                {
                    unvisited[uvi].push_back(npair);
                }
                auto cpair = std::make_pair(current,1);
                int nvi = (int)((neighbours[k].y*maze_vector.size())+neighbours[k].x);
                if(find(unvisited[nvi].begin(), unvisited[nvi].end(), cpair) == unvisited[nvi].end())
                {
                    unvisited[nvi].push_back(cpair);
                }
            }
        }
    }

    dist.at((int)((start.y*maze_vector.size())+start.x)) = 0;
    
    unvisitedq.push(pii(start,0));
    
    while(!unvisitedq.empty())
    {
        Coord u = unvisitedq.top().first;
        unvisitedq.pop();
        int ui = (int)((u.y*maze_vector.size())+u.x);
        if(f[ui]) continue;
        
        unsigned long size = unvisited[ui].size();
        for(int i = 0 ; i < size ; ++i)
        {
            Coord v = unvisited[ui][i].first;
            int w = unvisited[ui][i].second;
            int vi =(int)((v.y*maze_vector.size())+v.x);
            if(!f[vi] && (dist.at(ui)+w < dist.at(vi)))
            {
                dist.at(vi) = dist.at(ui) + w;
                unvisitedq.push(pii(v, dist.at(vi)));
            }
        }
        f[ui] = 1;
    }
    
    std::vector<Coord> path;
    return getShortestPath(maze_vector, start, end, dist);
}


