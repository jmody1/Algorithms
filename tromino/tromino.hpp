#include <cstdlib>
#include <iostream>
#include <array>
#include <assert.h>
#include <math.h>

using namespace std;


class 
Tromino
{

public:
	Tromino(int k, int r, int c) {this->k = k; this->r = r; this->c = c; this->num = pow(2.0, k);}

	int trominoTile();

	int buildTromino(int, int, int, int, int, int);

	int buildParams(array <int, 24>&, int, int, int, int, int, int);

	int printTromino();


private:
	int k, r, c, num, cnt = 1;	// Parameters

	int **tiles;		// Tromino board

	int numNodes = 0;	// Counter variable

};