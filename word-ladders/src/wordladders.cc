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
class Node{
  public:
    std::string word;
    std::list<std::string> prevs;
    // int numSteps;
    bool visited;
    bool calculated;
    std::list<int> neighbours;
  // Node(std::string pword){
  //   word = pword;
  //   // numSteps = pnumSteps;
  // }
};

int n;
std::list<std::pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<Node> nodes;

int addPossibleArc(Node a, std::string b) {
  if(a.word.compare(b) == 0){
    return -1;
  }
  std::string from = a.word;
  std::string to = b;
  from.erase(0,1);
  for(int i = 0; i < 4; i++){
    std::size_t found = to.find_first_of(from.at(i));
    if (found == std::string::npos){
      return -1;
    }
    to[found] = '\0';
  }
  return nameToIndex[b];
}

std::list<int> calcConnectionsForWord(Node tmp, std::string end) {
  if(tmp.calculated){
    return tmp.neighbours;
  }
  std::list<int> Nlist;
  Nlist = tmp.neighbours;
  for(Node n : nodes) {
    int neighbour = addPossibleArc(tmp, n.word);
    if(neighbour != -1) {
      Nlist.push_back(neighbour);
      if( n.word.compare(end) == 0 ){
        return Nlist;
      }
    }
  }
  tmp.calculated = true;
  return Nlist;
}

std::list<std::string> bfsALGO(std::string a, std::string b){
  std::list<Node> queue;
  Node start = nodes[nameToIndex[a]];
  queue.push_front(start);
  if ( a.compare(b) == 0 ){
    start.prevs.push_back(b);
    return start.prevs;
  }
  start.visited = true;
  while ( !queue.empty() ){
    Node v = queue.front();
    queue.pop_front();
    v.neighbours = calcConnectionsForWord(v, b);
    for(int i : v.neighbours) {
      // std::cout << v.word << " has these neighbours: ";
      // for (auto lol : v.neighbours){
      //   std::cout << nodes[lol].word << " ";
      // }
      // std::cout << '\n';
      if(nodes[i].visited == false) {
        nodes[i].visited = true;
        nodes[i].prevs = v.prevs;
        nodes[i].prevs.push_back(v.word);
        queue.push_back(nodes[i]);
        if ( nodes[i].word.compare(b) == 0 ) {
          // for (auto word : nodes[i].prevs){
          //   std::cout << word << " to ";
          // }
          // std::cout << b << '\n';
          nodes[i].prevs.push_back(b);
          return nodes[i].prevs;
        }
      }
    }
  }
  std::list<std::string> noPath;
  return noPath;
}


int main(int argc, char *argv[]) {
  // const clock_t begin1 = clock();
  std::string filename = argv[1];
  filename.erase(0,14);
  filename.erase(filename.size()-4,filename.size());
  std::stringstream iss(filename);
  iss >> n;
  nodes.resize(n);
  std::pair<std::string, std::string> wordpair;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  while (fscanf (pFile, "%s", str1) != EOF){
    std::string temp = str1;
    Node node;
    node.word = temp;
    node.visited = false;
    node.calculated = false;
    nodes[at] = node;
    // nodes[at].pred = nullptr;
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
  for (auto pair : wordpairs){
    std::list<std::string> soul = bfsALGO(pair.first, pair.second);
    int hejd = soul.size();
    std::cout << hejd-1 << '\n';
    for (int i = 0; i < nodes.size(); i++) {
      nodes[i].visited = false;
      std::list<std::string> empty;
      nodes[i].prevs = empty;
    }
  }
}
