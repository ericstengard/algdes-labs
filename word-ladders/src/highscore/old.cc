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

class Node{
  public:
    std::string word;
    // std::list<std::string> prevs;
    int numJ;
    // bool visited;
    std::vector<int> neighbours;
    std::vector<int> neighbourss;
    // std::unordered_set<int> neighbours;
    Node(std::string w, std::vector<int> n);
    // Node(std::string w);
};
Node::Node(std::string w, std::vector<int> n){
// Node::Node(std::string w){
  word = w;
  // visited = v;
  neighbours = n;
  // numJ = 0;
}

int n;
const bool T = true;
const bool F = false;
std::vector<std::pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<Node *> nodes;

void addPossibleArc(int i, int j) {
  std::string &a = (*nodes[i]).word;
  std::string &b = (*nodes[j]).word;
  if(a.compare(b) == 0){
    return;
  }
  std::string from = a;
  std::string to = b;
  from.erase(0,1);
  for(int i = 0; i < 4; i++){
    std::size_t found = to.find_first_of(from.at(i));
    if (found == std::string::npos){
      return;
    }
    to[found] = '\0';
  }
  (*nodes[i]).neighbours[j] = 1;
  (*nodes[i]).neighbourss.push_back(j);
  // (*nodes[i]).neighbours.insert(j);
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

// std::list<std::string> bfsALGO(Node & from, Node & to){
int bfsALGO(Node & from, Node & to, bool vis[]){
  // bool visited[n];
  for (int i = 0; i < n; i++) {
    vis[i] = F;
  }
  std::queue<Node *> queue;
  queue.push(&from);
  from.numJ = 0;
  if ( from.word.compare(to.word) == 0 ){
    return 0;
  }
  // std::unordered_set<int>::const_iterator got = from.neighbours.find(nameToIndex[to.word]);
  if ((*nodes[nameToIndex[from.word]]).neighbours[nameToIndex[to.word]] == 1){
  // if ( got != from.neighbours.end() ){
    // from.prevs.push_back(to.word);
    // return from.prevs;
    from.numJ ++;
    return from.numJ;
  }
  vis[nameToIndex[from.word]] = T;
  // got = (*nodes[nameToIndex[from.word]]).neighbours.find(nameToIndex[to.word]);
  // if (from.neighbours[nameToIndex[to.word]] == 1){
  //   // v.prevs.push_back(v.word);
  //   // v.prevs.push_back(to.word);
  //   from.numJ ++;
  //   // return v.prevs;
  //   return from.numJ;
  // }
  while ( !queue.empty() ){
    Node &v = (*queue.front());
    queue.pop();
    for (int neighbour : v.neighbourss) {
      if ( !vis[neighbour] ){
        // if ((*nodes[neighbour]).word.compare(to.word) == 0){
        //   v.prevs.push_back(v.word);
        //   v.prevs.push_back(to.word);
        //   return v.prevs;
        // }
        vis[neighbour] = T;
        // (*nodes[neighbour]).prevs = v.prevs;
        // (*nodes[neighbour]).prevs.push_back(v.word);
        (*nodes[neighbour]).numJ = v.numJ;
        (*nodes[neighbour]).numJ ++;
        // got = (*nodes[neighbour]).neighbours.find(nameToIndex[to.word]);
        if ((*nodes[neighbour]).neighbours[nameToIndex[to.word]] == 1){
        // if (got != (*nodes[neighbour]).neighbours.end()){
          (*nodes[neighbour]).numJ ++;
          return (*nodes[neighbour]).numJ;
        }

        queue.push(nodes[neighbour]);
      }
    }
  }
  // std::list<std::string> noPath;
  // return noPath;
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
  nodes.resize(n);
  // visited.resize(n);
  std::pair<std::string, std::string> wordpair;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  while (fscanf (pFile, "%s", str1) != EOF){
    std::string temp = str1;
    std::vector<int> neigh(n, 0);
    nodes[at] = new Node(temp, neigh);
    // nodes[at] = new Node(temp);
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
  std::list<int> done;
  bool visited[n];
  for (std::pair<std::string, std::string> pair : wordpairs){
    // std::list<std::string> soul = bfsALGO(*nodes[nameToIndex[pair.first]], *nodes[nameToIndex[pair.second]]);
    int soul = bfsALGO(*nodes[nameToIndex[pair.first]], *nodes[nameToIndex[pair.second]], visited);
    // int hejd = soul.size();
    done.push_back(soul);
    // visited.clear();
    // visited.resize(n);
    // for (int i = 0; i < nodes.size(); i++) {
    //   (*nodes[i]).visited = false;
    //   (*nodes[i]).numJ = 0;
    //   // (*nodes[i]).prevs.clear();
    // }
  }
  // const clock_t end3 = clock();
  for (auto i : done){
    // printf("%d\n", i);
    std::cout << i << '\n';
  }
  // at = 1;
  // for (auto ww : nodes){
  //   std::cout << at << " has there neighbours: ";
  //   at++;
  //   for (auto tt : ww->neighbourss){
  //     std::cout << tt+1 << " ";
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << "READ: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "CALC: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  // std::cout << "ALGO: " << (end3-begin3)/double(CLOCKS_PER_SEC) << '\n';
}
