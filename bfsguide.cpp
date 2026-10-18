/*
=====================================================================
BFS (BREADTH-FIRST SEARCH) STUDY GUIDE
=====================================================================
WHAT IS BFS?
 BFS explores a graph (or grid) in LAYERS, like ripples in a pond:
   layer 0: the start
   layer 1: everything 1 step from the start
   layer 2: everything 2 steps from the start
   ...
 The FIRST time BFS reaches a place, that is the SHORTEST number of
 steps to it. That is why BFS answers "fewest steps / fewest edges /
 fewest tickets".

WHEN TO USE IT (words in the question)
   "minimum number of steps / moves / edges / tickets"
   "shortest path" when every step costs the same (1)
   "can you reach X?"  "how many places can be reached?"
   "farthest place from the start"
 NOT for: paths where edges have different costs (that needs Dijkstra).

THE 3 INGREDIENTS (every BFS has exactly these)
   1) a QUEUE      : places waiting to be explored (front = oldest)
   2) a dist[] list: shortest distance of each place. -1 = not reached.
                     It doubles as the "visited" mark.
   3) a way to list NEIGHBORS of a place
      (graph: graph[u]    grid: the 4 directions)

THE 5 STEPS (same every time)
   1. dist[start] = 0, push start into the queue.
   2. While the queue is not empty:
   3.    take the FRONT place u out of the queue.
   4.    for every neighbor v of u:
   5.       if v is allowed AND dist[v] == -1 (never reached):
                dist[v] = dist[u] + 1;  push v.

WORKED TRACE (edges: 1-2, 1-3, 2-4, 3-4, 4-5, start = 1)
   graph[1] = {2, 3}   graph[2] = {1, 4}   graph[3] = {1, 4}
   graph[4] = {2, 3, 5}   graph[5] = {4}

   start:   dist[1] = 0                         queue: [1]
   take 1:  neighbors 2, 3 -> dist[2]=1, dist[3]=1   queue: [2, 3]
   take 2:  neighbors 1 (seen), 4 -> dist[4]=2       queue: [3, 4]
   take 3:  neighbors 1, 4 (both seen)               queue: [4]
   take 4:  neighbors 2, 3 (seen), 5 -> dist[5]=3    queue: [5]
   take 5:  neighbor 4 (seen)                        queue: []  done
   Final: dist = 1:0, 2:1, 3:1, 4:2, 5:3.
   (Node 4 is reached at distance 2 the FIRST time, through 2.
    Later, 3 also touches 4, but dist[4] is already set, so we skip.)

COMMON MISTAKES
   [ ] Forgetting to mark dist when you PUSH (mark when pushing, not
       when taking out; otherwise a place gets pushed many times).
   [ ] Using -1 as "not reached" but forgetting to fill dist with -1.
   [ ] Grid: forgetting the bounds check BEFORE reading grid[nr][nc].
   [ ] Edges are two-way: add BOTH graph[a].push_back(b) and
       graph[b].push_back(a).
   [ ] Using DFS or a stack instead of a queue (gives wrong distances).
   [ ] Nodes numbered from 1: make the arrays size n + 1.
=====================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
using namespace std;

// =====================================================================
// TEMPLATE 1: BFS ON A GRAPH  (distance from a source to every node)
// Used in: Bicycle, Sea travel, Failed update
// =====================================================================
// graph[u] = list of neighbors of u. Nodes are numbered 1..n.
vector<int> bfsGraph(const vector< vector<int> >& graph, int source, int n) {

    vector<int> dist(n + 1, -1);      // -1 = not reached yet
    queue<int> line;                  // the waiting line

    dist[source] = 0;                 // step 1: the source is 0 steps away
    line.push(source);

    while (!line.empty()) {           // step 2: until nothing is waiting
        int u = line.front();         // step 3: take the front node
        line.pop();

        for (int i = 0; i < (int)graph[u].size(); i++) {   // step 4
            int v = graph[u][i];      // a neighbor of u

            if (dist[v] == -1) {      // step 5: never reached before
                dist[v] = dist[u] + 1;   // one more step than u
                line.push(v);            // explore from v later
            }
        }
    }
    return dist;                      // dist[x] == -1 means "cannot reach x"
}
// How to build the graph and use it:
//   vector< vector<int> > graph(n + 1);
//   for each edge (a, b): graph[a].push_back(b); graph[b].push_back(a);
//   vector<int> d = bfsGraph(graph, 1, n);
//   - farthest node: the biggest d[x]
//   - number of reachable nodes: count d[x] != -1

// =====================================================================
// TEMPLATE 2: BFS ON A GRID  (fewest moves between cells)
// Used in: Crumbling Temple, Warehouse Robot
// =====================================================================
// grid[i][j] == '#' means blocked. Rows 0..r-1, columns 0..c-1.
vector< vector<int> > bfsGrid(const vector<string>& grid, int r, int c,
                              int startR, int startC) {

    vector< vector<int> > dist(r, vector<int>(c, -1));
    queue< pair<int, int> > line;

    // The four neighbors: up, down, left, right.
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    dist[startR][startC] = 0;
    line.push(make_pair(startR, startC));

    while (!line.empty()) {
        pair<int, int> cur = line.front();
        line.pop();

        for (int k = 0; k < 4; k++) {
            int nr = cur.first + dr[k];       // neighbor row
            int nc = cur.second + dc[k];      // neighbor column

            // 1) bounds check FIRST (so we never read outside the grid)
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) continue;
            // 2) blocked cell
            if (grid[nr][nc] == '#') continue;
            // 3) already reached
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            line.push(make_pair(nr, nc));
        }
    }
    return dist;                      // -1 = unreachable
}
// If holes come as a list of coordinates (Crumbling Temple), store them
// in a vector< vector<bool> > hole and check hole[nr][nc] instead of '#'.
// If the question numbers rows from 1, make the arrays size n + 1 and
// use bounds 1..n instead.

// =====================================================================
// TEMPLATE 3: BFS THAT IGNORES SOME EDGES  (Bicycle)
// =====================================================================
// graph[u] holds pairs (neighbor, difficulty). Only edges with
// difficulty <= limit may be used. Returns the largest distance among
// the nodes that CAN reach the source (0 if none).
int bfsWithLimit(const vector< vector< pair<int, int> > >& graph,
                 int n, int limit) {

    vector<int> dist(n + 1, -1);
    queue<int> line;
    dist[1] = 0;
    line.push(1);
    int best = 0;

    while (!line.empty()) {
        int u = line.front();
        line.pop();

        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i].first;
            int difficulty = graph[u][i].second;

            if (difficulty > limit) continue;    // this edge is not allowed
            if (dist[v] != -1) continue;         // already reached

            dist[v] = dist[u] + 1;
            line.push(v);
            if (dist[v] > best) best = dist[v];
        }
    }
    return best;
}

// =====================================================================
// TEMPLATE 4: BFS WITH ONE BLOCKED NODE  (Failed update)
// =====================================================================
// Counts how many nodes can be reached from node 1 when node
// "blocked" refuses to take part (it is never entered).
int reachableWithout(const vector< vector<int> >& graph, int n, int blocked) {

    vector<bool> visited(n + 1, false);
    queue<int> line;
    visited[1] = true;
    line.push(1);
    int reached = 1;

    while (!line.empty()) {
        int u = line.front();
        line.pop();
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (v == blocked || visited[v]) continue;   // skip blocked/seen
            visited[v] = true;
            reached++;
            line.push(v);
        }
    }
    return reached;       // nodes NOT reached = n - reached (includes blocked)
}
// Failed update: try every blocked node 2..n, keep the largest (n - reached).

// =====================================================================
// TEMPLATE 5: BFS WHERE ONE "TICKET" REACHES A WHOLE GROUP (Bus Routes)
// =====================================================================
// routesOfStop[x] = routes through stop x; stopsOfRoute[r] = stops of route r.
// One ticket = ride one route to ANY stop on it. dist counts tickets.
vector<int> bfsRoutes(const vector< vector<int> >& stopsOfRoute,
                      const vector< vector<int> >& routesOfStop,
                      int n, int m, int s) {

    vector<int> tickets(n + 1, -1);
    vector<bool> routeUsed(m, false);   // each route only needs to be ridden once
    queue<int> line;

    tickets[s] = 0;
    line.push(s);

    while (!line.empty()) {
        int u = line.front();
        line.pop();

        for (int i = 0; i < (int)routesOfStop[u].size(); i++) {
            int r = routesOfStop[u][i];
            if (routeUsed[r]) continue;      // already ridden: skip
            routeUsed[r] = true;

            // ONE more ticket reaches every stop on this route.
            for (int j = 0; j < (int)stopsOfRoute[r].size(); j++) {
                int v = stopsOfRoute[r][j];
                if (tickets[v] == -1) {
                    tickets[v] = tickets[u] + 1;
                    line.push(v);
                }
            }
        }
    }
    return tickets;
}

// =====================================================================
// TEMPLATE 6: PARENT ARRAY  (Valid BFS?)
// =====================================================================
// Remember WHO each node was reached from. In a tree this is the
// node's parent (the root has parent 0).
vector<int> bfsParents(const vector< vector<int> >& graph, int n) {

    vector<int> parent(n + 1, 0);
    vector<bool> seen(n + 1, false);
    queue<int> line;
    seen[1] = true;
    line.push(1);

    while (!line.empty()) {
        int u = line.front();
        line.pop();
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (!seen[v]) {
                seen[v] = true;
                parent[v] = u;       // we reached v from u
                line.push(v);
            }
        }
    }
    return parent;
}

// =====================================================================
// QUICK GUIDE: WHICH TEMPLATE FOR WHICH QUESTION?
// =====================================================================
//  Crumbling Temple   -> Template 2 (grid), holes from a list, run BFS
//                        ONCE, answer each query by looking up dist.
//  Warehouse Robot    -> Template 2 (grid), find S and E first.
//  Bicycle            -> Template 3 (skip edges above the limit,
//                        answer = largest dist), once per group.
//  Sea travel         -> Template 1 twice (from island 1, from island N),
//                        then value(v) = parks[v] + max(d1[v], dN[v]),
//                        answer = sum of the two biggest values.
//  Failed update      -> Template 4 (try each blocked node).
//  Bus Routes         -> Template 5 (a ticket reaches a whole route).
//  Valid BFS?         -> Template 6 (parents), then check that each
//                        node's children are the next block of the
//                        given sequence.
//
// HOW TO DECIDE WHAT THE "PLACES" AND "NEIGHBORS" ARE (the hard part!)
//  1. What is ONE step in the question? (a move, a flight, a ticket)
//  2. What are the PLACES? (cells, islands, stops)
//  3. From a place, where can ONE step take me? Those are the neighbors.
//  4. Is any place or edge forbidden? Skip it with `continue`.
//  5. What do I print? dist of a target / the largest dist / a count.

int main() {
    return 0;     // this file is a study guide; the templates are above
}