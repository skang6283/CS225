/* Your code here! */
#include "maze.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>
#include <cmath>

// SquareMaze::SquareMaze(){

// }

void SquareMaze::makeMaze(int width, int height){
	maze_w = width;
	maze_h = height;

	int size = maze_w * maze_h;
	maze.addelements(size);
	//You only need to store 2 bits per square: 
	//the "down" and "right" walls. The finished maze is always a tree of corridors.)

	right = new bool[size];
	down = new bool[size];

	for(int i = 0; i < size ; i++){
		right[i] = true;
	 	down[i] = true;
	}


	int idx, idx_next;
	while(maze.size(0) < size){
		//srand(time(NULL));
		int random = rand() % size;
		int right_down = rand() %2;
		
		//std::cout<<random<<right_down<<std::endl;
		if(right_down == 1){
			if((random + 1) % width != 0){					//right
				//std::cout<<"check loop11"<<std::endl;
				
				//std::cout<<random<<std::endl;	
				
				idx = maze.find(random);
				idx_next = maze.find(random +1);
				if(idx != idx_next){
					right[random] = false;	
					maze.setunion(random, random + 1);
				}
			}
		}else {
			if(random < (maze_w * (maze_h-1))){			//down
				//std::cout<<"check loop22"<<std::endl;
		
				idx = maze.find(random);
				idx_next = maze.find(random + maze_w);
				if(idx != idx_next){
					down[random] = false;
					maze.setunion(random, random + maze_w);
				}
			}
		}	
		
	}

}

bool SquareMaze::canTravel(int x, int y, int dir) const{
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

	int location  = maze_w * y + x;
	//edge cases



	if(dir == 0){
		if(x == (maze_w -1)){
			return false;
		}else{
			return !right[location];
		}	
	}

	if(dir == 1){
		if(y == (maze_h-1)){
			return false;
		}else {
			return !down[location];
		}
	}


	if(dir == 2){
		if(x == 0){
			return false;
		}else {
			return !right[location-1];
		}
	}

	if(dir == 3){
		if(y == 0){
			return false;
		}else {
			return !down[location-maze_w];
		}
	}

	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int location = y* maze_w + x;
	if(dir == 0){
		right[location] = exists;
	}else if(dir == 1){
		down[location] = exists;
	}
}


std::vector<int> SquareMaze::solveMaze(){
	//shortest path algorithm

	//start from the source cell and calls BFS procedure.
	std::vector<int> prev; // for keeping path
	//std::vector<int> destinations; //last row
	std::vector<bool> visited;	
	std::vector<int> distance;

	//initialize visited to false 
	//initialize path to null(-1)
	//initiliaze distance
	for(int i =0 ; i< maze_w * maze_h; i++){
		visited.push_back(false);
		prev.push_back(-1);
		distance.push_back(0);
	}


	//maintain a queue to store the coordinates of the matrix and initialize it with the source cell
	std::queue<int> coordinates;
	coordinates.push(0);
	visited[0] = true;



	int current_x, current_y, next;

	//loop till queue is not empty
	while(!coordinates.empty()){
	//Dequeue front cell from the queue
		int next = coordinates.front();
		coordinates.pop();

		current_x = next % maze_w;
		current_y = next / maze_w;

	//if the destination coordinates have reached. stores them
		// if(cur_y == maze_h -1){
		// 	destinations.push_back(next);
		// }	

	//For each of its four adjacent cells, 
	//if the value is 1 and they are not visited yet, 
	//we enqueue it in the queue and also mark them as visited.
		if(canTravel(current_x, current_y, 0) && visited[next + 1] == false){	//right
			coordinates.push(next+1);
			visited[next + 1] = true;
			prev[next+1] = next;
			distance[next+1] = distance[next]+1;

		}
		if(canTravel(current_x, current_y, 1) && visited[next + maze_w] == false){	//down
			coordinates.push(next + maze_w);
			visited[next + maze_w] = true;
			prev[next+maze_w] = next;
			distance[next+maze_w] = distance[next] + 1;
		}
		if(canTravel(current_x, current_y, 2) && visited[next - 1] == false){ //left
			coordinates.push(next - 1);
			visited[next - 1] = true;
			prev[next-1] = next;
			distance[next-1] = distance[next] + 1;
		}
		if(canTravel(current_x, current_y, 3) && visited[next - maze_w] == false){ //up

			coordinates.push(next - maze_w);
			visited[next - maze_w] = true;
			prev[next - maze_w] = next;
			distance[next-maze_w]= distance[next] + 1;
		}
	}

	//the real destination
	int tmp_idx = maze_w * (maze_h-1) ;
	int longest = distance[tmp_idx];
	int final_idx = tmp_idx;

	for(int i = 0; i < maze_w ; i++){

		if(longest < distance[tmp_idx+i]){
			final_idx = tmp_idx+i;
			longest = distance[tmp_idx+i];	
		}
	}
 

	std::vector<int> path; 
	
	while(longest != 0){ 	//counter
		if(prev[final_idx] == final_idx - 1){ // right
			path.push_back(0);
		} if(prev[final_idx] == final_idx - maze_w){ // down
			path.push_back(1);
		} if(prev[final_idx] == final_idx + 1 ){	//left
			path.push_back(2);
		} if(prev[final_idx] == final_idx + maze_w){	//up
			path.push_back(3);
		}
		final_idx = prev[final_idx];
		//std::cout<<final_idx<<std::endl;
		//std::cout<<longest<<std::endl;

		longest--;
	}

	reverse(path.begin(), path.end());
	return path;

}



