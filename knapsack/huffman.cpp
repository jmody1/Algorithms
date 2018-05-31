
#include "huffman.hpp"



int
Huffman::encode()
{
	/* Builds Huffman tree recursively */
	
	if (this->remaining == 1)
		return 0;

	HuffmanNode* first;
	HuffmanNode* second;
	HuffmanNode* newNode = new HuffmanNode;
	int node_weight = 0;

	node_weight += this->freqs[1];
	first = extractMin();
	node_weight += this->freqs[1];
	second = extractMin();

	newNode->leftChild = first;
	newNode->rightChild = second;
	this->remaining++;

	this->treePtr[this->remaining] = newNode;
	this->treePtr[this->remaining]->weight = node_weight;
	this->freqs[this->remaining] = node_weight;
	makeHeapifyCall(false);
	encode();


	return 0;
}


HuffmanNode*
Huffman::extractMin()
{
	HuffmanNode* min = this->treePtr[1];

	swap(1, this->remaining, false);
	this->remaining--;
	makeHeapifyCall(false);

	return min;
}


int 
Huffman::buildHuffmanTree()
{
	/* Build the Huffman tree recursively */

	for (int i = 1; i < this->freqs.size(); i++) {
		treePtr[i] = new HuffmanNode;
		treePtr[i]->isLeaf = true;
		treePtr[i]->item = this->chars[args[i]];
		treePtr[i]->idx = args[i];
	}

	// Recursively encode the characters
	encode();

	this->codes.resize(this->chars.size());

	HuffmanNode* current;
	HuffmanNode* left;
	HuffmanNode* right;
	std::vector <HuffmanNode*> stack;
	std::vector <int> _args_(chars.size());

	// Use depth-first-search to parse back the tree
	stack.push_back(this->treePtr[1]);

	while (stack.size() > 0) {
		current = stack.back();
		stack.pop_back();
		left = current->leftChild;
		if (left != nullptr) {
			stack.push_back(left);
			left->code += current->code;
			left->code += "0";
		}
		right = current->rightChild;
		if (right != nullptr) {
			stack.push_back(right);
			right->code += current->code;
			right->code += "1";
		}
		if (current->isLeaf == true) {
			this->codes[current->idx] = current->code;
			_args_[args[current->idx]] = current->idx;
		}
	}

	for (int i = 1; i < this->chars.size(); i++) {
		std::cout << this->chars[_args_[i]] << "\t"; 
	}
	std::cout << std::endl;	

	for (int i = 1; i < this->chars.size(); i++) {
		std::cout << this->codes[i] << "\t";
	}
	std::cout << std::endl;

	// Free dynamically allocated memories
	for (int i = 1; i < this->freqs.size(); i++) {
		delete treePtr[i];
	}
	free(treePtr);

	return 0;
}


int 
Huffman::buildMinHeap()
{

	treePtr = (HuffmanNode**) malloc(sizeof(HuffmanNode*) * this->chars.size());

	// Fill the indices vector to make reconstruction easier	
	for (int i = 0; i < this->chars.size(); i++) {
		this->args.push_back(i);
	}

	this->remaining = (this->freqs.size() - 1);
	makeHeapifyCall(true);

	return 0;
}


inline int
Huffman::makeHeapifyCall(bool needed = true)
{
	/* One call to this function heapifies */

	int last_node = this->remaining / 2;
	this->change_made = true;

	while (this->change_made == true) {
		this->change_made = false;
		heapify(last_node, needed);
	}

	return 0;
}


inline void
Huffman::swap(int node_1, int node_2, bool needed) 
{
	// Swap the frequencies 
	int temp_freq = this->freqs[node_1];
	this->freqs[node_1] = this->freqs[node_2];
	this->freqs[node_2] = temp_freq;

	if (needed) {

		// Swap the characters
		std::string temp_enc = this->chars[node_1];
		this->chars[node_1] = this->chars[node_2];
		this->chars[node_2] = temp_enc;

		// Swap the indices
		int temp_arg = this->args[node_1];
		this->args[node_1] = this->args[node_2];
		this->args[node_2] = temp_arg;

	} else {

		// Swap the tree nodes
		HuffmanNode* temp = this->treePtr[node_1];
		this->treePtr[node_1] = this->treePtr[node_2];
		this->treePtr[node_2] = temp;

	}
}


inline int 
Huffman::heapifyChild(int parent, int side, bool needed)
{
	// Heapify operation on a left or right child
	if (side == 0) {
		int left_c = 2*parent;
		if (this->remaining >= left_c) {
			if (this->freqs[parent] > this->freqs[left_c]) {
				swap(parent, left_c, needed);
				this->change_made = true;
				return 1;
			} else {
				return 0;
			}
		}
	} else {
		int right_c = 2*parent+1;
		if (this->remaining >= right_c) {
			if (this->freqs[parent] > this->freqs[right_c]) {
				swap(parent, right_c, needed);
				this->change_made = true;
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}



int
Huffman::heapify(int parent, bool needed)
{
	// Actual heapify call

	heapifyChild(parent, 0, needed);	// Heapify left child
	heapifyChild(parent, 1, needed);	// Heapify right child

	if (parent > 1)	heapify(parent - 1, needed);	// Heapify recursively till we reach root node

	return 0;
}



int
main(int argc, char* argv[])
{

	if (argc != 2) {std::cerr << "[Usage] ./huffman.out <input_file_name>.csv"; exit(0);}

	// Load the data 
	Huffman hm(argv[1]);

	// Build the min-heap 
	hm.buildMinHeap();

	// Build Huffman tree and print out the results
	hm.buildHuffmanTree();

	return 0;
}