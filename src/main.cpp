#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "myAVL.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	if (argc < 3) {
		cout << "Error. Usage: ./main inputFile outputFile" << endl;
		return 1;
	}
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	if (!inputFile.is_open()) {
		cout << "Error. Bad input file" << endl;
		return 1;
	} 
	if (!outputFile.is_open()) {
		cout << "Error. Bad output file" << endl;
		return 1;
	}
	string line;
	string currentToken;
	myTree tree;

	while (getline(inputFile, line)) {
		istringstream myStream(line);
		myStream >> currentToken;

		if (currentToken == "i") {
			myStream >> currentToken;
			tree.insert(currentToken);
		}
		else if(currentToken == "r") {
			string lesser, greater;
			myStream >> lesser >> greater;
			outputFile << tree.range(lesser, greater) << "\n";
		}
	}

	return 0;
}
