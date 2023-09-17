#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void AsciiChars() {
	cout << ('|');
	for (int i = 0; i < 256; ++i) {
		//char asciiChar = <char>(i);
		if (char(i) >= 32 && char(i) <= 126) {
			cout << char(i);
		}
		else {
			cout << ' ';
		}
	}
	cout << ('|') << endl;
}

void numsInThreeRows() {

	for (int j = 0; j < 3; j++) {
		cout << ('|');
		for (int i = 0; i < 256; ++i) {
			if (j == 0) {
				if (i / 100 == 0) {
					cout << ' ';
				}
				else {
					cout << i / 100;
				}
			}
			else if (j == 1) {
				if (i / 10 == 0) {
					cout << ' ';
				}
				else {
					cout << (i / 10) % 10;
				}

			}
			else {
				cout << i % 10;

			}
		}
		cout << ('|') << endl;
	}
}

int main(int argc, char* argv[]) {
	
	int freq[256] = {};
	int rowNum = 20; // -rnn change when done testing
	bool displayAsciiGraph = false;
	bool displayNumsInThreeRows = false;
	bool displayLogarithmic = false;
	bool noGraph = false;
	string fileName ; // change this to argv[1] when done testing
	if (argc != 2) {
		cout << "incorrect number of arguments";
		return 1;
	}
	std::ifstream ifs;
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'r') {
				rowNum = atoi(argv[i] + 2);
			}
			else if (argv[i][1] == 'a') {
				displayAsciiGraph = true;
			}
			else if (argv[i][1] == 'n') {
				displayNumsInThreeRows = true;
			}
			else if (argv[i][1] == 'l') {
				displayLogarithmic = true;
			}
			else if (argv[i][1] == 'g') {
				noGraph = true;
			}
			else {
				cout << "invalid argument";
				return 1;
			}
		}
		else if (i == 1) {
			fileName = argv[i];
		}
		else {
			cout << "invalid argument";
			return 1;
		}
	}
	ifs.open(fileName, ifstream::in | ifstream::binary);  
	
	if (ifs.good() == false) {
	cout << "Input file not found" << endl;
	return 1;
	}
	cout << "file opened successfully" << endl;

	unsigned char byte = ifs.get();
	int totalbytes{};
	while (!ifs.eof()) {
		totalbytes++;
		freq[byte]++;
		byte = ifs.get();
	}

	int maxFreq = 0;
	for (int i = 0; i < 256; i++) {
		if (freq[i] > maxFreq) {
			maxFreq = freq[i];
		}
	}

	double scale = (double)maxFreq / rowNum;
	char graph[10][256];

	for (int i = 0; i < 256; i++) {
		int height = (int)(freq[i] / scale);
		for (int row = rowNum - 1; row >= rowNum - height; --row) {
			graph[row][i] = '*';
		}
	}
	if (noGraph == false) {
		// Print the top border
		cout << '+';
		for (int i = 0; i < 256; i++) {
			cout << '-';
		}
		cout << '+' << endl;
		if (displayLogarithmic == true) {
			// Logarithmic display
			// Calculate the scaling factor for logarithmic display
			double logScale = log10(1 + maxFreq) / rowNum;

			// Print the graph logarithmically
			for (int row = 0; row < rowNum; row++) {
				cout << '|';
				for (int col = 0; col < 256; col++) {
					// Calculate the height logarithmically
					int height = (int)(log10(1 + freq[col]) / logScale);
					if (row >= rowNum - height) {
						cout << '*';
					}
					else {
						cout << ' ';
					}
				}
				cout << '|' << endl;
			}
		}
		else {
			// Print the graph
			for (int row = 0; row < rowNum; row++) {
				cout << '|';
				for (int col = 0; col < 256; col++) {
					if (graph[row][col] == '*') {
						cout << '*';
					}
					else {
						cout << ' ';
					}
				}
				cout << '|' << endl;
			}
		}

		// Print the bottom border
		cout << '+';
		for (int i = 0; i < 256; i++) {
			cout << '-';
		}
		cout << '+' << endl;

		if (displayNumsInThreeRows == true) {
			numsInThreeRows();
		}
		if (displayAsciiGraph == true) {
			AsciiChars();
		}

	}
	

	return 0;
}
