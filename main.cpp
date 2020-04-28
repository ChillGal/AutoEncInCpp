#include "md5.h"
#include "sha256.h"
#include "sha512.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void initialise(int& i) {
	i = 1;
}
void WriteToCSV(string word, string enctype, string result, int time1, int time2, int time3, double avg) {
	ofstream myfile;
	myfile.open("Output.csv", ios_base::app);
	myfile << word << "," << enctype << "," << result << "," << time1 << "," << time2 << "," << time3 << "," << avg << endl;
	myfile.close();
}
void MD5Func(string &Input) {
	int time1 = 0, time2 = 0, time3 = 0, avg;
	for (int i = 0; i < 3;) {
		auto t1 = high_resolution_clock::now();
		md5(Input);
		auto t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		if (i == 0) {
			time1 = duration;
		}
		else if (i == 1) {
			time2 = duration;
		}
		else if (i == 2) {
			time3 = duration;
		}
		i++;
	}
	avg = (time1 + time2 + time3)/3;
	WriteToCSV(Input, "MD5", md5(Input), time1, time2, time3, avg );
}
void SHA256Func(string &Input) {
	int time1 = 0, time2 = 0, time3 = 0, avg;
	for (int i = 0; i < 3;) {
		auto t1 = high_resolution_clock::now();
		sha256(Input);
		auto t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		if (i < 1) {
			time1 = duration;
		}
		else if (i < 2) {
			time2 = duration;
		}
		else if (i < 3) {
			time3 = duration;
		}
		i++;
	}
	avg = (time1 + time2 + time3) / 3;
	WriteToCSV(Input, "SHA256", sha256(Input), time1, time2, time3, avg);
}
void SHA512Func(string &Input) {
	int time1 = 0, time2 = 0, time3 = 0, avg;
	for (int i = 0; i < 3;) {
		auto t1 = high_resolution_clock::now();
		sha512(Input);
		auto t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		if (i == 0) {
			time1 = duration;
		}
		else if (i == 1) {
			time2 = duration;
		}
		else if (i == 2) {
			time3 = duration;
		}
		i++;
	}
	avg = (time1 + time2 + time3) / 3;
	WriteToCSV(Input, "SHA512", sha512(Input), time1, time2, time3, avg);
}
void ReadFile() {
	int count{};
	if (FILE* file = fopen("InputList.txt", "r")) {
		fclose(file);
		ifstream myfile;
		myfile.open("InputList.txt");
		string word;
		while (!myfile.eof()) {
			getline(myfile, word);
			count++;
			MD5Func(word);
			SHA256Func(word);
			SHA512Func(word);
		};
		myfile.close();
		cout << "number of lines in Input file: " << count << endl;
	}
	else {
		cout << "File not found." << endl;
		system("pause");
	}
	

}
int main() {
	cout << __DATE__ << endl;
	cout << "This script automatically encrypts a list of words using various encryption methods and measures the time taken to encrypt the word. The output is a CSV file. The program will let you know when it is finished." << endl;
	ReadFile();
	cout << "FINISHED" << endl;
}