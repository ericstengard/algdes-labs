#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;
std::vector<std::string> read(int n);
std::pair<std::vector<std::string>, std::vector<std::string> > cramInNames(std::vector<std::string> data, int n);
std::pair<std::vector<std::vector<int> >, std::vector<std::vector<int> > > cramInPrefs(std::vector<std::string> data, int n);
std::vector<int> solve(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, int n);
void print(std::vector<int> couples, std::vector<std::string> namesM, std::vector<std::string> namesF, int n);
int main (){
  ios::sync_with_stdio(0);
  cin.tie(0);
  std::string line;
  getline(std::cin, line);
  while (line.at(0) == '#'){
    getline(std::cin, line);
  }
  int n = atoi(line.erase(0, 2).c_str());
  // const clock_t begin1 = clock();
  std::vector<std::string> data = read(n);
  // const clock_t end1 = clock();
  // int n = atoi(data.at(0).erase(0, 2).c_str());
  // data.erase(data.begin());
  // const clock_t begin2 = clock();
  std::pair<std::vector<std::string>, std::vector<std::string> > names = cramInNames(data, n);
  // const clock_t end2 = clock();
  data.erase(data.begin(),data.begin()+(n*2));
  // const clock_t begin3 = clock();
  std::pair<std::vector<std::vector<int> >, std::vector<std::vector<int> > > prefs = cramInPrefs(data, n);
  // const clock_t end3 = clock();
  // const clock_t begin4 = clock();
  std::vector<int> couples = solve(prefs.first, prefs.second, n);
  // const clock_t end4 = clock();
  // const clock_t begin5 = clock();
  print(couples, names.first, names.second, n);
  // const clock_t end5 = clock();
  // std::cout << "READ: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "NAMES: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "PREFS: " << (end3-begin3)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "SOLVE: " << (end4-begin4)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "PRINT: " << (end5-begin5)/double(CLOCKS_PER_SEC) << '\n';
}
std::vector<std::string> read(int n){
  // std::vector<std::string> rtn(n*4, "");
  std::vector<std::string> rtn;
  std::string line;
  int at = 0;
  while (getline(std::cin, line)){
    if(line.size() > 0 && line.at(0) != '#'){
      rtn.push_back(line);
      at++;
    }
  }
  return rtn;
}
std::pair<std::vector<std::string>, std::vector<std::string> > cramInNames(std::vector<std::string> data, int n){
  std::vector<std::string> namesM;
  std::vector<std::string> namesF;
  int at = 0;
  for (std::string line : data){
    if (at == n){
      break;
    }
    int number;
    string name;
    std::stringstream iss( line );
    iss >> number;
    iss >> name;
    if (number%2 == 1){
      namesM.push_back(name);
    } else {
      namesF.push_back(name);
      at++;
    }
  }
  auto rtn = std::make_pair(namesM, namesF);
  return rtn;
}
std::pair<std::vector<std::vector<int> >, std::vector<std::vector<int> > >  cramInPrefs(std::vector<std::string> data, int n) {
  std::vector< std::vector<int> > prefsM;
  std::vector< std::vector<int> > prefsF;
  for (std::string line : data) {
    std::vector<int> prefs(n, -1);
    std::stringstream iss( line );
    string hane;
    iss >> hane;
    bool M;
    int num = std::stoi(hane, nullptr, 0);
    if (num%2 ==1){
      M = true;
    } else {
      M = false;
    }
    int i = 0;
    int number;
    while ( iss >> number ){
      if ( M ){
        prefs.at( i ) = number / 2 - 1;
      } else {
        prefs.at( number/2 ) = i;
      }
      i++;
    }
    if ( M ){
      prefsM.push_back(prefs);
    } else {
      prefsF.push_back(prefs);
    }
    M=!M;
    // prefs.clear();
  }
  auto rtn = std::make_pair(prefsM, prefsF);
  return rtn;
}
std::vector<int> solve(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, int n){
  std::vector<int> couples(n, -1);
  std::list<int> queue;
  std::vector<int> maletaken(n,0);
  std::vector<int> trial(n, 0);
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
  // sort after males instead of females...
  for ( unsigned int i = 0; i < couples.size(); i++ ){
    trial.at(couples.at(i)) = i;
  }
  return trial;
}
void print(std::vector<int> couples, std::vector<std::string> namesM, std::vector<std::string> namesF, int n) {
  // for (int i = 0; i < n; i++){
	// 	std::cout << namesM.at(couples.at(i)) << " -- " << namesF.at(i) << '\n';
	// }
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(i) << " -- " << namesF.at(couples.at(i)) << '\n';
	}
}
