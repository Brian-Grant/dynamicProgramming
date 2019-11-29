#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void floyd(int** adjMatrix, int** distMatrix, int ** pMatrix, int v);
void printMatrix(int** matrix, int v);
void printPath(int start, int finish, int** distMatrix, int** pMatrix);
void endPrintPath(int start, int finish, int** distMatrix);
void startPrintPath(int start, int finish);
void printAllpaths(int** distMatrix, int** pMatrix, int n);

int main(int argc, char **argv){

	srand(time(0));	// seed rand with time
		
	int n = rand()%(10-5+1)+5; // randomly generate between 5-10 vertices inclusive
	cout << "n = " << n << endl;
	
	// construct the adjacency matrix
	int** adjMatrix;
	adjMatrix = new int*[n];
	for(int i = 0; i < n; i++){
		adjMatrix[i] = new int[n];
	}
	// populate matrix with random weights 1-10
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i==j){
				adjMatrix[i][j] = 0;
			}
			else{
				adjMatrix[i][j] = (rand()%10)+1;
			}
		}
	}
	// set [i][j] = [j][i] because graph is undirected
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i < j){
				adjMatrix[i][j] = adjMatrix[j][i];
			}
		}
	}
	
	// create distnace matrix
	int** distMatrix;
	distMatrix = new int*[n];
	for(int i = 0; i < n; i++){
		distMatrix[i] = new int[n];
	}
	
	// make the pointer matrix
	int** pMatrix;
	pMatrix = new int*[n];
	for(int i = 0; i < n; i++){
		pMatrix[i] = new int[n];
	}
	
	// run the algo
	floyd(adjMatrix, distMatrix, pMatrix, n);
	
	printMatrix(adjMatrix, n); // print adjacency matrix
	//printMatrix(distMatrix, n); // print the resulting distance matrix
	//printMatrix(pMatrix, n); // print the resulting pointer matrix
	printAllpaths(distMatrix, pMatrix, n);
	
	// free memory
	for(int i = 0; i < n; i++){
		delete[] adjMatrix[i];
		delete[] distMatrix[i];
		delete[] pMatrix[i];
	}	
	delete[] adjMatrix;
	delete[] distMatrix;
	delete[] pMatrix;

}





void floyd(int** adjMatrix, int** distMatrix, int ** pMatrix, int n){
	// initialize dist matrix to the adjMatrix
	// and initialize the intermediate vertex pointer matrix to -1
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			distMatrix[i][j] = adjMatrix[i][j]; 
			pMatrix[i][j] = -1;
		}
	}
	for(int i = 0; i < n; i++){ // using the ith node as an intermediate node
		for(int j = 0; j < n; j++){ // from node j
			for(int k = 0; k < n; k++){ // to node k
				// if the dist from j to i to k is less than the current dist
				// from j to k...update the distance to this new distance
				// and mark node i as an intermediate node on the path
				// from j to k in the intermediate vertex pointer matrix				
				if(distMatrix[j][i] + distMatrix[i][k] < distMatrix[j][k]){
					distMatrix[j][k] = distMatrix[j][i] + distMatrix[i][k];
					pMatrix[j][k] = i;
				}
			}
		}
	}
}

void printMatrix(int** matrix, int n){
	cout << endl;	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// print out start node
void startPrintPath(int start, int finish){
	cout << start << " " << finish << " Path: " << start << " ";
}

//recurse and print intermediate nodes
void printPath(int start, int finish, int** distMatrix, int** pMatrix){
	if(pMatrix[start][finish] != -1){
		printPath(start, pMatrix[start][finish], distMatrix, pMatrix);
		cout << pMatrix[start][finish] << " ";
		printPath(pMatrix[start][finish], finish, distMatrix, pMatrix);
	}
}

// print destination node
void endPrintPath(int start, int finish, int** distMatrix){
	int sum = distMatrix[start][finish];	
	cout << finish << " " << "Length: " << sum << endl;
}

// print out all pairs shortest paths
// we only need to print when i<j (or j<i) because the graph
// is undirected..this path from i to j == path from j to i
void printAllpaths(int** distMatrix, int** pMatrix, int n){
	cout << endl;	
	int ctr = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i < j){
				ctr++;
				startPrintPath(i, j);
				printPath(i, j, distMatrix, pMatrix);
				endPrintPath(i, j, distMatrix);
			}
		}
	}
}
