#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int main (int argc, char const *argv[]){
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
  // std::vector<string> namesM(n,"");
  // std::vector<string> namesF(n,"");
  std::vector<string> namesM;
  std::vector<string> namesF;
  // std::vector<std::vector<int> > prefsM(n, std::vector<int>(n, 0));
  // std::vector<std::vector<int> > prefsF(n, std::vector<int>(n, 0));
  std::vector<std::vector<int> > prefsM;
  std::vector<std::vector<int> > prefsF;
  //reading in names!
  char str[50];
  int num;
  int atM = 0;
  int atF = 0;
  for (int i = 0; i < n*2; i++){
    scanf("%d", &num);
    scanf("%s", str);
    if (num%2 == 1){
      // namesM.at(atM) = str;
      namesM.push_back(str);
      atM++;
    } else {
      // namesF.at(atF) = str;
      namesF.push_back(str);
      atF++;
    }
  }
  getline(std::cin, line);
  atM = 0;
  atF = 0;
  int gender;
  for (int i = 0; i < n*2; i++){
    scanf("%s", str);
    string number;
    std::stringstream iss( str );
    iss >> number;
    number.erase(number.size()-1, number.size());
    std::stringstream dss( number );
    dss >> gender;
    // std::vector<int> prefs(n,0);
    std::vector<int> prefs;
    for (int i = 0; i < n; i++){
      prefs.push_back(0);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &num);
      if (gender%2 == 1){
        prefs.at(i) = num/ 2 - 1;
      } else {
        prefs.at(num/2) = i;
      }
    }
    if (gender%2 == 1){
      // prefsM.at(atM) = prefs;
      prefsM.push_back(prefs);
      atM++;
    } else {
      // prefsF.at(atF) = prefs;
      prefsF.push_back(prefs);
      atF++;
    }
  }
  std::list<int> queue;
  // std::vector<int> couples(n, -1);
  std::vector<int> couples;
  // std::vector<int> maletaken(n, 0);
  std::vector<int> maletaken;
  for (int i = 0; i < n; i++){
    queue.push_front(i);
    couples.push_back(-1);
    maletaken.push_back(0);
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
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(couples.at(i)) << " -- " << namesF.at(i) << '\n';
	}
  return 0;
}
