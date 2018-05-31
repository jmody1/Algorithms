
#include "readCsv.hpp"
#include <random>


class
Dynamic : public readCsv
{

public:
	Dynamic(std::string fileName) {readFile(fileName);}	// From now, we assume we have the whole data
	int initializeMatrix();
	int findOptimalSolution();
	int printOptimalSolution();
	inline int max(int, int);
	int printBoard();
	int printOut();

private:
	int** board;
};

