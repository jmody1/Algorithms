

#include "readCsv.hpp"


class 
bruteForce : public readCsv
{

public:

	bruteForce(std::string fileName) {readFile(fileName);}	// From now, we assume we have the whole data
	int findOptimalCombination();
	int binomialCoeffecient(int, std::vector < std::vector <int> >&);
	inline int findCombinations(int&, int, std::vector <int>&, std::vector < std::vector <int> >&, int&, int&);
	int findCosts(std::vector < std::vector <int> > &, std::vector <int> &, std::vector <int>&, int);


};