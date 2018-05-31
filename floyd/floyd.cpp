#include "floyd.hpp"


int 
Floyd::updateMatrix(vector<string> &content)
{

	this->dist = (int**)malloc(this->numNodes * sizeof(int*));

	for (int i = 0; i < this->numNodes; i++)	this->dist[i] = (int*)calloc(this->numNodes, sizeof(int));
	this->path.resize(this->numNodes, vector< vector <int> >(this->numNodes, vector<int>(0)));	

	int idx;
	string curDist = "";

	for (int i = 0; i < this->numNodes; i++) {
		idx = 0;
		curDist = "";
		for  (int j = 0; j < content[i].size(); j++) {
			if (content[i][j] == ',') {
				this->dist[i][idx] = atoi(curDist.c_str());
				curDist = "";
				idx++;
			} else if ((int)content[i][j] == 32) {
				continue;
			} else {
				curDist += content[i][j];
				if (j == content[i].size()-1)	this->dist[i][idx] = atoi(curDist.c_str());	
			}
		}
	}
	return 0;
}	


int
Floyd::readFile()
{
	/*
	* Read from file and create the matrix
	*/

	string line;
	vector<string> wholeCsv;
	ifstream matrixFile;
	matrixFile.open(this->fileName);
	if (!matrixFile) {cerr << "[Error]: Unable to read file"; exit(1);}
	
	while (!matrixFile.eof())
	{
		getline(matrixFile, line);
		wholeCsv.push_back(line);
		if (line.size() > 2)	this->numNodes++;
	}

	updateMatrix(wholeCsv);
	return 0;
}

int 
Floyd::printMatrices()
{
	/*
	*Print the shortest paths
	*/

	for (int i = 0; i < this->numNodes; i++) {
		for (int j = 0; j < this->numNodes; j++) {
			cout << i+1 << "->";
			for (int k = 0; k < this->path[i][j].size(); k++) {
				cout << this->path[i][j][k]+1 << "->"; 
			}
			cout << j+1 << endl;
		}
	}

	return 0;
}


int
Floyd::findShortestPaths()
{	
	/*
	*Implementation of Floyd Warshall Algorithm
	*/

	int total_size;
	int firstPath, secondPath;

	for (int j = 0; j < this->numNodes; j++) {	// Intermediate nodes
		for (int i = 0; i < this->numNodes; i++) {	// Starting node
			for (int k = 0; k < this->numNodes; k++) {	// Ending node

				if(this->dist[i][k] > (this->dist[i][j] + this->dist[j][k])) {	// When an intermediate node has shorter path

					this->dist[i][k] = this->dist[i][j] + this->dist[j][k];
					total_size = this->path[i][j].size() + this->path[j][k].size();
					path[i][k].resize(total_size+1);

					if (total_size==0) {
						this->path[i][k][0] = j;
						continue;
					}
					
					firstPath = this->path[i][j].size();
					if (firstPath != 0) {
						for (int m = 0; m < firstPath; m++)
							this->path[i][k][m] = this->path[i][j][m];
						this->path[i][k][firstPath] = j;
					} else {
						this->path[i][k][firstPath] = j;
						}

					secondPath = this->path[j][k].size();
					if (secondPath != 0) {
						for (int m = 0; m < secondPath; m++) {
							this->path[i][k][m+firstPath+1] = this->path[j][k][m];
						} 
					}
				}
			}
		}
	}
	return 0;
}



int
main(int argc, char* argv[])
{
	assert(argc == 2 && "[Usage] ./floyd input.csv");

	Floyd floyd(argv[1]);

	floyd.readFile();

	floyd.findShortestPaths();

	floyd.printMatrices();

	return 0;
}