/* All questions inherit this class to read csv file*/
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class 
readCsv{

public:

	int readFile(std::string, bool);
	int buildForKnapsack();
	int buildForHuffman();

protected:
	
	std::vector <std::string> wholeCsv;		// The CSV file, parsed line by line
	std::vector <std::vector <int> > items;	// Items are stored as {{set_of_item_values}, {set_of_item_weights}}
	std::vector <std::string> chars;		// Characters to encode using huffman
	std::vector <int> freqs;				// Corresponding frequencies of all the characters
	int cc, n_elem;							// Knapsack capacity and number of elements available to loot

};


int 
readCsv::readFile(std::string fileName, bool huffman = false)
{
	/* Read from file */
	
	std::string line;
	std::ifstream matrixFile;
	matrixFile.open(fileName.c_str());
	if (!matrixFile) {std::cerr << "[Error]: Unable to read file"; exit(1);}
	
	while (!matrixFile.eof())
	{
		getline(matrixFile, line);
		this->wholeCsv.push_back(line);
	}

	if (!huffman) {
		return buildForKnapsack();
	} else {
		return buildForHuffman();
	}
}


int 
readCsv::buildForKnapsack()
{
	/* Builds the whole knapsack environment */

	items.resize(2);
	this->n_elem = atoi(this->wholeCsv[0].c_str());
	bool comma = false;
	this->cc = atoi(this->wholeCsv[1].c_str());
	std::string current = "";
	std::string cur = "";
	int w_idx;

	for (int i = 0; i < 2; i++) {
		w_idx = i+2;
		for (int k = 0; k < wholeCsv[w_idx].size(); k++)
		{	
			cur = this->wholeCsv[w_idx][k];
			if (cur == " ") {
				continue;
			} else if (cur == ",") {
				this->items[i].push_back(atoi(current.c_str()));
				current = "";
				} else {
					current += cur;
				  }
		}
		this->items[i].push_back(atoi(current.c_str()));
		current = "";
	}

	wholeCsv.clear();

	return 0;
}



int 
readCsv::buildForHuffman()
{	
	/* Build the environment for huffman */

	// We index the min-heap from 1 for conveniance
	this->chars.push_back("");
	this->freqs.push_back(0);

	std::string current = "";
	std::string cur = "";

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < this->wholeCsv[i].size(); j++) {
			cur = this->wholeCsv[i][j];
			if (cur == ",") {
				if (i == 0) {
					this->chars.push_back(current);
				} else {
					this->freqs.push_back(atoi(current.c_str()));
				}
				current = "";
			} else if (cur == " ") {
				continue;
			} else {
				current += cur;
			}
		}
		if (i == 0) {
			this->chars.push_back(current);
		} else {
			this->freqs.push_back(atoi(current.c_str()));
		}
		current = "";
	}

	return 0;
}

