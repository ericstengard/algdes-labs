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
    string word;
    Node pred = nullptr;
    List<string> neighbours;
    bool visited;
    bool calculated;
    void addNeighbour(string neighbour) { neighbours.push_front(neighbour); }
    List<string> getNodePathFromThisTo(Node end) { return getNodePathFromThisTo(end, new LinkedList<Node>()); }
    List<string> getNodePathFromThisTo(Node end, List<Node> establishedPath) {
      if(end.word.compare(word) == 0) {
          establishedPath.push_front(*this);
          return establishedPath;
      }
      establishedPath.push_front(*this);
      return this->pred.getNodePathFromThisTo(end, establishedPath);
    }
};
Node::Node(string pword){
  word = pword;
}
list<Node> breathFirstAlgorithm(String a, String b) {
  list<Node> queue;
  Node start = nodesnodes.
}
int n;
list<pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<Node> nodes;


int main(int argc, char *argv[]) {
  const clock_t begin1 = clock();
  std::string filename = argv[1];
  filename.erase(0,14);
  filename.erase(filename.size()-4,filename.size());
  std::stringstream iss(filename);
  iss >> n;
  nodes.resize(n);
  pair<string, string> wordpair;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  int at = 0;
  while (fscanf (pFile, "%s", str1) != EOF){
    nodes[at] = Node(str1);
    nameToIndex.insert(std::make_pair<std::string,int>(str1,at));
  }
  fclose(pFile);
  pFile = fopen (argv[2],"r");
  while (fscanf (pFile, "%s %s", str1, str2) != EOF){
    wordpair = make_pair(str1,str2);
    wordpairs.push_back(wordpair);
  }
  fclose(pFile);
  for (auto pair : wordpairs){
    list<Node> soul = bfsALGO(pair.first, pair.second);
    std::cout << soul.size()-1 << '\n';
  }
}
