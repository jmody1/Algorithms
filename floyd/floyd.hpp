#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;


class
Floyd
{

public:
	Floyd(string fileName) {this->fileName = fileName;}

	int findShortestPaths();

	int printMatrices();

	int readFile();

	int updateMatrix(vector<string>&);

private:
	string fileName;

	int numNodes = 0;						// Number of nodes in the graph
	
	int **dist;								// Distances matrix
	
	vector< vector< vector<int> > > path;	// Shortest paths between nodes
};