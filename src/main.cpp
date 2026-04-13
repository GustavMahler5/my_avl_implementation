#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "avl.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	// If there are insufficient arguments to terminal, print usage and terminate program
	if (argc < 3) {
		cout << "Error. Usage: ./main inputFile outputFile" << endl;
		return 1;
	}

	// Open input and output files
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	// Check if files have been properly opened. Terminate program if fail to open
	if (!inputFile.is_open()) {
		cout << "Error. Bad input file" << endl;
		return 1;
	} 
	if (!outputFile.is_open()) {
		cout << "Error. Bad output file" << endl;
		return 1;
	}

	string line; 			// Hold one query
	string currentToken;	// Hold one token from the query
	myTree tree;			// Our AVL tree

	// Loop through the input file and process all queries into the output file
	while (getline(inputFile, line)) {
		istringstream myStream(line);	
		myStream >> currentToken;

		// We perform insertion on an insertion query
		if (currentToken == "i") {
			myStream >> currentToken;
			tree.insert(currentToken);	// Insert to AVL tree
		}

		// We perform a traversal on a range query
		else if (currentToken == "r") {
			string lesser, greater;
			myStream >> lesser >> greater;
			outputFile << tree.range(lesser, greater) << "\n";	// Output to output file
		}
	}

	return 0;
}
