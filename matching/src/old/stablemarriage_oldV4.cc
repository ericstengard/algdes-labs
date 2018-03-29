#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main (int argc, char const *argv[]){
  const clock_t begin1 = clock();
  int n;
  ios::sync_with_stdio(0);
  cin.tie(0);
  //take out N
  std::string line;
  getline(std::cin, line);
  while (line.at(0) == '#'){
    getline(std::cin, line);
  }
  line.erase(0, 2);
  std::stringstream iss( line );
  iss >> n;
  //read all lines and store them
  int at = 0;
  // const clock_t begin4 = clock();
  std::vector<string> namesM(n,"");
  std::vector<string> namesF(n,"");
  std::vector<std::vector<int> > prefsM(n, std::vector<int>(n, 0));
  std::vector<std::vector<int> > prefsF(n, std::vector<int>(n, 0));
  // const clock_t end4 = clock();
  int nb = 0;
  int mc = 0;
  int fc = 0;
  // const clock_t begin2 = clock();
  while (getline(std::cin, line)){
    if(line.size() > 0 && line.at(0) != '#'){
      if (at < n*2){
        int number;
        string name;
        std::stringstream iss( line );
        iss >> number;
        iss >> name;
        if (number%2 == 1){
          namesM.at(nb) = name;
        } else {
          namesF.at(nb) = name;
          nb++;
        }
      } else {
        int number;
        string name;
        std::vector<int> prefs(n, 0);
        std::stringstream iss( line );
        iss >> name;
        name.erase(name.size()-1, name.size());
        // int num = atoi(name.c_str());
        int num;
        std::stringstream tss( name );
        tss >> num;
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
          prefsM.at(mc) = prefs;
          mc++;
        } else {
          prefsF.at(fc) = prefs;
          fc++;
        }
      }
      at++;
    }
  }
  // const clock_t end2 = clock();
  //algo for perfect match
  // const clock_t begin3 = clock();
  std::list<int> queue;
  std::vector<int> couples(n, -1);
  std::vector<int> maletaken(n, 0);
  for (int i = 0; i < n; i++){
    queue.push_front(i);
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
  // const clock_t end3 = clock();
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(couples.at(i)) << " -- " << namesF.at(i) << '\n';
	}
  const clock_t end1 = clock();
  std::cout << "WHOLE: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "READ: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "ALGO: " << (end3-begin3)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "WRITEDATAS: " << (end4-begin4)/double(CLOCKS_PER_SEC) << '\n';
  return 0;
}
