// AlgoDat_Lab1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
std::vector < vector<int> > malesPref;
std::vector < vector<int> > femalesPref;
std::vector <string> names;
std::vector <string> namesM;
std::vector <string> namesF;
std::vector <int> males;
std::vector <int> partner;

int main() {

	readFiles();

	std::cout << "NAMES IN: " << endl;

	for (auto person : names) {
		std::cout << person << endl;
	}

	std::cout << "PREFS IN: " << endl;

	for ( auto prefs : malesPref ){
		for ( auto pref : prefs ){
			std::cout << pref << " ";
		}
		std::cout << '\n';
	}
	for ( auto prefs : femalesPref ){
		for ( auto pref : prefs ){
			std::cout << pref << " ";
		}
		std::cout << '\n';
	}

	solve();
	printSolution();

	return 0;
}

void readFiles() {
	int at = 0;

	std::ifstream myfile("../data/sm-random-50-in.txt");
	//std::ifstream myfile("c:\\Users\\Eric\\Documents\\LTH\\Year2\\algodat\\algdes-labs\\matching\\data\\sm-bbt-in.txt");
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
				// line.erase(0,2);
				// for (int i = 0; i < line.length(); i++)
				// 	if (line[i] == ' ') line.erase(i, 1);
				std::vector<int> prefs;
				// This is for adding prefs.
				if(ceil(i/2) <= n)
					// Adding names
				{
					if (at < 9){
	            line.replace(0,2,"");
	          } else if (at < 99) {
	            line.replace(0,3,"");
	          } else {
	            line.replace(0,4,"");
	          }
					names.push_back(line);
				}
				else if (i % 2 == 0 && round(i / 2) > n) {
					if (at-n < 10){
	            line.replace(0,2,"");
	          } else if (at-n < 100) {
	            line.replace(0,3,"");
	          } else if (at-n < 1000) {
	            line.replace(0,4,"");
	          } else {
							line.replace(0,5,"");
						}
					int number;
          std::vector<int> prefs;
          std::stringstream iss( line );
          while ( iss >> number )
            prefs.push_back( number );
					// for (char& i : line) {
					// 	prefs.push_back(i - '0');
					// }
					malesPref.push_back(prefs);
					prefs.clear();
				}
				else if (i % 2 != 0 && round(i / 2) > n) {
					if (at-n < 10){
	            line.replace(0,2,"");
	          } else if (at-n < 100) {
	            line.replace(0,3,"");
	          } else if (at-n < 1000) {
	            line.replace(0,4,"");
	          } else {
							line.replace(0,5,"");
						}
					int number;
          std::vector<int> prefs;
          std::stringstream iss( line );
          while ( iss >> number )
            prefs.push_back( number );
					// for (char& i : line) {
					// 	prefs.push_back(i - '0');
					// }
					femalesPref.push_back(prefs);
					prefs.clear();
				}
				i++;
				at++;
			}

		}
		names.pop_back();
		myfile.close();
	}

	else cout << "Unable to open file";

}

void solve() {
	bool odd = true;
	for ( auto name : names ){
		if (odd){
			namesM.push_back(name);
		} else {
			namesF.push_back(name);
		}
		odd = !odd;
	}

	for ( int i = 0; i < n; i++){
		males.push_back(i);
		partner.push_back(-1);
	}

	while (males.size() > 0){
		int male = males.front();
		int target = malesPref.at(male).front()/2 - 1;
		int prev = -1;
		malesPref.at(male).erase(malesPref.at(male).begin());
		males.erase(males.begin());
		if ( partner.at(target) == -1 ){
			partner.at(target) = male;
		} else {
			for ( auto i : femalesPref.at(target) ){
				if ( i/2 == male ){
					prev = partner.at(target);
					partner.at(target) = male;
					break;
				} else if ( i/2 == partner.at(target) ){
					prev = male;
					break;
				}
			}
		}
		if (prev != -1){
			males.push_back(prev);
		}
	}
}

void printSolution() {
	for (int i = 0; i < n; i++){
		std::cout << namesM.at(partner.at(i)) << " -- " << namesF.at(i) << '\n';
	}
}
