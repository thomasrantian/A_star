#include <iostream>
using namespace std;
#include <vector>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <queue>

class node{
	public:
		int x; // index in the grid
		int y;

		int occupied_status; // occupied status;
		char symble; // . if the node is empty; # if the node is occupied

		double h; // heuristic cost
		double g; // moving cost
		double f;

		int isVisited; // if or not we visied this node before
		int isClosed; // if or not the node is been closed

		int x_pre;
		int y_pre;
		// constructor, assign x, y, set h, g to be zero by default
		node(int x_in, int y_in, int status_in) {
      x = x_in;
      y = y_in;
			occupied_status = status_in;
			h = 1000000; // h value:  h is the heuristic value
			g = 1000000; // g value: g cost, moving cost
			f = g + h; // f value: f = g + h, final cost
			isVisited = 0;
			isClosed = 0;
			x_pre = -1;
			y_pre = -1;

		}

	};

// occupency grid class contsins the
class OccupancyGrid {
public:
	int rows;
	int columns;
	vector< vector<node> > grid; // [[n1 n2 n3]] n1.x = 0; n1.y = 0;
	// constructor: assign the length and width of the grid
	OccupancyGrid(int rows_in, int columns_in ) {
		rows = rows_in;
		columns = columns_in;
		grid.reserve(rows);
	}

	// generate a test grid
	/*......
		..##..
		..##..
		..##..
		......
		......*/
	void generate_test_grid() {
		rows = 6;
		columns = 6;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < columns; j++){
				int a = 0;
				node temp = node(i,j,a);
				if (a == 0){
					temp.symble = '.';
				}else{
					temp.symble = '#';
				}
				grid[i].push_back(temp);
			}
		}

		for (int i = 1; i < 4; ++i) {
			for (int j = 2; j < 4; ++j ) {
				grid[i][j].occupied_status = 1;
				grid[i][j].symble = '#';
			}
		}
	}

	// randomly generating the grid, generare node fill the grid, note the symple of the node if it is occupied or empty
	void generate_grid() {
		default_random_engine generator;
		uniform_int_distribution<int> distribution(0,9);

		for (int i = 0; i < rows; i++){
			for (int j = 0; j < columns; j++){
				//int a = rand() % 2;
				int number = distribution(generator);
				int a = 0;
				if (number >8 || number <1) a = 1;
				node temp = node(i,j,a);
				if (a == 0){
					temp.symble = '.';
				}else{
					temp.symble = '#';
				}
				grid[i].push_back(temp);
			}
		}
	}

	// print the grid using the symble of the node : eg., ...###...
	void print_grid() {
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < columns; j++){
					cout << grid[i][j].symble;
				}
				cout << endl;
			}
 };
};
//
// we use a comparetor in order to use heap
class f_compare {
public:
	bool operator() (const node* a, const node* b){
	        return (a -> f)  >  (b -> f);
	    }
};

class A_star {
public:
  bool flag = false;
	OccupancyGrid* map; // note that we use a pointer to the built grid instead of  store a copy of the grid
	vector< node* > final_path; // final path from the start to the final node;

	priority_queue<node*, vector<node*>, f_compare> openSet; // openSet, store the nodes that  needed to be checked
	vector< node* > closeSet; // closeSet, store the checked node


	// constructor, assign the input OccupancyGrid pointer to the map
	A_star(OccupancyGrid* map_in) {
		map = map_in;
	}

	// input the pointer of the goal node and the current_node, return the h value
	double calculate_h (node* goal, node* current_node) {
			return sqrt(pow(goal -> x - current_node -> x, 2)+ pow(goal->y - current_node->y,2));
	}

	// main searching algorithm input: index of the start node and the goal node
	// Sudo code:
 // 1. From the input x_0 y_0 find the start node, insert the start node in
 //    the openSet to enter the loop note that we are using pointer

 // 2. while openSet is not empty
 //		1). make the openSet as a heap using the comparetor
 //        std:: make_heap(vector.begin(), vector.end(), f_compare())
 //		2). pop the the one with smallest f value as the current_node
 //		3). if the current node is final node, reconstruct path, break;
 //		4). change the status of the current (isClosed = 1)
 //  5). for all its neibors:
 //					a. if the neighbor is closed or it is occupied, skip this neighbot
 //					b. if the neighbor is not visited, update the neighbor's g, h,
 //             f, x_pre, y_pre and put the neighbor into the openSet

