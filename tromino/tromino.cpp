#include "tromino.hpp"


int 
Tromino::trominoTile()
{
	this->tiles = (int**)calloc(this->num, sizeof(int*));
	for (int i = 0; i < this->num; i++)	this->tiles[i] = (int*)calloc(this->num, sizeof(int));

	buildTromino(0, 0, this->num, this->num, this->r, this->c);

	return 0;
}


int 
Tromino::buildParams(array <int, 24> &params, int row_s, int col_s, int row_e, int col_e, int r_hole, int c_hole)
{
	/* 
	   Builds parameters for recursive calls
	   Figures which half the hole is in, creates three other holes and updates the matrix
	*/

	int row_half = row_s + (row_e-row_s)/2;
	int col_half = col_s + (col_e-col_s)/2;

	if ((r_hole < row_half) && (c_hole < col_half))
	{
		params[0]=row_s; params[1]=col_s; params[2]=row_half; params[3]=col_half; params[4]=r_hole; params[5]=c_hole;
		params[6]=row_s; params[7]=col_half; params[8]=row_half; params[9]=col_e; params[10]=row_half-1; params[11]=col_half;
		params[12]=row_half; params[13]=col_s; params[14]=row_e; params[15]=col_half; params[16]=row_half; params[17]=col_half-1;
		params[18]=row_half; params[19]=col_half; params[20]=row_e; params[21]=col_e; params[22]=row_half; params[23]=col_half;
		this->tiles[row_half-1][col_half] = this->tiles[row_half][col_half-1] = this->tiles[row_half][col_half] = this->cnt;
		this->cnt++;
	}

	if ((r_hole < row_half) && (c_hole >= col_half))
	{
		params[0]=row_s; params[1]=col_s; params[2]=row_half; params[3]=col_half; params[4]=row_half-1; params[5]=col_half-1;
		params[6]=row_s; params[7]=col_half; params[8]=row_half; params[9]=col_e; params[10]=r_hole; params[11]=c_hole;
		params[12]=row_half; params[13]=col_s; params[14]=row_e; params[15]=col_half; params[16]=row_half; params[17]=col_half-1;
		params[18]=row_half; params[19]=col_half; params[20]=row_e; params[21]=col_e; params[22]=row_half; params[23]=col_half;
		this->tiles[row_half-1][col_half-1] = this->tiles[row_half][col_half-1] = this->tiles[row_half][col_half] = this->cnt;
		this->cnt++;
	}

	if ((r_hole >= row_half) && (c_hole < col_half))
	{
		params[0]=row_s; params[1]=col_s; params[2]=row_half; params[3]=col_half; params[4]=row_half-1; params[5]=col_half-1;
		params[6]=row_s; params[7]=col_half; params[8]=row_half; params[9]=col_e; params[10]=row_half-1; params[11]=col_half;
		params[12]=row_half; params[13]=col_s; params[14]=row_e; params[15]=col_half; params[16]=r_hole; params[17]=c_hole;
		params[18]=row_half; params[19]=col_half; params[20]=row_e; params[21]=col_e; params[22]=row_half; params[23]=col_half;
		this->tiles[row_half-1][col_half-1] = this->tiles[row_half-1][col_half] = this->tiles[row_half][col_half] = this->cnt;
		this->cnt++;
	}

	if ((r_hole >= row_half) && (c_hole >= col_half))
	{
		params[0]=row_s; params[1]=col_s; params[2]=row_half; params[3]=col_half; params[4]=row_half-1; params[5]=col_half-1;
		params[6]=row_s; params[7]=col_half; params[8]=row_half; params[9]=col_e; params[10]=row_half-1; params[11]=col_half;
		params[12]=row_half; params[13]=col_s; params[14]=row_e; params[15]=col_half; params[16]=row_half; params[17]=col_half-1;
		params[18]=row_half; params[19]=col_half; params[20]=row_e; params[21]=col_e; params[22]=r_hole; params[23]=c_hole;
		this->tiles[row_half-1][col_half-1] = this->tiles[row_half-1][col_half] = this->tiles[row_half][col_half-1] = this->cnt;
		this->cnt++;
	}

	return 0;
}


int 
Tromino::buildTromino(int row_s, int col_s, int row_e, int col_e, int r_hole, int c_hole)
{
	/*	Builds the tromino 
		row_s -> row start
		col_s -> col start
		row_e -> row end
		col_r -> col end
		r_hole -> row where hole is present
		c_hole -> col where hole is present
		(row_s, col_s) gives where square starts
		(row_e, col_e) gives where square ends
		(r_hole, c_hole) is where the hole is

	*/

	// Terminating condition
	if (((row_e - row_s) == 2) && ((col_e - col_s) == 2))
	{
		for (int i = row_s; i < row_e; i++) {
			for (int j = col_s; j < col_e; j++) {

				if (i==r_hole && j==c_hole) {
					continue;
				}	else {
						this->tiles[i][j] = this->cnt;
				}

			}
		}
		this->cnt++;
		return 0;
	}

	array <int, 24> params;	// Arguments for all the four recursive calls, six each
	buildParams(params, row_s, col_s, row_e, col_e, r_hole, c_hole);

	buildTromino(params[0], params[1], params[2], params[3], params[4], params[5]);
	buildTromino(params[6], params[7], params[8], params[9], params[10], params[11]);
	buildTromino(params[12], params[13], params[14], params[15], params[16], params[17]);
	buildTromino(params[18], params[19], params[20], params[21], params[22], params[23]);

	return 0;
}


int
Tromino::printTromino()
{
	/*
	* Prints tromino board
	*/
	for (int i = 0; i < this->num; i++) {
		for (int j = 0; j < this->num; j++) {
			cout << tiles[i][j] << "\t";
		}
		cout << endl << endl;
	}
	return 0;
}



int 
main(int argc, char* argv[])
{

	assert(argc == 4 && "[Usage] : ./tromino.out k n_rows n_cols");

	Tromino tromino(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	tromino.trominoTile();
	tromino.printTromino();
	tromino.~Tromino();

	return 0;
}