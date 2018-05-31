#include "backtrack.hpp"


inline void
backtrack::clone(std::vector <int> &dst, std::vector <int> &src)
{
	/* Clones src into dst */

	dst.clear();
	for (auto x: src)
		dst.push_back(x);
}



inline int 
backtrack::return_max_index(std::vector <int> &current)
{
	std::vector <int> __max__;
	int max = 0;
	int max_idx = -1;

	// if (current.size() == )

	for (int x: this->fractions) {
		__max__.push_back(x);
	}
	for (int x: current) {
		__max__[x] = 0;
	}

	for (int i = 0; i < this->fractions.size(); i++) {
		if (this->fractions[i] > max) {
			max = this->fractions[i];
			max_idx = i;
		}
	}
	return max_idx;
}



bool
backtrack::promising(int start, int current_cost, int current_wt, int &optimal_cost, std::vector <int> current)
{

	if (current_wt > this->cc)
		return false;

	int max_idx = return_max_index(current);
	int wt_rem = this->cc - current_wt;
	int wt_rem_cur = this->items[1][max_idx];

	// Compute the bounds
	while (wt_rem > 0) {

		if (wt_rem_cur == 0) {
			current.push_back(max_idx);
			if (start == this->n_elem)
				break;
			max_idx = return_max_index(current);
			if (max_idx == -1)	return true;
			wt_rem_cur = this->items[1][max_idx];
		}

		current_cost += this->fractions[max_idx];
		wt_rem--;
		wt_rem_cur--;

	}

	// If bound > current_optimal_cost, it is promising.
	return (current_cost > optimal_cost);
}



int
backtrack::recursivelyBacktrack(int start, int current_cost, int current_wt, std::vector <int>& optimal_vec, std::vector <int> current, int& optimal_cost)
{
	/*
	* Consider it like a binary space partitioning tree (every knapsack element is now a dimension)
	* Not promising? Prune (Backtrack)
	* start - start point, optimal_vec - to store intermmediate results
	* current - current vector
	*/
	
	if (!promising(start, current_cost, current_wt, optimal_cost, current))
		return 0;
	
	if (current_cost > optimal_cost) {
		clone(optimal_vec, current);
		optimal_cost = current_cost;
	}
		
	if (start >= this->n_elem)
		return 0;

	std::vector <int> klone;
	clone(klone, current);
	current.push_back(start);

	recursivelyBacktrack(start+1, current_cost+this->items[0][start], current_wt+this->items[1][start], optimal_vec, current, optimal_cost);
	recursivelyBacktrack(start+1, current_cost, current_wt, optimal_vec, klone, optimal_cost);

	return 0;
}


int
backtrack::findOptimalSolution()
{

	int optimal_cost = 0;
	std::vector <int> optimal_vec;
	std::vector <int> temp;

	for (int i = 0; i < this->items[0].size(); i++) {
		this->fractions.push_back(items[0][i]/items[1][i]);
	}

	recursivelyBacktrack(0, 0, 0, optimal_vec, temp, optimal_cost);
	printOut(optimal_vec);

	return 0;
}

int 
backtrack::printOut(std::vector <int> &sol)
{
	/* Print out the results*/

	int weight, profit;
	weight = profit = 0;

	for (auto i: sol) {
		weight += this->items[1][i];
		profit += this->items[0][i];
	}

	std::cout << "Total Profit : " << profit << std::endl;
	std::cout << "Total Weight : " << weight << std::endl;
	std::cout << "Selected Items : ";
	for (auto i: sol)	std::cout << i+1 << " ";
	std::cout << std::endl;
	
	return 0;
}





int 
main(int argc, char* argv[])
{

	if (argc != 2) {std::cerr << "[Usage] ./backtrack.out <input_file_name>.csv"; exit(0);}

	backtrack bt(argv[1]);

	bt.findOptimalSolution();

	return 0;	
}
