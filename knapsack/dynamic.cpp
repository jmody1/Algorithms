#include "dynamic.hpp"


int 
Dynamic::printBoard()
{
	for (int i = 0; i <= this->n_elem; i++) {
		for (int j = 0; j < this->cc+1; j++) {
			std::cout << this->board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}



int 
Dynamic::initializeMatrix()
{
	board = (int**) malloc((this->n_elem+1) * sizeof(int*));
	for (int i = 0; i < n_elem+1; i++) {
		board[i] = (int*) calloc(sizeof(int), this->cc+1);
	}

	for (int i = 0; i < n_elem; i++) {
		this->board[i+1][this->items[1][i]] = this->items[0][i];
	}

	return 0;
}


inline int
Dynamic::max(int a, int b)
{
	if (a > b) {
		return a;
	} else {
		return b;
	}
}


int 
Dynamic::findOptimalSolution()
{
	/* Builds the matrix structure for finding the optimal solution */

	int cur;

	for (int i = 1; i <= this->n_elem; i++) {
		for (int j = 1; j <= this->cc; j++) {
			if (this->items[1][i-1] > j) {
				this->board[i][j] = this->board[i][j-1];
				if (this->board[i][j] < this->board[i-1][j]) this->board[i][j] = this->board[i-1][j];
			} else {
				this->board[i][j] = max(this->board[i-1][j], this->board[i-1][j-this->items[1][i-1]] + this->items[0][i-1]);
			  }
		}
	}
}


int
Dynamic::printOut()
{
	/* Print out the results */

	std::vector <int> chosen;

	int max_wt;

	for (int i = this->cc; i > 0; i--) {
		if (this->board[this->n_elem][i] != this->board[this->n_elem][i-1]) {
			max_wt = i;
			break;
		}
	}

	// Keep going till you figure out whether the item is added (or not).
	int final_cost = this->board[this->n_elem][this->cc];
	int current_cost = 0;
	int current_weight = max_wt;
	int diff = this->cc - max_wt;
	int row = this->n_elem;
	int col = max_wt;

	while (row > 0) {

		if (this->board[row][col] == this->board[row-1][col]) {
			row--;
			continue;
		}

		else if (this->board[row][col] == this->board[row][col-1]) {
			col--;
			continue;
		}

		else {
			if ((final_cost - current_cost >= this->items[0][row-1]) && current_weight >= this->items[1][row-1]) {
				chosen.push_back(row);
				current_cost += this->items[0][row-1];
				current_weight -= this->items[1][row-1];
				col -= this->items[1][row-1];
				row--;
				continue;
			} else {
				col--;
				continue;
			}
		}
	}	

	std::cout << "Total Profit: " << final_cost << std::endl;
	std::cout << "Total Weight: " << max_wt << std::endl;
	std::cout << "Items Selected: ";

	for (int i = chosen.size()-1; i >= 0; i--) { std::cout << chosen[i] << " ";}
	std::cout << std::endl;

	return 0;
}


int 
main(int argc, char* argv[])
{

	if (argc != 2) {std::cerr << "[Usage] ./dynamic.out <input_file_name>.csv"; exit(0);}

	Dynamic dyn(argv[1]);

	dyn.initializeMatrix();

	dyn.findOptimalSolution();

	dyn.printOut();

	return 0;	
}
