#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
string line;
bool first = true;
int n;
bool odd = true;
int at = 0;
std::vector<string> namesM;
std::vector<string> namesF;
std::vector<std::vector<int> > prefM;
std::vector<std::vector<int> > prefF;
std::vector<int> couples;
std::vector<int> queue;
std::vector<int> trial;
void readFile();
void printData();
void solve();
void print();
int main (int argc, char* argv[]) {
  readFile();
  solve();
  print();
}
void readFile() {
  ios::sync_with_stdio(false);
  cin.tie(false);
  std::string line;
  std::vector<std::string> test;
  while (getline (std::cin, line) != nullptr) {
    if (line.at(0) != '#' && line.at(0) != ''){
      test.push_back(line);
    }
  }
  n = atoi(test.at(0).erase(0, 2).c_str());
  test.erase(myvector.begin())
  int at = 0;
  bool G = false;
  for (auto lin : test){
    if (at < n*2){
      int number;
      string name;
      std::stringstream iss( lin );
      if ( iss >> number ){
        if (iss >> name){
          if (number % 2 != 0){
            namesM.push_back(name);
          } else {
            namesF.push_back(name);
          }
        }
      }
    }
    if (n*2 < at < n*4) {
      int number;
      std::vector<int> prefs (n, -1);
      std::stringstream iss( lin );
      string hane;
      iss >> hane;
      bool F = true;
      int i = 1;
      while ( iss >> number ){
        if ( F ){
          F = !F;
          G = !G;
        } else {
          if ( G ){
            prefs.at( i - 1 ) = number / 2 - 1;
          } else {
            prefs.at( number/2 ) = i;
          }
          i++;
        }
      }
      if ( G ){
        prefM.push_back(prefs);
      } else {
        prefF.push_back(prefs);
      }
    }
    at++;
  }
}
void solve() {
  for (int i = 0 ; i < n; i++){
    couples.push_back(-1);
    queue.push_back(i);
    trial.push_back(0);
  }
  while (queue.size() > 0){
    int male = queue.at(0);
    int target = prefM.at(male).at(0);
    int prev = -1;
    prefM.at(male).erase(prefM.at(male).begin());
		queue.erase(queue.begin());
    if ( couples.at(target) == -1 ){
			couples.at(target) = male;
		} else {
      if ( prefF.at(target).at(male) < prefF.at(target).at(couples.at(target)) ){
        prev = couples.at(target);
        couples.at(target) = male;
      } else {
        prev = male;
      }
    }
    if (prev != -1){
			queue.push_back(prev);
		}
  }
  // sort after males instead of females...
  for ( int i = 0; i < couples.size(); i++ ){
    trial.at(couples.at(i)) = i;
  }
}
void print() {
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(i) << " -- " << namesF.at(trial.at(i)) << '\n';
	}
}
