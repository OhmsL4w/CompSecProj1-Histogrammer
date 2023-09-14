#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>
using namespace std;



int main(int argc, char* argv[]) {
	// validate user input and check thers only 1 param
	// open the file 
	// loop throuhg the file byte by byte and increment counts for each character

	int freq[256] = {};

	//if (argc != 2) {
	//	cout << "incorrect number of arguments";
	//	return 1;
	//}
	std::ifstream ifs;
	ifs.open("Hamlet.txt", ifstream::in | ifstream::binary); // change this to argv[1] when done testing 
	
		if (ifs.good() == false) {
		cout << "Error: could not open the file";
		return 1;
	}
		cout << "file opened successfully" << endl;

	unsigned char byte = ifs.get();
	int totalbytes{};
	while (!ifs.eof())
	{
		totalbytes++;
		freq[byte]++;
		byte = ifs.get();
	}

	//for (int i = 0; i < 32; i++){
	//	cout << setw(3) << i << setw(7) << freq[i] << " || "
	//	<< setw(3) << i + 32 << setw(7) << freq[i + 32] << " || "
	//	<< setw(3) << i + 64 << setw(7) << freq[i + 64] << " || "
	//	<< setw(3) << i + 96 << setw(7) << freq[i + 96] << " || "
	//	<< setw(3) << i + 128 << setw(7) << freq[i + 128] << " || "
	//	<< setw(3) << i + 160 << setw(7) << freq[i + 160] << " || "
	//	<< setw(3) << i + 192 << setw(7) << freq[i + 192] << " || "
	//	<< setw(3) << i + 224 << setw(7) << freq[i + 224] << endl;
	//}
	//cout << endl<< "Total bytes read were: " << totalbytes;

	//so far this code reads in the entire file and gets the frequency of all the characters that occur in the file, 
	//TO DO: implement the graph
	//TO DO: implement the scaling to scale everythihng using an algorithm
	//TO DO: add all the exceptions and error handling 

	int maxFreq = 0;
	for (int i = 0; i < 256; i++) {
		if (freq[i] > maxFreq) {
			maxFreq = freq[i];
		}
	}
	int rowNum = 20;
	double scale = (double)maxFreq / rowNum;
	vector<string> graph(rowNum, string(256, ' '));

	for (int i = 0; i < 256; i++) {
		int height = (int)(freq[i] / scale);
		for (int row = rowNum -1; row >= rowNum - height ; --row) {
			graph[row][i] = '*';
		}
	}
	graph.insert(graph.begin(), string(256, '-'));
	graph.push_back(string(256, '-'));
	for (string& row : graph) {
		row.insert(row.begin(), '|');
		row.push_back('|');
	}
	graph.front().front() = '+';
	graph.front().back() = '+';
	graph.back().front() = '+';
	graph.back().back() = '+';

	for (const string& row : graph) {
		cout << row << '\n';
	}
	cout<<('|');
	/*for (int i = 0; i < 256; i++)
	{
		cout << char(i);
		if (i < 255) {
			cout << " ";
		}
	}*/
	for (int i = 0; i < 256; ++i) {
		//char asciiChar = <char>(i);
		if (char(i) >= 32 && char(i) <= 126) {
			cout << char(i);
		}	
		else {
			cout << ' ';
		}
		
		
	}
	cout << ('|');


}
