all:
	make backtrack bruteForce dynamic huffman

bruteForce:
	g++ -o bruteForce.out bruteForce.cpp -g

dynamic:
	g++ -o dynamic.out dynamic.cpp -g -std=c++11

backtrack:
	g++ -o backtrack.out backtrack.cpp -g -std=c++11

huffman:
	g++ -o huffman.out huffman.cpp -g -std=c++11

clean:
	rm -f *out

debug_bf:
	gdb ./bruteForce.out

debug_dy:
	gdb ./dynamic.out

debug_bt:
	gdb ./backtrack.out

debug_hf:
	gdb ./huffman.out
