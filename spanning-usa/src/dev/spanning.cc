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
using namespace std;
typedef  pair<int, int> iPair;
struct edge {
  int Fc;
  int Tc;
  int cost;
  edge(int from, int to, int costI){
    Fc = from;
    Tc = to;
    cost = costI;
  }
};

std::unordered_map<std::string, int> nameToIndex;
std::vector<std::string> names;
std::vector<edge *> connections;

// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;

    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back(make_pair(w, make_pair(u, v)));
    }

    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result

    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(V);

    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            // cout << names[u] << " - " << names[v] << endl;

            // Update MST weight
            mst_wt += it->first;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}
// Driver program to test above functions
int main(int argc, char *argv[])
{
    /* Let us create above shown weighted
       and unidrected graph */
     char str [100];
     FILE * pFile;
     pFile = fopen (argv[1],"r");
     int at = 0;
     size_t pos = 0;
     // Cnames.resize(128);
     names.reserve(200000);
     connections.reserve(200000);
     while (fgets (str , 100 , pFile) != NULL){
       std::string name = str;
       pos = name.find("--");
       if (pos != std::string::npos){
         break;
       }
       name.pop_back();
       name.erase(std::remove(name.begin(), name.end(), ' '),name.end());
       name.erase(std::remove(name.begin(), name.end(), '"'),name.end());
       names.push_back(name);
       nameToIndex.insert(make_pair(name, at));
       at ++;
     }
     while (fgets (str , 100 , pFile) != NULL){
       std::string line = str;
       pos = 0;
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
       from.erase(std::remove(from.begin(), from.end(), ' '),from.end());
       from.erase(std::remove(from.begin(), from.end(), '"'),from.end());
       to.erase(std::remove(to.begin(), to.end(), ' '),to.end());
       to.erase(std::remove(to.begin(), to.end(), '"'),to.end());
       edge * newEdge = new edge(nameToIndex.at(from), nameToIndex.at(to), costI);
       connections.push_back(newEdge);
     }

    int V = names.size(), E = connections.size();
    Graph g(V, E);

    for( auto connection : connections ){
      g.addEdge(connection->Fc, connection->Tc, connection->cost);
    }
    //  making above shown graph

    // cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();

    cout << mst_wt << "\n";

    return 0;
}
