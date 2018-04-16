#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
std::vector<std::string> namesM;
std::vector<std::string> namesF;
std::vector<std::vector<int> > prefsM;
std::vector<std::vector<int> > prefsF;
std::vector<int> couples;
std::vector<int> maletaken;
std::vector<int> prefs;
int num;
int atM = 0;
int atF = 0;
char str[50];
int gender;
int n;
int main (int argc, char const *argv[]){
  // const clock_t begin1 = clock();
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
  namesM.resize(n);
  namesF.resize(n);
  prefsM.resize(n);
  prefsF.resize(n);
  //reading in names!
  for (int i = 0; i < n*2; i++){
    scanf("%d", &num);
    scanf("%s", str);
    if (num%2 == 1){
      namesM.at(atM) = str;
      atM++;
    } else {
      namesF.at(atF) = str;
      atF++;
    }
  }
  getline(std::cin, line);
  atM = 0;
  atF = 0;
  prefs.resize(n);
  for (int i = 0; i < n*2; i++){
    scanf("%s", str);
    std::string number = str;
    number.erase(number.size()-1, number.size());
    std::stringstream dss( number );
    dss >> gender;
    for (int i = 0; i < n; i++) {
      scanf("%d", &num);
      if (gender%2 == 1){
        prefs.at(i) = num/ 2 - 1;
      } else {
        prefs.at(num/2) = i;
      }
    }
    if (gender%2 == 1){
      prefsM.at(atM) = prefs;
      atM++;
    } else {
      prefsF.at(atF) = prefs;
      atF++;
    }
  }
  std::list<int> queue;
  couples.resize(n);
  maletaken.resize(n);
  for (int i = 0; i < n; i++){
    queue.push_front(i);
    couples.at(i) = -1;
    maletaken.at(i) = 0;
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
  // const clock_t end1 = clock();
  // std::cout << "WHOLE: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  return 0;
}
