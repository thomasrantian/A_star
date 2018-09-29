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
      h = 0;
      g = 0;

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

	// randomly generating the grid
	void generate_grid() {

	}

	// print the grid using the symble of the node : eg., ...###...
	void print_grid() {

	}

};

class A_star {
public:
	OccupancyGrid* map;
	// assign the map to the solver, note the type of the input
	A_star(OccupancyGrid* map_in) {


	}

	vector<node> solution;

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
