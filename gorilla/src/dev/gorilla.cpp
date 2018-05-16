#include <stdio.h>
#include <fstream>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <unordered_map>

#define MAX_N 1001

using namespace std;
typedef long long lld;
typedef unsigned long long llu;
int gap_score = 4;
std::unordered_map<char, int> charToIndex;
int match_scoreboard[24][24] = {{4, -1, -2, -2,  0, -1, -1,  0, -2, -1, -1, -1, -1, -2, -1,  1,  0, -3, -2,  0, -2, -1,  0},
                               {-1, 5,  0,  -2, -3, 1,  0,  -2, 0,  -3, -2, 2,  -1, -3, -2, -1, -1, -3, -2, -3, -1, 0,  -1},
                               {-2, 0,  6,  1,  -3, 0,  0,  0,  1,  -3, -3, 0,  -2, -3, -2, 1,  0,  -4, -2, -3, 3,  0,  -1},
                               {-2, -2, 1,  6,  -3, 0,  2,  -1, -1, -3, -4, -1, -3, -3, -1, 0,  -1, -4, -3, -3, 4,  1,  -1},
                               {0,  -3, -3, -3, 9,  -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1, -3, -3, -2},
                               {-1, 1,  0,  0,  -3, 5,  2,  -2, 0,  -3, -2, 1,  0,  -3, -1, 0,  -1, -2, -1, -2, 0,  3,  -1},
                               {-1, 0,  0,  2,  -4, 2,  5,  -2, 0,  -3, -3, 1,  -2, -3, -1, 0,  -1, -3, -2, -2, 1,  4,  -1},
                               {0,  -2, 0,  -1, -3, -2, -2, 6,  -2, -4, -4, -2, -3, -3, -2, 0,  -2, -2, -3, -3, -1, -2, -1},
                               {-2, 0,  1,  -1, -3, 0,  0,  -2, 8,  -3, -3, -1, -2, -1, -2, -1, -2, -2, 2,  -3, 0,  0,  -1},
                               {-1, -3, -3, -3, -1, -3, -3, -4, -3, 4,  2,  -3, 1,  0,  -3, -2, -1, -3, -1, 3,  -3, -3, -1},
                               {-1, -2, -3, -4, -1, -2, -3, -4, -3, 2,  4,  -2, 2,  0,  -3, -2, -1, -2, -1, 1,  -4, -3, -1},
                               {-1, 2,  0,  -1, -3, 1,  1,  -2, -1, -3, -2, 5,  -1, -3, -1, 0,  -1, -3, -2, -2, 0,  1,  -1},
                               {-1, -1, -2, -3, -1, 0,  -2, -3, -2, 1,  2,  -1, 5,  0,  -2, -1, -1, -1, -1, 1,  -3, -1, -1},
                               {-2, -3, -3, -3, -2, -3, -3, -3, -1, 0,  0,  -3, 0,  6,  -4, -2, -2, 1,  3,  -1, -3, -3, -1},
                               {-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4, 7,  -1, -1, -4, -3, -2, -2, -1, -2},
                               {1,  -1, 1,  0,  -1, 0,  0,  0,  -1, -2, -2, 0,  -1, -2, -1, 4,  1,  -3, -2, -2, 0,  0,  0},
                               {0,  -1, 0,  -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1, 1,  5,  -2, -2, 0,  -1, -1, 0},
                               {-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1, 1,  -4, -3, -2, 11,  2,  -3, -4, -3, -2},
                               {-2, -2, -2, -3, -2, -1, -2, -3, 2,  -1, -1, -2, -1, 3,  -3, -2, -2, 2,  7,  -1, -3, -2, -1},
                               {0,  -3, -3, -3, -1, -2, -2, -3, -3, 3,  1,  -2, 1,  -1, -2, -2, 0,  -3, -1, 4,  -3, -2, -1},
                               {-2, -1, 3,  4,  -3, 0,  1,  -1, 0,  -3, -4, 0,  -3, -3, -2, 0,  -1, -4, -3, -3, 4,  1,  -1},
                               {-1, 0,  0,  1,  -3, 3,  4,  -2, 0,  -3, -3, 1,  -1, -3, -1, 0,  -1, -3, -2, -2, 1,  4,  -1},
                               {0,  -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, 0,  0,  -2, -1, -1, -1, -1, -1}
                               };
int dp[MAX_N][MAX_N];

/*
 Needleman-Wunsch algorithm for determining the optimal alignment between two strings
 assuming a given score for hits, gaps and mismatches.
 Complexity: O(n * m) time, O(n * m) memory
*/

