#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <cstddef>
#include <map>
using namespace std;
std::map<string,set<string> > allKnowJumps;
class Node{
  public:
    string word;
    int numSteps;
  Node(string pword, int pnumSteps){
    word = pword;
    numSteps = pnumSteps;
  }
};
int findPath(set<string> words, string from, string to){
  list<Node> queue;
  list<string> wordsToErase;
  std::map<string,set<string> >::iterator it;
  std::set<string>::iterator it2;
  queue.push_front(Node(from, 0));
  while (!queue.empty()){
    Node top = queue.front();
    words.erase(top.word);
    queue.pop_front();
    string topword = top.word;
    if (topword.compare(to) == 0){
      return top.numSteps;
    }
    const clock_t begin2 = clock();
    std::cout << words.size() << '\n';
    it = allKnowJumps.find(topword);
    if (it != allKnowJumps.end()){
      std::cout << "topword found" << '\n';
      it2 = allKnowJumps[topword].find(to);
      if (it2 != allKnowJumps[topword].end()){
        return top.numSteps;
      }
      for (auto testWord : allKnowJumps[topword]){
        std::cout << "found jump" << '\n';
        it2 = words.find(testWord);
        if (it2 != words.end()){
          queue.push_back(Node(testWord, top.numSteps+1));
        }
        words.erase(testWord);
      }
    }
    std::cout << words.size() << '\n';
    const clock_t end2 = clock();
    // std::cout << "learnt: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
    const clock_t begin3 = clock();
    string topwordUntouched = topword;
    topword.erase(0,1);
    for (auto newWord : words){
      string temp = newWord;
      bool check = true;
      for(int i = 0; i < 4; i++){
        std::size_t found = temp.find_first_of(topword.at(i));
        if (found == std::string::npos){
          check = false;
          break;
        }
        temp[found] = '\0';
      }
      if (check){
        if (newWord.compare(to) == 0){
          return top.numSteps+1;
        }
        if (it != allKnowJumps.end()){
          allKnowJumps[topwordUntouched].insert(newWord);
        } else {
          set<string> hane;
          hane.insert(newWord);
          allKnowJumps.insert(std::pair<string,set<string> >(topwordUntouched, hane));
        }
        queue.push_back(Node(newWord, top.numSteps+1));
        wordsToErase.push_front(newWord);
      }
    }
    for (auto w : wordsToErase){
      words.erase(w);
    }
    const clock_t end3 = clock();
    // std::cout << "brute: " << (end2-begin2)/double(CLOCKS_PER_SEC) << '\n';
  }
  return -1;
}
int main(int argc, char *argv[]) {
  const clock_t begin1 = clock();
  pair<string, string> wordpair;
  set<string> words;
  list<pair<string,string> > pairs;
  char str1 [6];
  char str2 [6];
  FILE * pFile;
  pFile = fopen (argv[1],"r");
  while (fscanf (pFile, "%s", str1) != EOF){
    words.insert(str1);
  }
  fclose(pFile);
  pFile = fopen (argv[2],"r");
  while (fscanf (pFile, "%s %s", str1, str2) != EOF){
    wordpair = make_pair(str1,str2);
    pairs.push_back(wordpair);
  }
  fclose(pFile);
  int i = 0;
  for (auto p : pairs){
    std::cout << p.first << " to " << p.second << ". " << i << '\n';
    int temp = findPath(words, p.first, p.second);
    std::cout << temp << '\n';
    i++;
  }
  const clock_t end1 = clock();
  std::cout << "WHOLE: " << (end1-begin1)/double(CLOCKS_PER_SEC) << '\n';
  return 0;
}
