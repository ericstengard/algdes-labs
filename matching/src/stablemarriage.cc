#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
using namespace std;
std::vector<string> namesM;
std::vector<string> namesF;
std::vector<std::vector<int> > prefsM;
std::vector<std::vector<int> > prefsF;
std::vector<int> couples;
std::vector<int> maletaken;
std::vector<int> trial;
std::list<int> queue;
int nb = 0;
int mc = 0;
int fc = 0;
int n;
int at = 0;
int main (){
  // int n;
  ios::sync_with_stdio(0);
  cin.tie(0);
  //take out N
  std::string line;
  getline(std::cin, line);
  while (line.at(0) == '#'){
    getline(std::cin, line);
  }
  n = std::atoi(line.erase(0, 2).c_str());
  //read all lines and store them
  // int at = 0;
  // std::vector<string> namesM(n,"");
  // std::vector<string> namesF(n,"");
  // std::vector<std::vector<int> > prefsM(n, std::vector<int>(n, 0));
  // std::vector<std::vector<int> > prefsF(n, std::vector<int>(n, 0));
  // std::vector<string> namesM;
  // std::vector<string> namesF;
  // std::vector<std::vector<int> > prefsM;
  // std::vector<std::vector<int> > prefsF;
  // int nb = 0;
  // int mc = 0;
  // int fc = 0;
  while (getline(std::cin, line)){
    if(line.size() > 0 && line.at(0) != '#'){
      if (at < n*2){
        int number;
        string name;
        std::stringstream iss( line );
        iss >> number;
        iss >> name;
        if (number%2 == 1){
          // namesM.at(nb) = name;
          namesM.push_back(name);
        } else {
          // namesF.at(nb) = name;
          namesF.push_back(name);
          nb++;
        }
      } else {
        int number;
        string name;
        // std::vector<int> prefs(n, 0);
        std::vector<int> prefs;
        for ( int j = 0; j < n; j++){
          prefs.push_back(0);
        }
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
        if (M) {
          // prefsM.at(mc) = prefs;
          prefsM.push_back(prefs);
          mc++;
        } else {
          // prefsF.at(fc) = prefs;
          prefsF.push_back(prefs);
          fc++;
        }
      }
      at++;
    }
  }
  //algo for perfect match
  // std::list<int> queue;
  // std::vector<int> couples(n, 0);
  // std::vector<int> maletaken(n, 0);
  // std::vector<int> trial(n, 0);
  // std::vector<int> couples;
  // std::vector<int> maletaken;
  // std::vector<int> trial;
  for (int i = 0; i < n; i++){
    queue.push_front(i);
    // couples.at(i) = -1;
    couples.push_back(-1);
    maletaken.push_back(0);
    trial.push_back(0);
  }
  while (queue.size() > 0){
    int male = queue.front();
    queue.pop_front();
    int target = prefsM.at(male).at(maletaken.at(male));
    maletaken.at(male)++;
    int prev = -1;
    if ( couples.at(target) == -1 ){
			couples.at(target) = male;
		} else {
      if ( prefsF.at(target).at(male) < prefsF.at(target).at(couples.at(target)) ){
        prev = couples.at(target);
        couples.at(target) = male;
      } else {
        prev = male;
      }
    }
    if (prev != -1){
			queue.push_front(prev);
		}
  }
  //sort them aaccording to males
  for ( int i = 0; i < n; i++ ){
    trial.at(couples.at(i)) = i;
  }
  //print to console
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(i) << " -- " << namesF.at(trial.at(i)) << '\n';
	}
  // for (int i = 0; i < n; i++){
	// 	std::cout << namesM[couples[i]] << " -- " << namesF[i] << '\n';
	// }
  namesM.clear();
  namesF.clear();
  prefsM.clear();
  prefsF.clear();
  couples.clear();
  maletaken.clear();
  trial.clear();
  queue.clear();
}
