
//
//  maze.cpp
//  vixen
//
//  Created by Jamie Flint on 21/02/2016.
//  Copyright © 2016 Jamie Flint. All rights reserved.
//

#include "maze.hpp"

Maze::Maze(int width, int height){
	this->width = width;
	this->height = height;
	this->maze_vector = std::vector< std::vector<int> >(width+1, std::vector<int>(height+1,1));
    this->mazeSurface = SDL_LoadBMP("/Users/lutzee/Dropbox/Uni/vixen/vixen/images/wall.bmp");
}

int Maze::Id(int x, int y){
	return y*(width+1)+x;
}

int Maze::X(int i) {
    return i % (width + 1);
}

int Maze::Y(int i) {
    return floor(i / (width + 1));
}

// Third attempt at Maze generation, this time using Prim's Algorithm, this one works
void Maze::GenerateThree(){
    std::vector<Coord> frontier;
    
    start = *new Coord(1,1,NULL);
    maze_vector[start.x][start.y] = 2;
    for(int x = -1 ; x <= 1 ; ++x){
        for(int y = -1 ; y <= 1 ; ++y){
            if( (x == 0 && y == 0) || (x != 0 && y != 0)){
                continue;
            }
            try{
                if(maze_vector.at(start.x+x).at(start.y+y)==0)
                    continue;
            }
            catch(const std::out_of_range e){ // ignore ArrayIndexOutOfBounds
                continue;
            }
            frontier.push_back(*new Coord(start.x+x,start.y+y,&start));
        }
    }
    //Coord * last = nullptr;
    
    while(!frontier.empty()){
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, (int)frontier.size()-1);
        int rand = dist(mt);
        Coord current = frontier.at(rand);
        frontier.erase(frontier.begin()+(rand));
        Coord * opposite = Coord::Opposite(current);

        try {
            if(opposite == NULL){
                continue;
            }
            if(maze_vector[current.x][current.y] == 1){
                if(maze_vector.at(opposite->x).at(opposite->y) == 1){
                    maze_vector.at(current.x).at(current.y) = 0;
                    maze_vector.at(opposite->x).at(opposite->y) = 0;
                    
                    //last = opposite;
                    
                    for(int x=-1;x<=1;x++){
                        for(int y=-1;y<=1;y++){
                            if((x==0&&y==0)||(x!=0&&y!=0))
                                continue;
                            try{
                                if(maze_vector.at(opposite->x+x).at(opposite->y+y)== 0)
                                    continue;
                            } catch(const std::out_of_range e){
                                continue;
                            }
                            frontier.push_back(*new Coord(opposite->x+x,opposite->y+y,opposite));
                        }
                    }
                }
            }
        }
        catch(const std::exception e){
            
        }
        
        if(frontier.empty()){
            maze_vector[39][39]=3;
            end = *new Coord(39, 39);
        }
        int maze_size = (int)maze_vector.size();
    
        for(int x = 0 ; x < maze_size ; ++x){
            int val = maze_vector[x][0];
            if(val==2 || val==3)
                continue;
            maze_vector.at(x).at(0) = 1;
        }
        for(int x = 0 ; x < maze_size ; ++x){
            int val = maze_vector[x][maze_size-1];
            if(val==2 || val==3)
                continue;
            maze_vector.at(x).at(maze_size-1) = 1;
        }
        for(int x = 0 ; x < maze_size ; ++x){
            int val =maze_vector[0][x];
            if(val==2 || val==3)
                continue;
            maze_vector.at(0).at(x)=1;
        }
        for(int x = 0 ; x < maze_size ; ++x){
            int val = maze_vector[maze_size-1][x];
            if(val==2 || val==3)
                continue;
            maze_vector.at(maze_size-1).at(x)=1;
        }
    }
}