 //					c. if the  neighbor is visited (means the neighbor is already in the openser)
 //							c1. calculate its tententive g score, if new g is < than old g, update g,h,f,x_pre,y_re;

	void search(int start_x, int start_y, int goal_x, int goal_y) {
		// push the start node into the open set
		node* start_node = &(map -> grid[start_x][start_y]);
    node* goal_node = &(map -> grid[goal_x][goal_y]);
		openSet.push(start_node);
		int direction[][2] = {{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};
		while (!openSet.empty()){
			// get the current node from the openSet;
			 node* current_node = openSet.top();


			 // add the current node to the closeSet and set the current_node's isClosed status to be true
			 closeSet.push_back(current_node);
			 current_node -> isClosed = true;

			 // pop the current node from the openSet
 		 	 openSet.pop();
			 // if the current node is the goal node, break, construct the path
			 if ((current_node -> x == goal_x) && (current_node -> y == goal_y)) {
				 construct_path(start_node, current_node);
				 flag = true;
				 break;
			 }

 		 	// loop all its neighbors
			 for (auto it : direction){
				 		// valid if the neighbor's index is correct or not
            if (current_node -> x + it[0] >= map->rows || current_node -> x + it[0] < 0
						    || current_node -> y + it[1] >= map->columns || current_node -> y + it[1] < 0
							  )
								 continue;
						// check if its isClosed status and occupied status, if eigher == 1, skip this node
           node* neighbor = &map->grid[current_node -> x + it[0]][current_node -> y + it[1]];
					 if (neighbor -> isClosed == true || neighbor -> occupied_status == true) continue;

					 // if not in the openSet, add it in the openSet, update the g, value, h value
           if (neighbor -> isVisited != true) {
							neighbor -> h = calculate_h(current_node, goal_node);
							if (abs(it[0]) == 1 && abs(it[1] == 1)){
								neighbor -> g = current_node -> g + 14;
							}
							else {
									neighbor -> g = current_node -> g + 10;
							}
							neighbor -> f = neighbor -> g + neighbor -> h;
							neighbor -> x_pre = current_node -> x;
							neighbor -> y_pre = current_node -> y;
							neighbor -> isVisited = true;
							openSet.push(neighbor);
					 }
					 else {
						 if (abs(it[0]) == 1 && abs(it[1] == 1)){
							 if ((current_node-> g + 14) < (neighbor -> g)){
								 neighbor -> g = current_node -> g + 14;
								 neighbor -> x_pre = current_node -> x;
								 neighbor -> y_pre = current_node -> y;
								 neighbor -> f = neighbor -> g + neighbor -> h;

							 }
						 }
						 else {
							 if ((current_node-> g + 10) < (neighbor -> g)){
								 neighbor -> g = current_node -> g + 10;
								 neighbor -> x_pre = current_node -> x;
								 neighbor -> y_pre = current_node -> y;
								 neighbor -> f = neighbor -> g + neighbor -> h;

							 }
							}
						}
					}
				}
				if (!flag)
					cout << "No path"<< endl;
      
			}

	// given the goal node pointer, reconstruct the path through back tracking
	void construct_path(node* start_node, node* goal_node) {
			int parent_node_x = goal_node -> x_pre;
			int parent_node_y = goal_node -> y_pre;
			int start_x = start_node -> x;
			int start_y = start_node -> y;
			//cout << start_x << "ttttt" << start_y << endl;
			//cout << goal_node->x << "fffff" << goal_node->y << endl;
			goal_node->symble = '*';
		  node* parent_node = &(map-> grid[parent_node_x][parent_node_y]);
			parent_node -> symble = '*';
			while (!(parent_node -> x == start_x && parent_node -> y == start_y)){
		  	//node* current_node = parent_node;
				//cout << parent_node->x << "parent" << parent_node->y << endl;
				final_path.push_back(parent_node);
        parent_node = &(map-> grid[parent_node -> x_pre][parent_node -> y_pre]);
				parent_node -> symble = '*';
	    }
      //final_path.();
		}
};



int main(int argc, char const *argv[]){
	OccupancyGrid my_map(10,10);
	my_map.generate_grid();
	//my_map.generate_test_grid();
	//my_map.print_grid();
	A_star solver(&my_map);
	solver.search(0,0,5,5);
	my_map.print_grid();
	return 0;
};
