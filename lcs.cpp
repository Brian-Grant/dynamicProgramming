#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char **argv){
	
	if(argc != 3){
		cout << "Must be executed with two string command line arguments" << endl;
		return -1;
	}
	// get the strings from the command line
	string s1;
	string s2;
	
	istringstream buf1(argv[1]);
	buf1 >> s1;	
	istringstream buf2(argv[2]);
	buf2 >> s2;
	
	// get the length
	int lenS1 = s1.length();
	int lenS2 = s2.length();
	
	// add one to the length of each string to create the table bounds
	int tableX = lenS1+1;
	int tableY = lenS2+1;
	
	// create the table
	int** table;
	table = new int*[tableX];
	for(int i = 0; i < tableX; i++){
		table[i] = new int[tableY];
	}
	
	// create the table of associated directions
	string** dTable;
	dTable = new string*[tableX];
	for(int i = 0; i < tableX; i++){
		dTable[i] = new string[tableY];
	}

	
	table[0][0] = 0; // set top left corner of table to zero
	dTable[0][0] = "XX";	// set top left corner of dTable to xx
	for(int i = 1; i < tableX; i++){
		table[i][0] = 0; // initialize first column in table to 0
		dTable[i][0] = s1[i-1]; // initialize first column in dTable to input 
	}							// string s1
	for(int i = 1; i < tableY; i++){ 
		table[0][i] = 0; // initialize the first row in table to 0
		dTable[0][i] = s2[i-1]; // initialize first row in dTable to input
	}							// string s2
	
	// populate both tables with the relevant information
	for(int i = 1; i < tableX; i++){
		for(int j = 1; j < tableY; j++){
			if(s1[i-1] == s2[j-1]){ 
				table[i][j] = table[i-1][j-1] + 1; 
				dTable[i][j] = "D";
			}
			else{
				if(table[i-1][j] >= table[i][j-1]){
					table[i][j] = table[i-1][j];
					dTable[i][j] = "U";
				}
				else{
					table[i][j] = table[i][j-1];
					dTable[i][j] = "L";
				}
			}

		}
	}
	int resultInt = table[lenS1][lenS2]; // this is the length of the lcs
	
	char* result = new char[resultInt]; // this will be used to build the lcs
	
	int i=lenS1; 	
	int j=lenS2;
	int idx=(resultInt-1);
	string location;	
	location = dTable[i][j];
	while(idx >= 0){                   // here we start at the bottom right of
		if(location == "D"){			// the dTable and follow the "directions"
			result[idx] = s1[i-1];		// On "diagonals" we record the associated
			idx--;						// char in the result arr from right to 
			i--;						// left
			j--;
			location = dTable[i][j];
		}
		else if(location == "U"){
			i--;
			location = dTable[i][j];
		} 
		else if(location == "L"){
			j--;
			location = dTable[i][j];		
		}
	}
	// print the result
	if(resultInt == 0){
		cout << "There is no common subsequence" << endl;
	}
	else{	
		cout << "Length: " << resultInt << endl;		
		cout << result << endl;
	}
		
	// the following prints out both tables for debugging purposes

	// s1 is along y axis
	// s2 is along x axis
/*	for(int i = 0; i < tableX; i++){
		for(int j = 0; j < tableY; j++){
			cout << table[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;
	for(int i = 0; i < tableX; i++){
		for(int j = 0; j < tableY; j++){
			cout << dTable[i][j] << "\t";
		}
		cout << endl;
	}
*/


	// free the memory
	for(int i = 0; i < tableX; i++){
		delete[] table[i];
		delete[] dTable[i];
	}	
	delete[] table;
	delete[] dTable;
	delete[] result;
	


}