// Second attempt at generating mazes, this was an attempt to replicate the maze
// generation from the minecraft tool worldedit, this failed misserably
void Maze::GenerateTwo(){
	std::random_device rd;
	std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);
	std::stack<int> stack;
	std::vector<int> visited;
	
	std::vector<int> *noWallLeft = new std::vector<int>((width+1)*(height+1), 0);
	std::vector<int> *noWallAbove = new std::vector<int>((width+1)*(height+1), 0);
	//stack.push(Id(floor(dist(mt)*width), floor(dist(mt)*height)));
	stack.push(Id(46,46));
	
	while(stack.size() > 0){
		int cell = stack.top();
		stack.pop();
		int x = X(cell);
		int y = Y(cell); 
		visited.push_back(cell);
		std::vector<int> neighbours;
		if(x>0){
			neighbours.push_back(Id(x-1,y));
		}
		if (x < width - 1) {
			neighbours.push_back(Id(x + 1, y));
		}
	    if (y > 0) {
			neighbours.push_back(Id(x, y - 1));
		}
    	if (y < height - 1) {
			neighbours.push_back(Id(x, y + 1));
		}
		
		std::random_shuffle(neighbours.begin(), neighbours.end());
		
		while(neighbours.size() > 0){
			std::cout << "neighbours bigger than 0: " << neighbours.size() << std::endl;
			int neighbour = neighbours.front();
			neighbours.erase(neighbours.end()-1);
			int nx = X(neighbour);
			int ny = Y(neighbour);
			
			if(!visited[neighbour]){
				stack.push(cell);
				
				if(y == ny){
					if(nx < x) {
						std::cout << "setting cell " << cell  << std::endl;
						noWallLeft->at(cell) = 1;
					} else {
						std::cout << "setting neighbour " << neighbour  << std::endl;
						noWallLeft->at(neighbour) = 1;
					}
				} else {
					if(ny < y){
						std::cout << "setting cell " << cell  << std::endl;
						noWallAbove->at(cell) = 1;
					} else {
						std::cout << "setting neighbour " << neighbour  << std::endl;
						noWallAbove->at(neighbour) = 1;
					}
				}
				
				stack.push(neighbour);
				break;
			}
		}
	}
	
	std::cout << "w: " << width << " h: " << height  << std::endl;
	
	for( int i = 0 ; i < noWallLeft->size() ; ++i){
		std::cout << noWallLeft->at(i) << ",";
	}
	std::cout << std::endl;
	
	for( int i = 0 ; i < noWallAbove->size() ; ++i){
		std::cout << noWallAbove->at(i) << ",";
	}
	std::cout << std::endl;
	
	for(int y = 0; y < height; ++y){			
		for(int x = 0; x < width ; ++x){
			int cell = Id(x, y);
						
			if(noWallLeft->at(cell) == 0 && cell != Id(x, height)){
				maze_vector[x][y] = 0;
			}
			if(noWallAbove->at(cell) == 0 && cell != Id(width, y)){
				maze_vector[x][y] = 0;
			}
			
			
			//if(cell != Id(x, height) && cell != Id(width, y)){
			//	maze_vector[x][y] = 1;
			//}
		}
	}
}

// First attempt at maze generation using recursive backstepping, lots of samey areas generated in the maze

void Maze::GenerateOne(){
	printf("maze generating\n");
	
	std::random_device rd;
	std::mt19937 mt(rd());
	
	int posX = 0;
	int posY = 0;
	std::queue<int> moves;
	moves.push(posY+(posX*width));
	int loops = 0;
	while(true){
		loops++;
		if(moves.size() != 0){
			std::vector<direction> possibleDirections;
			if(posX + 2 > 0 && posX + 2 < height -1 && maze_vector[posX + 2][posY] == 1){
				possibleDirections.push_back(south);
			}
			if(posX - 2 > 0 && posX - 2 < height -1 && maze_vector[posX - 2][posY] == 1){
				possibleDirections.push_back(north);
			}
			if(posY - 2 > 0 && posY - 2 < width -1 && maze_vector[posX][posY - 2] == 1){
				possibleDirections.push_back(west);
			}
			if(posY + 2 > 0 && posY + 2 < width -1 && maze_vector[posX][posY + 2] == 1){
				possibleDirections.push_back(east);
			}
			if(possibleDirections.size() != 0){
				std::uniform_int_distribution<int> dist(0, (int)possibleDirections.size()-1);
				int move = dist(mt);
				
				switch(possibleDirections[move]){
					case north:
						maze_vector[posX - 2][posY] = 0;
						maze_vector[posX - 1][posY] = 0;
						posX -= 2;
					case south:
						maze_vector[posX + 2][posY] = 0;
						maze_vector[posX + 1][posY] = 0;
						posX += 2;
						break;
					case west:
						maze_vector[posX][posY - 2] = 0;
						maze_vector[posX][posY - 1] = 0;
						posY -= 2;
						break;
					case east:
						maze_vector[posX][posY + 2] = 0;
						maze_vector[posX][posY + 1] = 0;
						posY += 2;
						break;         
				}
				moves.push(posY + (posX*width));
			}
			else{
				int back = moves.front();
				moves.pop();
				posX = floor(back/width);
				posY = back % width;
			}
		}
		if(loops == 1000000){
			break;
		}
	}
}

void Maze::PrintOut(){
	for(int i = 0 ; i < maze_vector.size() ; ++i){
		std::cout << "[";
		for(int j = 0 ; j < maze_vector[i].size() ; ++j){
			if(maze_vector[j][i] == 0)
				std::cout << "  ";
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

void Maze::render(SDL_Renderer * r){
    SDL_Texture *maze = SDL_CreateTextureFromSurface(r, mazeSurface);
    
    for(int x = 0 ; x < maze_vector.size() ; ++x){
        for(int y = 0 ; y < maze_vector[x].size() ; ++y){
            if(maze_vector[x][y] == 1){
                SDL_Rect texture_rect;
                texture_rect.x = x*20;
                texture_rect.y = y*20;
                texture_rect.w = 20;
                texture_rect.h = 20;
                SDL_RenderCopy(r, maze, NULL, &texture_rect);
            }
        }
    }
    
    SDL_RenderPresent(r); //updates the renderer
    
}