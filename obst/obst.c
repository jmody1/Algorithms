#include <stdio.h>
#include <stdlib.h>

void createOptimalTree(float *p);

int n;

int main(int argc, char* argv[]) {

	n = atoi(argv[1]);
	float p[n+1];
	for(int i=0; i<n; i++){
		p[i+1] = atof(argv[i+2]);
	}

	createOptimalTree(p);
	return EXIT_SUCCESS;
}

void initTable(float table[n+2][n+1]){
	for(int i=0; i<n+2; i++){
		for(int j=0; j<n+1; j++){
			table[i][j] = 0.0f;
		}
	}
}

void initRoots(int roots[n+2][n+1]){
	for(int i=0; i<n+2; i++){
		for(int j=0; j<n+1; j++){
			roots[i][j] = -1;
		}
	}
}

void createOptimalTree(float *p){
	int i, j, k, diagonal;
	float table[n+2][n+1];
	int roots[n+2][n+1];
	initTable(table);
	initRoots(roots);
	for(i=1; i<=n; i++){
		table[i][i-1] = 0;
		roots[i][i-1] = 0;
		table[i][i] = p[i];
		roots[i][i] = i;
	}

	for(diagonal=1; diagonal<=n-1;diagonal++){
		for(i=1; i<=n-diagonal; i++){
			j = i+diagonal;
			float totalP = 0.0f, minVal = 9999.0f, minRoot;
			for(k=i; k<=j; k++){
				totalP += p[k];
			}
			for(k=i; k<=j; k++){
				float newVal = table[i][k-1] + table[k+1][j] + totalP;
				if(newVal <= minVal){
					minVal = newVal;
					minRoot = k;
				}
			}
			table[i][j] = minVal;
			roots[i][j] = minRoot;
		}
	}

	printDepths(roots);
}


void printDepths(int roots[n+2][n+1]){
	int front = 1, rear = 1;
	int queue[n+1];
	int used[n+1];
	int depth = 0;
	int exit = 1;
	for(int i=1; i<=n; i++){
		used[i] = 0;
		queue[i] = 0;
	}

	//get root
	int root = roots[1][n];
	//mark root as used
	used[root] = 1;

	//add root to queue
	queue[rear] = root;
	rear++;

	//a copy of rear value at each iteration of while loop below
	int rearCopy;


	while(1){
		//by default, exit
		exit = 1;
		//make a copy of rear at this point
		rearCopy = rear;
		printf("depth %d:", depth);
		//for all keys at this depth
		for(int i=front; i<rearCopy;i++){
			printf(" k%d,", queue[i]);

			//get left and right child
			int leftChild = roots[1][queue[i]-1]; //roots[1][2]
			int rightChild = roots[queue[i]+1][n];


			if(leftChild != -1 && used[leftChild]==0){ //if leftChild exists, add to queue
				used[leftChild] = 1;
				queue[rear] = leftChild;
				rear++;
				exit = 0; //child exists, next iteration exists
			}
			if(rightChild != -1 && used[rightChild]==0){//if rightChild exists, add to queue
				used[rightChild] = 1;
				queue[rear] = rightChild;
				rear++;
				exit = 0; //child exists, next iteration exists
			}
			front++;//remove current node
		}

		if(exit){
			printf("\n");
			break;
		}
		printf(" ");
		depth++;
	}


}