/*
=====================================================================
QUESTION SUMMARY: "Failed update"
=====================================================================
There are N servers (1 to N) joined by M two-way network links.
Server 1 is the master. It is updated by hand. Every other server gets
the update through the network: a server that receives the update
passes it on to its neighbors.

The update software may CRASH on at most ONE server (never server 1).
A crashed server does not get updated AND does not pass the update on.

TASK: In the WORST case (the best server to crash from the point of
      view of causing damage), how many servers fail to get updated?
      Count the crashed server itself too.

INPUT:
 - Line 1: N and M (2 <= N <= 1000, 1 <= M <= 5000)
 - Next M lines: A B (a link between servers A and B)

OUTPUT:
 - One integer: the biggest number of servers that fail to get updated.

SAMPLE INPUT:
7 7
1 2
3 2
1 4
3 4
3 5
6 3
5 7

SAMPLE OUTPUT:
4

WHY 4? (walking through the sample)
 Crash server 2: others still reach everyone through 1-4-3...   -> only 2 fails (1)
 Crash server 4: others reach 3 through 2                       -> only 4 fails (1)
 Crash server 5: server 7 is only connected to 5, so 5 and 7 fail (2)
 Crash server 3: servers 5, 6, 7 are only reachable through 3,
                 so 3, 5, 6, 7 fail                              -> 4
 Crash 6 or 7: only itself fails (1).
 Worst case = 4.

KEY IDEA (simple, since N and M are small):
 Try crashing EACH server c from 2 to N, one at a time:
   1) Run BFS (explore outward) from server 1, but never enter
      server c.
   2) Count how many servers were reached (call it "reached").
   3) The servers that failed = N - reached. This includes c itself,
      because c was never entered, and every server that could only
      be reached through c.
 Keep the biggest failed count over all choices of c.
 Cost: about N searches x (N + M) steps = about 6 million steps. Fast.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, m;         // n = servers, m = links
    cin >> n >> m;

    // The network as an "adjacency list": graph[u] = servers linked to u.
    vector< vector<int> > graph(n + 1);
    for (int j = 0; j < m; j++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);   // links work in both directions,
        graph[b].push_back(a);   // so we store it for both servers
    }

    int worst = 0;    // the biggest number of failed servers found so far

    // Try crashing each server c (server 1 never crashes).
    for (int c = 2; c <= n; c++) {

        vector<bool> visited(n + 1, false);   // which servers got the update
        queue<int> line;                      // the BFS waiting line

        visited[1] = true;     // the master is always updated
        line.push(1);
        int reached = 1;       // how many servers got the update (server 1 counts)

        while (!line.empty()) {
            int u = line.front();   // take the server at the front
            line.pop();

            for (int i = 0; i < (int)graph[u].size(); i++) {
                int v = graph[u][i];

                // Skip the crashed server: it never receives or passes
                // on the update. Also skip servers already reached.
                if (v == c || visited[v]) {
                    continue;
                }

                visited[v] = true;   // v gets the update
                reached++;
                line.push(v);        // v passes it on later
            }
        }

        // Every server that was not reached has failed (this includes c).
        int failed = n - reached;

        if (failed > worst) {
            worst = failed;          // new worst case
        }
    }

    cout << worst << endl;   // print the worst case

    return 0;         // tells the computer the program finished successfully
}