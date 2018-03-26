#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
using namespace std;
int n;
int main (int argc, char* argv[]){
  ios::sync_with_stdio(0);
  cin.tie(0);
  //take out N
  std::string line;
  getline(std::cin, line);
  while (line.at(0) == '#'){
    getline(std::cin, line);
  }
  n = atoi(line.erase(0, 2).c_str());
  //read all lines and store them
  int at = 0;
  string namesM[n];
  string namesF[n];
  std::vector<int> prefsM[n];
  std::vector<int> prefsF[n];
  int nb = 0;
  while (getline(std::cin, line)){
    if(line.size() > 0 && line.at(0) != '#'){
      if (at < n*2){
        int number;
        string name;
        std::stringstream iss( line );
        iss >> number;
        iss >> name;
        if (number%2 == 1){
          namesM[nb] = name;
        } else {
          namesF[nb] = name;
          nb++;
        }
      } else {
        int number;
        string name;
        std::vector<int> prefs(n, 0);
        std::stringstream iss( line );
        iss >> name;
        int num = std::stoi(name, nullptr, 0);
        bool M;
        if (num%2 == 1){
          M = true;
        } else {
          M = false;
        }
        nb = 0;
        while (iss >> number){
          if ( M ){
            prefs.at( nb ) = number / 2 - 1;
          } else {
            prefs.at( number/2 ) = nb;
          }
          nb++;
        }
        if (M){
          prefsM[num/2] = prefs;
        } else {
          prefsF[num/2-1] = prefs;
        }
      }
      at++;
    }
  }
  //algo for perfect match
  std::list<int> queue;
  int couples[n];
  int maletaken[n];
  int trial[n];
  for (int i = 0; i < n; i++){
    queue.push_front(i);
    couples[i] = -1;
    maletaken[i] = 0;
  }
  while (queue.size() > 0){
    int male = queue.front();
    queue.pop_front();
    int target = prefsM[male].at(maletaken[male]);
    maletaken[male]++;
    int prev = -1;
    if ( couples[target] == -1 ){
			couples[target] = male;
		} else {
      if ( prefsF[target].at(male) < prefsF[target].at(couples[target]) ){
        prev = couples[target];
        couples[target] = male;
      } else {
        prev = male;
      }
    }
    if (prev != -1){
			queue.push_front(prev);
		}
  }
  //sort them aaccording to males
  for ( unsigned int i = 0; i < n; i++ ){
    trial[couples[i]] = i;
  }
  //print to console
  for (int i = 0; i < n; i++){
		std::cout << namesM[i] << " -- " << namesF[trial[i]] << '\n';
	}
}
