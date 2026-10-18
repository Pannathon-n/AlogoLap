/*
=====================================================================
QUESTION SUMMARY: "Bicycle"
=====================================================================
A playground map is a GRAPH: N nodes (places) joined by M edges
(bicycle paths). Node 1 is the center. Each edge has a difficulty Dj.

There are Q groups of children. Group i refuses to use any path with
difficulty GREATER than Bi, so for that group only the edges with
Dj <= Bi exist.

For each group:
 - Choose a starting node s that can still reach node 1.
 - The child takes the SHORTEST path to node 1 (fewest edges).
 - We want the start s whose shortest path is the LONGEST.

TASK: For each group, print that longest shortest-path length
      (the number of edges).

INPUT:
 - Line 1: N, M and Q
 - Next M lines: U V D (an edge between U and V with difficulty D)
 - Next Q lines: B (the maximum difficulty for each group)

OUTPUT:
 - Q lines: one answer per group.

SAMPLE INPUT 1 (shortened): N=7, M=9, Q=3, B = 1000000, 20, 14
SAMPLE OUTPUT 1:
3
4
2

WHY? (walking through group 3 of sample 1, B = 14)
 Only edges with difficulty <= 14 are allowed:
   2-3 (5), 3-1 (14), 7-6 (12)
 Nodes that can reach node 1: node 3 (1 edge), node 2 (2 edges).
 Nodes 4, 5, 6, 7 cannot reach node 1, so they are not allowed.
 The longest shortest path is from node 2: 2 edges. Answer = 2.

SAMPLE INPUT 2: N=4, M=3, Q=1, B=1000000
SAMPLE OUTPUT 2: 2  (node 4 -> 2 -> 1 uses 2 edges)

KEY IDEA (BFS = Breadth-First Search):
 BFS starts at node 1 and explores outward like ripples in a pond:
 first all nodes 1 edge away, then 2 edges away, and so on. The first
 time BFS reaches a node, that is its shortest distance from node 1.
 For each group:
   1) Run BFS from node 1, but IGNORE edges with difficulty > B.
   2) Nodes never reached cannot get to node 1, so we skip them.
   3) The answer is the BIGGEST distance among reached nodes.
 BFS is fast (about N + M steps), and Q is at most 5, so it is fine.
 If no other node is reachable, the answer is 0.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
#include <utility>    // lets us use "pair" (two values stuck together)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading many numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;      // n = nodes, m = edges, q = number of groups
    cin >> n >> m >> q;

    // The map, stored as an "adjacency list":
    // graph[u] is a list of (neighbor, difficulty) pairs for node u.
    // Nodes are numbered from 1, so we make n + 1 lists (spot 0 unused).
    vector< vector< pair<int, int> > > graph(n + 1);

    for (int j = 0; j < m; j++) {
        int u, v, d;
        cin >> u >> v >> d;
        // A path works in both directions, so we store it for both nodes.
        graph[u].push_back(make_pair(v, d));
        graph[v].push_back(make_pair(u, d));
    }

    // Handle each group one by one.
    for (int g = 0; g < q; g++) {

        int b;        // the maximum difficulty this group can ride
        cin >> b;

        // dist[x] = the fewest edges from node 1 to node x.
        // -1 means "not reached (yet)".
        vector<int> dist(n + 1, -1);

        queue<int> line;      // the BFS waiting line

        dist[1] = 0;          // node 1 is 0 edges from itself
        line.push(1);         // start exploring from node 1

        int best = 0;         // the longest shortest distance found so far

        while (!line.empty()) {

            int u = line.front();   // take the node at the front of the line
            line.pop();

            // Look at every path that leaves node u.
            for (int i = 0; i < (int)graph[u].size(); i++) {

                int v = graph[u][i].first;        // the neighbor node
                int difficulty = graph[u][i].second;

                // Skip the path if it is too hard for this group.
                if (difficulty > b) {
                    continue;   // "continue" jumps to the next path
                }

                // Only visit v if we have not reached it before.
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;   // one more edge than u
                    line.push(v);            // explore from v later

                    if (dist[v] > best) {
                        best = dist[v];      // new longest distance
                    }
                }
            }
        }

        cout << best << '\n';   // the answer for this group
    }

    return 0;         // tells the computer the program finished successfully
}