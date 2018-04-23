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
#include <queue>
#include <algorithm>

int n;
std::vector<std::pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<std::string> words;
std::unordered_map<std::string,std::vector<int> > calcW;
std::vector<std::vector<int> > wordNeighbours;
std::vector<int> wordJ;

void addPossibleArc(int i, int j) {
  wordNeighbours[i].reserve(77);
  std::string from = words[i];
  std::string to = words[j];
  from.erase(0,1);
  for(int i = 0; i < 4; i++){
    std::size_t found = to.find_first_of(from.at(i));
    if (found == std::string::npos){
      return;
    }
    to[found] = '\0';
  }
  wordNeighbours[i].push_back(j);
}

void calcConnections(int size) {
  for(int i = 0; i < size; i++) {
    std::string sorted = words[i];
    sorted.erase(0,1);
    std::sort(sorted.begin(), sorted.end());
    std::unordered_map<std::string,std::vector<int> >::const_iterator got = calcW.find(sorted);
    if ( got == calcW.end() ){
      for(int j = 0; j < size; j++) {
          addPossibleArc(i,j);
      }
      calcW.insert(make_pair(sorted, wordNeighbours[i]));
    } else {
      wordNeighbours[i] = calcW[sorted];
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

int bfsALGO(int from, int to, bool vis[]){
  if ( from == to ){
    return 0;
  }
  for (int i = 0; i < n; i++) {
    vis[i] = false;
  }
  std::queue<int> queue;
  queue.push(from);
  wordJ[from] = 0;
  vis[from] = true;
  while ( !queue.empty() ){
    int v = queue.front();
    queue.pop();
    for (int neighbour : wordNeighbours[v]) {
      if ( !vis[neighbour] ){
        vis[neighbour] = true;
        wordJ[neighbour] = wordJ[v] + 1;
        if (neighbour == to){
          return wordJ[neighbour];
        }
        queue.push(neighbour);
      }
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  // const clock_t begin1 = clock();
  std::string filename = argv[1];
  filename = first_numberstring(filename);
  std::stringstream iss(filename);
  iss >> n;
  words.resize(n);
  wordJ.resize(n);
  wordNeighbours.resize(n);
  std::pair<std::string, std::string> wordpair;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  while (fscanf (pFile, "%s", str1) != EOF){
    std::string temp = str1;
    words[at] = temp;
    nameToIndex.insert(make_pair(temp,at));
    at++;
  }
  fclose(pFile);
  pFile = fopen (argv[2],"r");
  while (fscanf (pFile, "%s %s", str1, str2) != EOF){
    wordpair = std::make_pair(str1,str2);
    wordpairs.push_back(wordpair);
  }
  fclose(pFile);
  // const clock_t end1 = clock();
  // const clock_t begin2 = clock();
  calcConnections(n);
  // const clock_t end2 = clock();
  // const clock_t begin3 = clock();
  int done[wordpairs.size()];
  bool visited[n];
  at = 0;
  for (std::pair<std::string, std::string> pair : wordpairs){
    done[at] = bfsALGO(nameToIndex[pair.first], nameToIndex[pair.second], visited);
    at++;
  }
  // const clock_t end3 = clock();
  for (int i = 0; i < wordpairs.size(); i++) {
    std::cout << done[i] << '\n';
  }
  // std::cout << "READ: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "CALC: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "ALGO: " << (end3-begin3)/double(CLOCKS_PER_SEC) << '\n';
}
