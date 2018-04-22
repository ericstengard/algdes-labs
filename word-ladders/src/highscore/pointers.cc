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
int n;
bool T = true;
std::list<std::pair<std::string,std::string> > wordpairs;
std::vector<std::string> words;
std::unordered_map<std::string,int> wordJ;
std::unordered_map<std::string,int> nameToIndex;
std::unordered_map<std::string,std::list<std::string> > neighbours;
std::unordered_map<std::string,std::vector<int> > neighbourss;

void addPossibleArc(int i, int j) {
  std::string from = words[i];
  std::string to = words[j];
  if(to.compare(from) == 0){
    return;
  }
  from.erase(0,1);
  for(int i = 0; i < 4; i++){
    std::size_t found = to.find_first_of(from.at(i));
    if (found == std::string::npos){
      return;
    }
    to[found] = '\0';
  }
  neighbourss[words[i]][j] = 1;
  neighbours[words[i]].push_back(words[j]);
}
void calcConnections(int size) {
  for(int i = 0; i < size; i++) {
    for(int j = i+1; j < size; j++) {
      if(i != j) {
        addPossibleArc(i,j);
        addPossibleArc(j,i);
      }
    }
  }
}
std::string first_numberstring(std::string const & str) {
  std::size_t const n = str.find_first_of("0123456789");
  if (n != std::string::npos) {
    std::size_t const m = str.find_first_not_of("0123456789", n);
    return str.substr(n, m != std::string::npos ? m-n : m);
  }
  return std::string();
}
int bfsALGO(std::string const & from, std::string const & to){
  std::vector<bool> visited(n);
  std::list<std::string> queue;
  queue.push_front(from);
  wordJ[from] = 0;
  if ( from.compare(to) == 0 ){
    return 0;
  }
  visited[nameToIndex[from]] = &T;
  if (neighbourss[from][nameToIndex[to]] == 1){
    return 1;
  }
  while ( !queue.empty() ){
    std::string v = queue.front();
    queue.pop_front();
    for (std::string neighbour : neighbours[v]) {
      if ( !visited[nameToIndex[neighbour]] ){
        visited[nameToIndex[neighbour]] = &T;
        wordJ[neighbour] = wordJ[v];
        wordJ[neighbour] ++;
        if (neighbourss[neighbour][nameToIndex[to]] == 1){
          wordJ[neighbour] ++;
          return wordJ[neighbour];
        }

        queue.push_back(neighbour);
      }
    }
  }

  return -1;
}
int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  const clock_t begin1 = clock();
  std::string filename = argv[1];
  filename = first_numberstring(filename);
  std::stringstream iss(filename);
  iss >> n;
  words.resize(n);
  std::pair<std::string, std::string> wordpair;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  while (fscanf (pFile, "%s", str1) != EOF){
    std::string temp = str1;
    words[at] = temp;
    std::list<std::string> temp1;
    std::vector<int> temp2(n, 0);
    nameToIndex.insert(make_pair(temp,at));
    wordJ.insert(make_pair(temp,0));
    neighbours.insert(make_pair(temp, temp1));
    neighbourss.insert(make_pair(temp, temp2));
    at++;
  }
  fclose(pFile);
  pFile = fopen (argv[2],"r");
  while (fscanf (pFile, "%s %s", str1, str2) != EOF){
    wordpair = std::make_pair(str1,str2);
    wordpairs.push_back(wordpair);
  }
  fclose(pFile);
  const clock_t end1 = clock();
  const clock_t begin2 = clock();
  calcConnections(n);
  const clock_t end2 = clock();
  const clock_t begin3 = clock();
  std::list<int> done;
  for (std::pair<std::string, std::string> pair : wordpairs){
    int soul = bfsALGO(pair.first, pair.second);
    done.push_back(soul);
  }
  const clock_t end3 = clock();
  for (auto i : done){
    std::cout << i << '\n';
  }
  std::cout << "READ: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  std::cout << "CALC: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  std::cout << "ALGO: " << (end3-begin3)/double(CLOCKS_PER_SEC) << '\n';
}
