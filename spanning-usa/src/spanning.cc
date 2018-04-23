#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <unordered_set>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>

struct Bim {
  std::string Fc;
  std::string Tc;
  int cost;
};

bool compareByLength(const Bim &a, const Bim &b)
{
    return a.cost < b.cost;
}

std::vector<std::string> Cnames;
std::vector<Bim> connections;



int main(int argc, char *argv[]) {
  char str [100];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  Cnames.resize(128);
  bool longname = false;
  while (fgets (str , 100 , pFile) != NULL && at < 128){
    std::string name = str;
    name.pop_back();
    Cnames[at] = name;
    // nameToIndex.insert(make_pair(name, at));
    at ++;
  }
  while (fgets (str , 100 , pFile) != NULL){
    std::string line = str;
    size_t pos = 0;
    pos = line.find("--");
    std::string from = line.substr(0, pos);
    line.erase(0, pos + 2);
    pos = line.find("[");
    std::string to = line.substr(0, pos);
    to.pop_back();
    line.erase(0, pos + 1);
    line.pop_back();
    std::string cost = line;
    int costI;
    std::stringstream iss( line );
    iss >> costI;
    Bim combo;
    combo.Fc = from;
    combo.Tc = to;
    combo.cost = costI;
    connections.push_back(combo);
  }
  std::sort(connections.begin(), connections.end(), compareByLength);
  


}
