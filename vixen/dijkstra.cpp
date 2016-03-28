//
//  dijkstra.cpp
//  vixen
//
//  Created by Jamie Flint on 28/03/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "dijkstra.hpp"
// given adjacency matrix adj, finds shortest path from A to B
int dijkstra(int A, int B, std::vector< std::vector<int> > maze) {
    int inf = 1 << 30;
    int n = (int)maze.size();
    std::vector<int> distance(n);
    std::vector<bool> visited(n);
    
    for(int i = 0; i < n; ++i) {
        distance[i] = inf;
    }
    distance[A] = 0;
    
    for(int i = 0; i < n; ++i) {
        int cur = -1;
        for(int j = 0; j < n; ++j) {
            if (visited[j]) continue;
            if (cur == -1 || distance[j] < distance[cur]) {
                cur = j;
            }
        }
        
        visited[cur] = true;
        for(int j = 0; j < n; ++j) {
            int path = distance[cur] + maze[cur][j];
            if (path < distance[j]) {
                distance[j] = path;
            }
        }
    }
    
    return distance[B];
}