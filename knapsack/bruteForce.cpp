
#include "bruteForce.hpp"
#include <cmath>

inline int 
bruteForce::findCombinations(int &r, int st, std::vector <int> &combination, std::vector < std::vector <int> >& cur_comb, int &done, int &n_c_r) 
{
	/*
	* Recursive tree method to build combinations
	*/

	int idx;
	std::vector < std::vector <int> > new_clones;
	new_clones.resize(this->n_elem+1 - st);
	for (int i = st; i < this->n_elem+1; i++) { 
		new_clones[i-st] = combination; 
	}

	for (int i = 0; i < new_clones.size(); i++)
	{
		if (done >= n_c_r)	return 0;		// When we are done adding all combinations
		if (new_clones[i].size() == r) {
			cur_comb[done] = new_clones[i];
			done++;
			return 0;
		}
		if (i+st >= this->n_elem)	continue;	// Whatever to be pushed inside should not be greater than max elements
		if (new_clones[i][new_clones[i].size()-1] >= i+st)	continue;	// If {0,3} is in clones, and nothing <= 3 should be added
		new_clones[i].push_back(i+st);
		findCombinations(r, st+1, new_clones[i], cur_comb, done, n_c_r);
	}

	return 0;
}



int 
bruteForce::binomialCoeffecient(int r, std::vector < std::vector <int> >& cur_comb)
{	
	/*
	* Computes all possible combinations given by n_elem C r
	*/

	if (this->n_elem == r) {
		cur_comb.resize(1);
		for (int i = 0; i < this->n_elem; i++) {
			cur_comb[0].push_back(i);
		}
		return 0;
	}

	int n_c_r, num = 1, den = 1, done = 0;

	for (int i = 0; i < r; i++) {
		num *= (this->n_elem-i);
		den *= (i+1);
	}

	// n_c_r is the binomial coefficient. We pre-allocate memory to hold these many combinations
	n_c_r = num / den;
	cur_comb.resize(n_c_r);
	std::vector <int> temp;

	for (int i = 0; i < this->n_elem; i++) {
		temp.clear();
		temp.push_back(i);
		findCombinations(r, i+1, temp, cur_comb, done, n_c_r);
	}

	return 0;
}


int 
bruteForce::findCosts(std::vector < std::vector <int> > &bc, std::vector <int> &costs, std::vector <int> &idxs, int idx)
{
	/*
	* Given a combination, find corresponding costs.
	*/

	int max = 0;
	int weight = 0;
	idxs[idx] = -1;


	for (int i = 0; i < bc.size(); i++) {
		costs.push_back(0);
		weight = 0;
		for (int j = 0; j < bc[i].size(); j++) {
			costs[i] += this->items[0][bc[i][j]];
			weight += this->items[1][bc[i][j]];
		}
		if (weight <= this->cc && costs[i] > max) {
			idxs[idx] = i;
			max = costs[i];
		}
	}

	return 0;
}


int
bruteForce::findOptimalCombination()
{
	/* Finds the optimal solution to 0/1 knapsack problem using brute force method */

	int total_combinations = pow(2, this->n_elem);

	int min = 99999999;
	for (int i = 0; i < n_elem; i++) {
		if (this->items[1][i] < min) min = this->items[1][i]; 
	}

	if (this->cc < min) {
		std::cerr << "There is no optimal solution. The knapsack capacity(" << this->cc << ") is lower than the smallest item(" << min << ")" << std::endl;;
		exit(0);
	}
	
	std::vector < std::vector < std::vector <int> > > combinations;
	std::vector < std::vector <int> > costs;
	std::vector <int> idxs(this->n_elem);
	combinations.resize(this->n_elem);
	costs.resize(this->n_elem);

	// We calculate the combinations for knapsack with all capacities
	for (int i = 0; i < this->n_elem; i++) {
		binomialCoeffecient(i+1, combinations[i]);
		findCosts(combinations[i], costs[i], idxs, i);
	}

	int max = 0;
	int max_idx;
	int total_wt = 0;

	for (int i = 0; i < idxs.size(); i++) {
		if (costs[i][idxs[i]] > max && idxs[i] > 0) {
			max = costs[i][idxs[i]];
			max_idx = i;
		}
	}

	for (int i = 0; i < combinations[max_idx][idxs[max_idx]].size(); i++) {
		total_wt += this->items[1][combinations[max_idx][idxs[max_idx]][i]];
	}

	std::cout << "Total Profit: " << costs[max_idx][idxs[max_idx]] << std::endl;
	std::cout << "Total Weight: " << total_wt << std::endl;
	std::cout << "Items Selected: ";
	
	for (int i = 0; i < combinations[max_idx][idxs[max_idx]].size(); i++) {
		std::cout << combinations[max_idx][idxs[max_idx]][i]+1 << " ";
	}
	
	std::cout << std::endl;

	return 0;
}






int 
main(int argc, char* argv[])
{

	if (argc != 2) {std::cerr << "[Usage] ./bruteForce.out <input_file_name>.csv"; exit(0);}

	bruteForce bf(argv[1]);

	bf.findOptimalCombination();

	return 0;	
}
