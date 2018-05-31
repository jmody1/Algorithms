
#include "readCsv.hpp"


struct HuffmanNode;

class 
Huffman : public readCsv
{

public:

	Huffman(std::string fileName) { readFile(fileName, true); }
	int buildHuffmanTree();	
	int buildMinHeap();
	inline void swap(int, int, bool);
	inline int heapifyChild(int, int, bool);
	inline int makeHeapifyCall(bool);
	int heapify(int, bool);
	HuffmanNode* extractMin();
	int encode();

private:

	bool change_made = true;
	std::vector <int> args;
	std::vector <int> min_heap;
	std::vector <std::string> codes;
	int remaining;
	HuffmanNode** treePtr;

};



struct 
HuffmanNode 
{
	bool isLeaf = false;
	HuffmanNode* leftChild = nullptr;
	HuffmanNode* rightChild = nullptr;
	std::string item;
	std::string code = "";
	int idx, weight;
};