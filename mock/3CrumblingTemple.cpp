/*
=====================================================================
QUESTION SUMMARY: "The Crumbling Temple"
=====================================================================
A temple floor is an N x N grid of tiles. Exactly M tiles are HOLES
that you cannot step on. You start at tile (1, 1) (never a hole).
You may move up, down, left or right to a neighboring tile that is
not a hole. Each step costs 1.

There are t target tiles (t <= 5).
TASK: For each target, print the FEWEST steps from (1, 1) to it.
      If the target is a hole, or cannot be reached because holes
      block the way, print: Impossible

INPUT:
 - Line 1: N and M (1 <= N <= 1000, 0 <= M <= 100,000)
 - Next M lines: row and column of each hole
 - Next line: t
 - Next t lines: row and column of each target

OUTPUT:
 - t lines: the minimum steps, or "Impossible".

SAMPLE INPUT 1:
4 3
2 2
2 3
3 1
2
4 4
3 2
SAMPLE OUTPUT 1:
6
7

WHY? (sample 1, H = hole, grid rows 1 to 4)
   row 1:  .  .  .  .
   row 2:  .  H  H  .
   row 3:  H  .  .  .
   row 4:  .  .  .  .
 To reach (4,4): go right 3 along row 1, then down 3 along column 4
 = 6 steps. To reach (3,2): the shortest way is around the right side:
 (1,1) -> (1,4) is 3 steps, down to (3,4) is 2 more, then left to
 (3,3) and (3,2) is 2 more = 7 steps.

SAMPLE INPUT 2: N=5, holes (1,2) (2,2) (3,2) (4,2) (5,2), target (5,5)
 A wall of holes in column 2 blocks everything -> Impossible.

KEY IDEA (BFS = Breadth-First Search):
 BFS explores outward from (1, 1) in layers: all tiles 1 step away,
 then 2 steps away, and so on. The first time BFS reaches a tile,
 that is its shortest distance. We run BFS ONCE from (1, 1), fill a
 distance table for the whole grid, and then answer every query by
 just looking up the table. The grid has at most 1,000,000 tiles, so
 this is fast.
 Distance -1 means "never reached". A hole is never reached, so the
 same check covers "target is a hole" and "blocked off".
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
#include <utility>    // lets us use "pair" (two values stuck together)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 lines is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = grid size, m = number of holes
    cin >> n >> m;

    // hole[r][c] is true if tile (r, c) is a hole.
    // Rows and columns start at 1, so we make n + 1 spots (spot 0 unused).
    vector< vector<bool> > hole(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        hole[r][c] = true;   // mark this tile as a hole
    }

    // dist[r][c] = fewest steps from (1,1) to tile (r,c). -1 = not reached.
    vector< vector<int> > dist(n + 1, vector<int>(n + 1, -1));

    queue< pair<int, int> > line;   // the BFS waiting line of tiles

    dist[1][1] = 0;                 // the start is 0 steps from itself
    line.push(make_pair(1, 1));

    // The four directions we can move: up, down, left, right.
    // For direction k we change the row by dr[k] and the column by dc[k].
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!line.empty()) {

        pair<int, int> cur = line.front();   // take the tile at the front
        line.pop();

        int r = cur.first;
        int c = cur.second;

        // Try all four neighbors.
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];   // the neighbor's row
            int nc = c + dc[k];   // the neighbor's column

            // Skip neighbors that are outside the grid.
            if (nr < 1 || nr > n || nc < 1 || nc > n) {
                continue;
            }
            // Skip holes and tiles we have already reached.
            if (hole[nr][nc] || dist[nr][nc] != -1) {
                continue;
            }

            dist[nr][nc] = dist[r][c] + 1;   // one more step than the current tile
            line.push(make_pair(nr, nc));    // explore from it later
        }
    }

    // Answer the queries by looking up the table.
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int x, y;
        cin >> x >> y;

        if (dist[x][y] == -1) {
            cout << "Impossible" << '\n';   // hole, or blocked off
        } else {
            cout << dist[x][y] << '\n';
        }
    }

    return 0;         // tells the computer the program finished successfully
}
/*
This is the grid version of your Bicycle, Bus Routes, and Sea travel problems (BFS for shortest distance), 
so if the TA’s mock exam is accurate, graphs may appear on the midterm after all.
*/