cs225::PNG* SquareMaze::drawMaze() const{

	cs225::PNG* grid = new cs225::PNG(maze_w*10+1,maze_h*10+1);
	for(int i = 0 ; i < maze_h*10+1 ; i++){
		cs225::HSLAPixel& pixel = grid->getPixel(0,i);
		pixel.h = 0;
		pixel.s = 0;
		pixel.l = 0;
	}

	for(int i = 10 ; i < maze_w*10+1 ; i++){
		cs225::HSLAPixel& pixel = grid->getPixel(i,0);
		pixel.h = 0;
		pixel.s = 0;
		pixel.l = 0;
	}

//  ((x+1)*10,y*10+k) for k from 0 to 10 right
//	(x*10+k, (y+1)*10) for k from 0 to 10	//down
	int x, y;
	int size = maze_w * maze_h;
	for(int i =0; i < size ; i++){
		x = i % maze_w;
		y = i / maze_w;

		if(right[i] == true){
			for(int k = 0; k <= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel((x+1)*10,y*10+k);
				pixel.h = 0;
				pixel.s = 0;
				pixel.l = 0;
			}
		}
		if(down[i] == true){
			for(int k = 0; k<=10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y+1)*10);
				pixel.h = 0;
				pixel.s = 0;
				pixel.l = 0;
			}
		}	
	}

	return grid;

}


