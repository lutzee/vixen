//
//  world.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "world.hpp"

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

World::World()
{

}

void World::close()
{
    sqlite3_close(db);
}

int World::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    
    this->pathSurface = SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/path.bmp");

    
    rc = sqlite3_open("/Users/lutzee/dissertation.db", &db);
    if(rc)
    {
        std::cout << "Can't open db" << std::endl;
        sqlite3_close(db);
        return 1;
    }
    
    rc = sqlite3_exec(db, "drop table results;", callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, "create table results (resulttype text, resulttime INT8, series integer);", callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, "drop table iterations;", callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, "create table iterations (resulttype text, iterations INT8, series integer);", callback, 0, &zErrMsg);
    
    renderPath(renderer, path);
    //delete n;
    
    return 0;
}

void World::GenerateMaze(int series)
{
    Maze maze = Maze(40,40);
    Astar astar = Astar(renderer);
    Dijkstra dj = Dijkstra();
    Wallfollow wf = Wallfollow();
    Natural n = Natural(renderer);
    
    maze.GenerateThree();
    //std::cout<<"Maze generated" << std::endl;
    //maze.PrintOut();
    /*
    auto begin = std::chrono::high_resolution_clock::now();
    path = astar.CreatePath(maze.start, maze.end, maze.maze_vector);
        
    auto end = std::chrono::high_resolution_clock::now();
    
    auto atime = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    std::cout << "A* took: " << atime << "us" << std::endl;

    std::stringstream ass;
    
    ass << "insert into results (resulttype, resulttime,series) values ('astar', " << atime << "," << series << ");";
    auto astr = ass.str();
    rc = sqlite3_exec(db, astr.c_str() , callback, 0, &zErrMsg);
    //fprintf(stderr, "SQL error: %s\n", zErrMsg);
    begin = std::chrono::high_resolution_clock::now();
        
    path = dj.calculatePath(maze.start, maze.end, maze.maze_vector);
        
    end = std::chrono::high_resolution_clock::now();
    auto dtime = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();

    std::cout << "Dijkstra took: " << dtime << "us" << std::endl;
    std::stringstream dss;
    
    dss << "insert into results (resulttype, resulttime, series) values ('dijkstra', " << dtime << "," << series << ");";

    auto dstr = dss.str();
    rc = sqlite3_exec(db, dstr.c_str() , callback, 0, &zErrMsg);
     */
    auto begin = std::chrono::high_resolution_clock::now();
        
    path = wf.calculatePath(maze.maze_vector, maze.start, maze.end, db, series);
        
    auto end = std::chrono::high_resolution_clock::now();
    auto wtime = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();

    std::cout << "Wall Follow took: " << wtime << "us" << std::endl;
    std::stringstream wss;
    
    wss << "insert into results (resulttype, resulttime, series) values ('wallfolllow', " << wtime << "," << series << ");";
    
    auto wstr = wss.str();
    rc = sqlite3_exec(db, wstr.c_str() , callback, 0, &zErrMsg);

        
    begin = std::chrono::high_resolution_clock::now();
        
    path = n.calculatePath(maze.maze_vector, maze.start, maze.end, db, series);
        
    end = std::chrono::high_resolution_clock::now();
    auto ntime = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();

    std::cout << "Natural took: " << ntime << "us" << std::endl;
    std::stringstream nss;
    
    nss << "insert into results (resulttype, resulttime, series) values ('natural', " << ntime << "," << series << ");";
    
    auto nstr = nss.str();
    rc = sqlite3_exec(db, nstr.c_str() , callback, 0, &zErrMsg);
    //maze.render(renderer);
    //renderPath(renderer, path);
}

void World::renderPath(SDL_Renderer *renderer, std::vector<Coord> path)
{
    SDL_Texture *pathTex = SDL_CreateTextureFromSurface(renderer, pathSurface);
    
    for(auto &path : path){
        SDL_Rect texture_rect;
        texture_rect.x = path.x*20;
        texture_rect.y = path.y*20;
        texture_rect.w = 20;
        texture_rect.h = 20;
        SDL_RenderCopy(renderer, pathTex, NULL, &texture_rect);
    }
    
    SDL_RenderPresent(renderer); //updates the renderer
}

void World::loop()
{
    //maze.render(renderer);
    
    for ( Player &p : playerList )
    {
        // Update player
        p.update();
        
        // Render Player
        p.render(renderer);
        
        // Check win condition
    }
}

