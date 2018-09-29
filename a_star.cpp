#include <iostream>
using namespace std;
#include <vector>


class node{
	public:
		int x; // index in the grid
		int y;

		int occupied_status; // occupied status;
		char symble; // . if the node is empty; # if the node is occupied

		double h; // heuristic cost
		double g; // moving cost

		// constructor, assign x, y, set h, g to be zero by default
		node(int x_in, int y_in) {
      x = x_in;
      y = y_in;
			h = 10000; // h value:  h is the heuristic value
			g = 10000; // g value: g cost, moving cost
			f = g + h; // f value: f = g + h, final cost
		}

	};
// occupency grid class contsins the

class OccupancyGrid {
public:
	int length;
	int width;
	vector< vector<node> > grid;
	// constructor: assign the length and width of the grid
	OccupancyGrid(int l, int w) {

	}

	// randomly generating the grid, generare node fill the grid, note the symple of the node if it is occupied or empty
	void generate_grid() {

	}

	// print the grid using the symble of the node : eg., ...###...
	void print_grid() {

	}

};


// we use a
class f_compare() {

}

class A_star {
public:

	OccupancyGrid* map; // note that we use a pointer to the built grid instead of  store a copy of the grid
	vector< node* > final_path; // final path from the start to the final node;

	vector< node* > openSet; // openSet, store the nodes that  needed to be checked
	vector< node* > closeSet; // closeSet, store the checked node


	// constructor, assign the input OccupancyGrid pointer to the map
	A_star(OccupancyGrid* map_in) {


	}

	void search(int x_0, int y_0, int x_f, int y_f) {

	}

};



int main(int argc, char const *argv[])
{
	//OccupancyGrid my_map(5,5);
	//my_map.generate_grid();
	//my_map.print_grid();
	return 0;
}