inline int needleman_wunsch(std::string A, std::string B, int n, int m)
{
    for (int i=0;i<=n;i++) dp[i][0] = dp[0][i] = -i * gap_score;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            int S = match_scoreboard[charToIndex[A[i-1]]][charToIndex[B[j-1]]];
            dp[i][j] = max(dp[i-1][j-1] + S, max(dp[i-1][j] - gap_score, dp[i][j-1] - gap_score));
        }
    }
    return dp[n][m];
}

inline pair<string, string> get_optimal_alignment(std::string A, std::string B, int n, int m)
{
    string retA, retB;
    stack<char> SA, SB;
    int ii = n, jj = m;
    while (ii != 0 || jj != 0)
    {
        if (ii == 0)
        {
            SA.push('-');
            SB.push(B[jj-1]);
            jj--;
        }
        else if (jj == 0)
        {
            SA.push(A[ii-1]);
            SB.push('-');
            ii--;
        }
        else
        {
            int S = match_scoreboard[charToIndex[A[ii-1]]][charToIndex[B[jj-1]]];
            if (dp[ii][jj] == dp[ii-1][jj-1] + S)
            {
                SA.push(A[ii-1]);
                SB.push(B[jj-1]);
                ii--; jj--;
            }
            else if (dp[ii-1][jj] > dp[ii][jj-1])
            {
                SA.push(A[ii-1]);
                SB.push('-');
                ii--;
            }
            else
            {
                SA.push('-');
                SB.push(B[jj-1]);
                jj--;
            }
        }
    }
    while (!SA.empty())
    {
        retA += SA.top();
        retB += SB.top();
        SA.pop();
        SB.pop();
    }
    return make_pair(retA, retB);
}

int main(int argc, char **argv)
{
  charToIndex.insert(make_pair('A', 0));
  charToIndex.insert(make_pair('R', 1));
  charToIndex.insert(make_pair('N', 2));
  charToIndex.insert(make_pair('D', 3));
  charToIndex.insert(make_pair('C', 4));
  charToIndex.insert(make_pair('Q', 5));
  charToIndex.insert(make_pair('E', 6));
  charToIndex.insert(make_pair('G', 7));
  charToIndex.insert(make_pair('H', 8));
  charToIndex.insert(make_pair('I', 9));
  charToIndex.insert(make_pair('L', 10));
  charToIndex.insert(make_pair('K', 11));
  charToIndex.insert(make_pair('M', 12));
  charToIndex.insert(make_pair('F', 13));
  charToIndex.insert(make_pair('P', 14));
  charToIndex.insert(make_pair('S', 15));
  charToIndex.insert(make_pair('T', 16));
  charToIndex.insert(make_pair('W', 17));
  charToIndex.insert(make_pair('Y', 18));
  charToIndex.insert(make_pair('V', 19));
  charToIndex.insert(make_pair('B', 20));
  charToIndex.insert(make_pair('Z', 21));
  charToIndex.insert(make_pair('X', 22));

  std::fstream FILE;
  FILE.open(argv[1]);
  std::string name = "", amino = "", A, B, whole, line;
  int at = 1;
  bool first = true;
  int names, t;
  std::unordered_map<std::string, std::string> things;
  std::vector<string> v;
  for (int i = 0; std::getline(FILE, line); i++){
    if (i == 0){
      std::stringstream iss( line );
      iss >> names;
    } else if (i < names+1){
      name = line;
      std::getline(FILE, line);
      amino = line;
      things.insert(make_pair(name, amino));
    } else {
      std::stringstream iss( line );
      iss >> A;
      iss >> B;
      // std::cout << A << "--" << B << ": ";
      // printf("%d\n",needleman_wunsch(things.at(A), things.at(B), things.at(A).length(), things.at(B).length()));
      whole = A + "--" + B + ": " + std::to_string(needleman_wunsch(things.at(A), things.at(B), things.at(A).length(), things.at(B).length()));
      v.push_back(whole);
    }
    // else if (line[0] == '>'){
    //   if (!first){
    //     things.push_back(make_pair(name, amino));
    //     name = "";
    //     amino = "";
    //     at = 1;
    //   }
    //   first = false;
    //   while (line[at] != ' '){
    //     name += line[at];
    //     at++;
    //   }
    // } else { amino += line; }
  }

  for (auto i : v){
    std::cout << i << '\n';
  }

  // for (int i = 0; i < things.size(); i++){
  //   for (int j = i + 1; j < things.size(); j++){
  //     std::string A = things.at(i).second;
  //     std::string B = things.at(j).second;
  //     int n = A.length(), m = B.length();
  //     std::cout << things.at(i).first << "--" << things.at(j).first << ": ";
  //     printf("%d\n",needleman_wunsch(A, B, n, m));
  //     pair<string, string> alignment = get_optimal_alignment(A, B, n, m);
  //     printf("%s\n%s\n", alignment.first.c_str(), alignment.second.c_str());
  //   }
  // }

  return 0;
}
