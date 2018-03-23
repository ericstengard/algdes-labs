#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

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
  // printData();
  std::chrono::milliseconds before = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  solve();
  std::chrono::milliseconds after = std::chrono::duration_cast< std::chrono::milliseconds >(
      std::chrono::system_clock::now().time_since_epoch()
  );
  print();
  std::chrono::milliseconds took = after - before;
  std::cout << took.count() << '\n';
}

void readFile() {
  ifstream myfile ("../data/sm-random-500-in.txt");
  if (myfile.is_open()){
    while ( getline (myfile, line) ){
      if ( line.find("#") == std::string::npos ){
        if (first){
          first = !first;
          line.replace( 0, 2, "" );
          n = atoi( line.c_str() );
        }
        if ( at < n*2 + 1){
          at++;
          int number;
          string name;
          std::stringstream iss( line );
          if ( iss >> number ){
            if (iss >> name){
              if (number % 2 != 0){
                  namesM.push_back(name);
                } else {
                  namesF.push_back(name);
                }
              }
            }
          } else {
              try {
                line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
              } catch (const std::exception& e){ std::cout << "test1" << '\n'; }
              int number;
              std::vector<int> prefs (n, -1);
              std::stringstream iss( line );
              bool F = true;
              bool G = true;
              int i = 1;
              // try{
              while ( iss >> number ){
                if ( F ){
                  F = !F;
                  if (number % 2 != 0){
                    G = true;
                  } else { G = false; }
                } else {
                  if ( G ){
                    prefs.at( i - 1 ) = number / 2 - 1;
                  } else {
                    prefs.at( number/2 ) = i;
                  }
                  i++;
                }
              }
              // } catch (const std::exception& e){ std::cout << "test" << '\n'; }
              if ( G ){
                prefM.push_back(prefs);
              } else {
                prefF.push_back(prefs);
              }
          }
        }
      }
    } else cout << "Unable to open file";
    prefM.erase(prefM.begin());
}
void printData() {
  std::cout << "Male names" << '\n';
  for ( auto name : namesM ){
    std::cout << name << '\n';
  }
  std::cout << "Female names" << '\n';
  for ( auto name : namesF ){
    std::cout << name << '\n';
  }
  std::cout << "Prefs for males" << '\n';
  for ( auto prefs : prefM ){
    for ( auto pref : prefs ){
      std::cout << pref;
    }
    std::cout << '\n';
  }
  std::cout << "Prefs for females" << '\n';
  for ( auto prefs : prefF ){
    for ( auto pref : prefs ){
      std::cout << pref;
    }
    std::cout << '\n';
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