cs225::PNG* SquareMaze::drawMazeWithSolution(){
	
	cs225::PNG* grid_solved = drawMaze();

	std::vector<int> solution = solveMaze();

//Start at pixel (5,5).
	int x = 5;
	int y = 5;
	int k;

	int real_x =0;
	int real_y =0;
	for(unsigned int i=0; i< solution.size() ; i++){
		//int k;
		//std::cout<<x<<","<<y<<std::endl;
		if(solution[i] == 0) {		//right
			for( k =0; k <= 10; k++){ 	
				cs225::HSLAPixel& pixel = grid_solved->getPixel(x+k,y);	
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			x = x+k-1;
			real_x++;
		}
		if(solution[i] == 1) {		//down
			for( k =0; k <= 10; k++){
				cs225::HSLAPixel& pixel = grid_solved->getPixel(x,y+k);	
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			y=y+k-1;
			real_y++;
		}
		if(solution[i] == 2) {		//left
			for( k =0; k <= 10; k++){
				cs225::HSLAPixel& pixel = grid_solved->getPixel(x-k,y);	
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			x=x-k+1;
			real_x--;
		}	
		if(solution[i] == 3) {		//up
			for( k =0; k <= 10; k++){
				cs225::HSLAPixel& pixel = grid_solved->getPixel(x,y-k);	
				pixel.h = 0;
				pixel.s = 1;
				pixel.l = 0.5;
				pixel.a = 1;
			}
			y=y-k+1;
			real_y--;
		}
	}

	for( k =1; k<10;k++){
		cs225::HSLAPixel& pixel = grid_solved->getPixel(real_x*10+k, (real_y+1)*10);
		pixel.h = 360;
		pixel.s = 1;
		pixel.l = 1;
		pixel.a = 1;
	}


	return grid_solved;
}


cs225::PNG* SquareMaze::drawCreativeMaze(){

	cs225::PNG* grid = new cs225::PNG(maze_w*10+1,maze_h*10+1);
	for(int i = 0 ; i < maze_h*10+1 ; i++){
		cs225::HSLAPixel& pixel = grid->getPixel(0,i);
		//cs225::HSLAPixel& pixel3 = grid->getPixel((maze_h*10+1)/3,(maze_h*10+1)/3+i/3);
		//cs225::HSLAPixel& pixel4 = grid->getPixel((maze_h*10+1)*2/3,(maze_h*10+1)/3+i/3);

		pixel.l = 0;
		//pixel2.l = 0;
		//pixel3.l = 0;
		//pixel4.l = 0;
			
	}

	for(int i = 0 ; i < maze_w*10+1 ; i++){
		cs225::HSLAPixel& pixel = grid->getPixel(i,0);
		//cs225::HSLAPixel& pixel3 = grid->getPixel((maze_h*10+1)/3+i/3,(maze_h*10+1)/3);
		//cs225::HSLAPixel& pixel4 = grid->getPixel((maze_h*10+1)/3+i/3,(maze_h*10+1)*2/3);

		
		pixel.l = 0;
		//pixel2.l = 0;
		//pixel3.l = 0;
		//pixel4.l = 0;
		
	}

	

	int x, y;
	int size = maze_w *maze_h;
	for(int i =0; i < size/3 ; i++){
		x = i % maze_w;
		y = i / maze_w;

		if(right[i] == true){
			for(int k = 0; k <= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel((x+1)*10,y*10+k);
				pixel.l = 0;
			}
		}
		if(down[i] == true){
			for(int k = 0; k<= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y+1)*10);
				pixel.l = 0;
			}
		}
		if(( x >= (maze_w/3) && x <= (maze_w/3)*2 ) && y == maze_h/3){
			for(int k = 0; k<= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y+1)*10);
				pixel.l = 0;
			}
		}	
	
	}


for(int i =size/3; i < size/3*2 ; i++){
		x = i % maze_w;
		y = i / maze_w;

		if(right[i] == true && ( x < (maze_w/3) || x> (maze_w/3)*2 )){
			for(int k = 0; k <= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel((x+1)*10,y*10+k);
				pixel.h = 0;
				pixel.s = 0;
				pixel.l = 0;
			}
		}
		if(down[i] == true && ( x < (maze_w/3) || x > (maze_w/3)*2 )) {
			for(int k = 0; k<= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y+1)*10);
				pixel.h = 0;
				pixel.s = 0;
				pixel.l = 0;
			}
		}	
		if(( x == (maze_w/3)-1 || x== (maze_w/3)*2 ) ){
			for(int k = 0; k <= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel((x+1)*10,y*10+k);
				pixel.h = 0;
				pixel.s = 0;
				pixel.l = 0;
			}
		}


	}	


	for(int i =size/3*2; i < size ; i++){
		x = i % maze_w;
		y = i / maze_w;

		if(right[i] == true){
			for(int k = 0; k <= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel((x+1)*10,y*10+k);
				pixel.l = 0;
			}
		}
		if(down[i] == true){
			for(int k = 0; k<= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y+1)*10);
				pixel.l = 0;
			}
		}	

		if(( x >= (maze_w/3) && x<= (maze_w/3)*2 ) && y <= (maze_h/3*2)+1 ){
			for(int k = 0; k<= 10 ; k++){
				cs225::HSLAPixel& pixel = grid->getPixel(x*10+k, (y)*10);
				pixel.l = 0;
			}
		}

	}


	return grid;
}	
