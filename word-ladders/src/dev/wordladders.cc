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
    // std::list<Node> prev;
    int numJ;
    bool visited;
    std::vector<int> neighbours;
    std::list<int> neighbourss;
};

// std::list<Node> calcFromNtoN(Node from, Node to, std::list<Node> ns){
//   if (from.word.compare(to.word) == 0){
//     ns.push_back(from);
//     return ns;
//   }
//   ns.push_back(from);
//   return calcFromNtoN(from.prev.front() , to, ns);
// }

int n;
std::list<std::pair<std::string,std::string> > wordpairs;
std::unordered_map<std::string,int> nameToIndex;
std::vector<Node> nodes;

void addPossibleArc(int i, int j) {
  std::string a = nodes[i].word;
  std::string b = nodes[j].word;
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
  nodes[i].neighbours[j] = 1;
  nodes[i].neighbourss.push_back(j);
}

void calcConnections(int size) {
  for(int i = 0; i < size; i++) {
    for(int j = i; j < size; j++) {
      if(i != j) {
        addPossibleArc(i,j);
        addPossibleArc(j,i);
      }
    }
  }
}

std::string first_numberstring(std::string const & str)
{
  std::size_t const n = str.find_first_of("0123456789");
  if (n != std::string::npos)
  {
    std::size_t const m = str.find_first_not_of("0123456789", n);
    return str.substr(n, m != std::string::npos ? m-n : m);
  }
  return std::string();
}

// std::list<Node> bfsALGO(std::string a, std::string b){
int bfsALGO(std::string a, std::string b){
  // std::vector<Node> nodes1(nodes);
  std::list<Node> queue;
  Node start = nodes[nameToIndex[a]];
  queue.push_front(start);
  std::list<Node> prevs;
  if ( a.compare(b) == 0 ){
    // nodes[nameToIndex[a]].prev.push_back(nodes[nameToIndex[b]]);
    nodes[nameToIndex[a]].numJ ++;
    // return calcFromNtoN(nodes[nameToIndex[a]], nodes[nameToIndex[b]], prevs);
    return nodes[nameToIndex[a]].numJ;
  }
  start.visited = true;
  while ( !queue.empty() ){
    Node v = queue.front();
    queue.pop_front();
    if (nodes[nameToIndex[v.word]].neighbours[nameToIndex[b]] == 1){
      // nodes[nameToIndex[v.word]].prev.push_back(nodes[nameToIndex[b]]);
      nodes[nameToIndex[v.word]].numJ ++;
      nodes[nameToIndex[v.word]].numJ ++;
      return nodes[nameToIndex[v.word]].numJ;
    }
    for (auto neighbour : v.neighbourss) {
      if ( nodes[neighbour].visited == false ){
        nodes[neighbour].visited = true;
        nodes[neighbour].numJ = nodes[nameToIndex[v.word]].numJ + 1;
        queue.push_back(nodes[neighbour]);
      }
    }
  }
  // std::list<Node> noPath;
  // return noPath;
  return 0;
}

int main(int argc, char *argv[]) {
  // const clock_t begin1 = clock();
  std::string filename = argv[1];
  // filename.erase(0,14);
  // filename.erase(filename.size()-4,filename.size());
  filename = first_numberstring(filename);
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
    std::vector<int> neigh(n, 0);
    node.neighbours = neigh;
    node.numJ = 0;
    nodes[at] = node;
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
  const clock_t begin1 = clock();
  calcConnections(n);
  const clock_t end1 = clock();
  std::list<int> done;
  const clock_t begin2 = clock();
  for (auto pair : wordpairs){
    // std::list<Node> soul = bfsALGO(pair.first, pair.second);
    // int hejd = soul.size();
    int hejd = bfsALGO(pair.first, pair.second);
    done.push_back(hejd-1);
    for (int i = 0; i < nodes.size(); i++) {
      nodes[i].visited = false;
      // std::list<Node> empty;
      // nodes[i].prev = empty;
      nodes[i].numJ = 0;
    }
  }
  const clock_t end2 = clock();
  for (auto i : done){
    std::cout << i << '\n';
  }
  std::cout << "GRAPH: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  std::cout << "ALGO: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
}
