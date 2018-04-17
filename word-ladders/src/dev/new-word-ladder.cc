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
namespace NODE{
  class Node{
    public:
      std::string word;
      static Node pred;
      std::list<int> neighbours;
      bool visited;
      bool calculated;
      void addNeighbour(int neighbour) { neighbours.push_front(neighbour); }
      std::list<NODE::Node> getNodePathFromThisTo(NODE::Node end) {
        std::list<NODE::Node> temp;
        return getNodePathFromThisTo(end, temp);
      }
      std::list<NODE::Node> getNodePathFromThisTo(NODE::Node end, std::list<NODE::Node> establishedPath) {
        if(end.word.compare(word) == 0) {
            establishedPath.push_front(*this);
            return establishedPath;
        }
        establishedPath.push_front(*this);
        return this->pred.getNodePathFromThisTo(end, establishedPath);
      }
  };
}
int n;
std::list<std::pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<NODE::Node> nodes;
bool addPossibleArc(NODE::Node a, std::string b) {
  if(a.word.compare(b) == 0){
    return false;
  }
  std::string temp = b;
  temp.erase(0,1);
  for(int i = 0; i < 4; i++){
    std::size_t found = b.find_first_of(temp.at(i));
    if (found == std::string::npos){
      return false;
    }
    temp[found] = '\0';
  }
  a.addNeighbour(nameToIndex[b]);
  return true;
}
void calcConnectionsForWord(NODE::Node tmp, std::string end) {
  if(tmp.calculated)
      return;
  for(NODE::Node n : nodes) {
    if(addPossibleArc(tmp, n.word)) {
      if( n.word.compare(end) == 0 ){
        return;
      }
    }
  }
  tmp.calculated = true;
}
std::list<NODE::Node> bfsALGO(std::string a, std::string b) {
  std::list<NODE::Node> queue;
  NODE::Node start = nodes[nameToIndex[a]];
  queue.push_front(start);
  if ( a.compare(b) == 0 ){
    return queue;
  }
  start.visited = true;
  while ( !queue.empty() ){
    NODE::Node v = queue.front();
    queue.pop_front();
    calcConnectionsForWord(v, b);
    for(int i : v.neighbours) {
      if(nodes[i].visited == false) {
        nodes[i].visited = true;
        queue.push_back(nodes[i]);
        nodes[i].pred = v;
        if ( nodes[i].word.compare(b) == 0 ) {
          return nodes[i].getNodePathFromThisTo(start);
        }
      }
    }
  }
  std::list<NODE::Node> noPath;
  return noPath;
}
int main(int argc, char *argv[]) {
  const clock_t begin1 = clock();
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
    std::string tempest = str1;
    NODE::Node node;
    node.word = tempest;
    nodes[at] = node;
    // nodes[at].pred = nullptr;
    nodes[at].visited = false;
    nameToIndex.insert(std::make_pair<std::string,int>(tempest,at));
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
    std::list<NODE::Node> soul = bfsALGO(pair.first, pair.second);
    std::cout << soul.size()-1 << '\n';
  }
}
