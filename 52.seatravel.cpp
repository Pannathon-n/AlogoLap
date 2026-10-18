/*
=====================================================================
QUESTION SUMMARY: "Sea travel"
=====================================================================
There are N islands and M boat routes (a graph; each route works in
both directions). Airports are on island 1 and island N.
Island i has Pi parks (P1 = PN = 0).

Your trip:
 1) Fly to island 1 or island N (call it the START).
 2) Boat trip from START to some island x (x is not START).
    The boat trip uses the FEWEST routes (shortest path).
    Visit all Px parks.
 3) Helicopter to a different island y (y is not x). Visit all Py parks.
    The helicopter itself gives no points.
 4) Boat trip (fewest routes) from y to island 1 or N (the END).
 5) Fly home from the END.

SATISFACTION = (routes START->x) + Px + Py + (routes y->END).
TASK: Print the MAXIMUM satisfaction.

INPUT:
 - Line 1: N and M
 - Line 2: P1 ... PN
 - Next M lines: A B (a route between islands A and B)

OUTPUT:
 - One integer: the best satisfaction.

SAMPLE OUTPUT: 12  (for the sample with N = 8, M = 9)

WHY 12? (plan 3 of the statement)
 Fly to island 8, boat to island 3 (3 routes), 4 parks = 7 points.
 Helicopter to island 7, 2 parks, boat to island 1 (3 routes) = 5 points.
 Total = 12.

KEY IDEA:
 The x-part and the y-part do not depend on each other, except that
 x and y must be DIFFERENT islands.
 For any island v, the best value it can give is:
        f(v) = Pv + max( dist(1, v), dist(N, v) )
 because we may choose START (or END) to be whichever airport is
 farther away. Distances are the same in both directions.
 So the answer = the biggest f(x) + f(y) with x != y
               = the SUM OF THE TWO LARGEST f VALUES.
 To get dist(1, v) and dist(N, v) for every island, run BFS
 (Breadth-First Search) twice: once from island 1 and once from island N.
 BFS explores outward in layers, so the first time it reaches a
 node is the shortest distance (in routes).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// Fills "dist" with the fewest routes from island "source" to every island.
// -1 means "cannot be reached".
vector<int> bfs(const vector< vector<int> >& graph, int source, int n) {

    vector<int> dist(n + 1, -1);   // every island starts as "not reached"
    queue<int> line;               // the BFS waiting line

    dist[source] = 0;              // the source is 0 routes from itself
    line.push(source);

    while (!line.empty()) {
        int u = line.front();      // take the island at the front
        line.pop();

        // Look at every island that has a direct route to u.
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (dist[v] == -1) {           // not reached yet
                dist[v] = dist[u] + 1;     // one more route than u
                line.push(v);              // explore from v later
            }
        }
    }
    return dist;
}

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading many numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = islands, m = boat routes
    cin >> n >> m;

    // parks[i] = number of parks on island i (islands numbered from 1).
    // "long long" is a big number box, to be safe.
    vector<long long> parks(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> parks[i];
    }

    // The map as an "adjacency list": graph[u] = islands next to u.
    vector< vector<int> > graph(n + 1);
    for (int j = 0; j < m; j++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);   // routes work in both directions,
        graph[b].push_back(a);   // so we store it for both islands
    }

    // Shortest distances from island 1 and from island N.
    vector<int> d1 = bfs(graph, 1, n);
    vector<int> dN = bfs(graph, n, n);

    // We want the two LARGEST values of f(v) over all islands v.
    // "best1" is the largest, "best2" is the second largest.
    // They start very small so any real value replaces them.
    long long best1 = -1, best2 = -1;

    for (int v = 1; v <= n; v++) {

        // The farther airport gives more boat routes.
        long long far = d1[v];
        if (dN[v] > far) {
            far = dN[v];
        }

        long long f = parks[v] + far;   // the best value island v can give

        // Keep track of the top two values.
        if (f > best1) {
            best2 = best1;   // the old largest becomes second largest
            best1 = f;
        } else if (f > best2) {
            best2 = f;
        }
    }

    // x and y are different islands, so we add the top two values.
    cout << best1 + best2 << endl;

    return 0;         // tells the computer the program finished successfully
}