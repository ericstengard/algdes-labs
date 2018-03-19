// AlgoDat_Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>
#include <math.h>

using namespace std;

void readFiles();
void solve();
void printSolution();

int n;
bool first = true;
std::string line;
std::vector <vector<int>> malesPref;
std::vector <vector<int>> femalesPref;
std::vector <string> names;
std::vector <int> partner;

int main() {
	readFiles();
	//solve();
	//printSolution();


	std::cout << "NAMES IN: " << endl;

	for (auto person : names) {
		std::cout << person << endl;
	}

	std::cout << "PREFS IN: " << endl;

	for (int i = 0; i < malesPref.size(); i++) {
		for (int j = 0; j < malesPref[i].size(); j++) {
			std::cout << malesPref[i][j];
		}
		std::cout << endl;
	}

	for (int i = 0; i < femalesPref.size(); i++) {
		for (int j = 0; j < femalesPref[i].size(); j++) {
			std::cout << femalesPref[i][j];
		}
		std::cout << endl;
	}

	return 0;
}

void readFiles() {

	ifstream myfile("c:\\Users\\Eric\\Documents\\LTH\\Year2\\algodat\\algdes-labs\\matching\\data\\sm-bbt-in.txt");
	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, line))
		{
			if (line.find("#") == std::string::npos)
			{
				if (first) {
					line.erase(0, 2);
					n = atoi(line.c_str());
					first = false;
					i++;
					continue;
				}
				line.erase(0, 2);
				for (int i = 0; i < line.length(); i++)
					if (line[i] == ' ') line.erase(i, 1);
				std::vector<int> prefs;


				std::cout << "i: " << i << endl;
				std::cout << "n: " << n << endl;
				std::cout << "FML" << endl;
				std::cout << floor(i/2) << endl;
			// This is for adding prefs.
				if(ceil(i/2) <= n)
					// Adding names
				{
					if (line.length() < 2) {
						continue;
					}
					else {
						std::cout << "Name to add: " << line << endl;
						names.push_back(line);
						partner.push_back(-1);
					}

				}
				else if (i % 2 == 0 && round(i / 2) > n) {
					for (char& i : line) {
						prefs.push_back(i - '0');
					}
					malesPref.push_back(prefs);
					prefs.clear();
				}
				else if (i % 2 != 0 && round(i / 2) > n) {
					for (char& i : line) {
						prefs.push_back(i - '0');
					}
					femalesPref.push_back(prefs);
					prefs.clear();
				}

				i++;
			}

		}
		myfile.close();
	}

	else cout << "Unable to open file";

}

void solve() {
	
	int male = 0;
	while (partner[male] == -1 && malesPref[male].size() > 0) {
		int woman = malesPref[male].front();

		if (partner[woman] == -1) {
			partner[male] = woman;
			partner[woman] = male;
		}
		auto abc = find(femalesPref[woman].begin(), femalesPref[woman].end(), male);
		int first = distance(femalesPref[woman].begin(), abc);
		auto abc2 = find(femalesPref[woman].begin(), femalesPref[woman].end(), partner[woman]);
		int second = distance(femalesPref[woman].begin(), abc2);
		if (first < second)
		{
			int ex = partner[woman];
			partner[ex] = -1;
			partner[woman] = male;
			partner[male] = woman;

		}
		male = (male + 2) % (n * 2);
		for (int i = 0; i < n; i++) {
			if (partner[male] != -1)
				male = (male + 2) % (n * 2);
		}
	}
	
}

void printSolution() {
	
	for (int i = 0; i < n; i++) {
		if (partner[i * 2] != -1)
			std::cout << names[i * 2] << " -- " << names[partner[i * 2]] << endl;
		else
			std::cout << names[i * 2] << " -- " << " free" << endl;
	}
	
}


