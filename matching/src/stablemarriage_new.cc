#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
std::vector<std::string> read();
void cramInNames(std::vector<std::string> namesM, std::vector<std::string> namesF, std::vector<std::string> data, int n);
void cramInPrefs(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, std::vector<std::string> data, int n);
std::vector<int> solve(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, int n);
void print(std::vector<int> couples, std::vector<std::string> namesM, std::vector<std::string> namesF, int n);
int main (){
  ios::sync_with_stdio(0);
  std::vector<std::string> data = read();
  int n = atoi(data.at(0).erase(0, 2).c_str());
  data.erase(data.begin());
  std::vector<std::string> namesM(n, "");
  std::vector<std::string> namesF(n, "");
  std::vector< std::vector<int> > prefsM;
  std::vector< std::vector<int> > prefsF;
  cramInNames(namesM, namesF, data, n);
  cramInPrefs(prefsM, prefsF, data, n);
  std::vector<int> couples = solve(prefsM, prefsF, n);
  print(couples, namesM, namesF, n);
}
std::vector<std::string> read(){
  std::vector<std::string> rtn;
  std::string line;
  while (getline(std::cin, line)){
    if(line.size() > 0 && line.at(0) != '#'){
      rtn.push_back(line);
    }
  }
  return rtn;
}
void cramInNames(std::vector<std::string> namesM, std::vector<std::string> namesF, std::vector<std::string> data, int n){
  int at = 0;
  bool M = true;
  for (std::string line : data){
    if (at*2 == n){
      break;
    }
    int number;
    string name;
    std::stringstream iss( line );
    iss >> number;
    iss >> name;
    if (M){
      namesM.at(at) = name;
    } else {
      namesF.at(at) = name;
      at++;
    }
    M=!M;
  }
  // at.clear();
  // M.clear();
  data.erase(data.begin()+n);
}
void cramInPrefs(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, std::vector<std::string> data, int n) {
  bool M = true;
  for (std::string line : data) {
    std::vector<int> prefs(n, -1);
    std::stringstream iss( line );
    string hane;
    iss >> hane;
    hane.clear();
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
}
std::vector<int> solve(std::vector< std::vector<int> > prefsM, std::vector< std::vector<int> > prefsF, int n){
  std::vector<int> couples(n, -1);
  std::vector<int> queue(n, -1);
  std::vector<int> trial(n, -1);
  for (int i = 0; i < n; i++){
    queue.at(i)=i;
  }
  while (queue.size() > 0){
    int male = queue.at(0);
    int target = prefsM.at(male).at(0);
    int prev = -1;
    prefsM.at(male).erase(prefsM.at(male).begin());
		queue.erase(queue.begin());
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
			queue.push_back(prev);
		}
  }
  // sort after males instead of females...
  for ( unsigned int i = 0; i < couples.size(); i++ ){
    trial.at(couples.at(i)) = i;
  }
  return trial;
}
void print(std::vector<int> couples, std::vector<std::string> namesM, std::vector<std::string> namesF, int n) {
  for (int i = 0; i < n; i++){
		std::cout << namesM.at(couples.at(i)) << " -- " << namesF.at(i) << '\n';
	}
}
