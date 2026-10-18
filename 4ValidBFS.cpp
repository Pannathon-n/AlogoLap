/*
=====================================================================
QUESTION SUMMARY: "Valid BFS?"
=====================================================================
BFS (Breadth-First Search) visits a graph in layers, starting at
vertex 1, using a queue:
 1) Put vertex 1 in the queue and mark it as used.
 2) Take a vertex v from the FRONT of the queue and PRINT it.
 3) Look at every neighbor u of v that is not yet used. Mark each one
    as used and put it at the BACK of the queue.
    The order in which you take these neighbors is up to you.
 4) Repeat from step 2 until the queue is empty.

Because step 3 lets you choose the neighbor order, many different
sequences are possible for the same graph.

TASK: You get a TREE (a connected graph with no loops, n vertices,
      n-1 edges) and a sequence a1..an. Decide if the sequence can
      be printed by SOME valid BFS starting at vertex 1.
      Print "Yes" or "No".

INPUT:
 - Line 1: n (1 <= n <= 200,000)
 - Next n-1 lines: x y (an edge between x and y)
 - Last line: n distinct numbers a1 ... an (the sequence to check)

OUTPUT:
 - "Yes" or "No"

SAMPLE INPUT 1:
4
1 2
1 3
2 4
1 2 3 4
SAMPLE OUTPUT 1:
Yes

SAMPLE INPUT 2:
4
1 2
1 3
2 4
1 2 4 3
SAMPLE OUTPUT 2:
No

WHY? (the tree: 1 has children 2 and 3; 2 has child 4)
 Sequence 1 2 3 4: BFS from 1 adds children 2 and 3 (either order),
   then 2 adds 4. Printed order 1 2 3 4 is possible -> Yes.
 Sequence 1 2 4 3: after 1 we must print BOTH 2 and 3 before
   anything deeper like 4. But 4 comes before 3 -> No.

KEY IDEA:
 In a tree, once we start from vertex 1, every other vertex has
 exactly one PARENT (the neighbor closer to vertex 1).
 In a valid BFS, the vertices appear in the sequence like this:
   a[0] = 1, then ALL children of a[0] (in any order), then ALL
   children of a[1], then ALL children of a[2], and so on.
 So we walk through the sequence, and for each vertex v = a[i]:
   - count its children (c),
   - the NEXT c numbers of the sequence must all have v as their
     parent.
 If any check fails, the answer is "No".
 Because the numbers are distinct and the tree has n vertices,
 passing every check means the whole sequence is a valid BFS.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 200,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;            // number of vertices
    cin >> n;

    // The tree as an "adjacency list": graph[u] = the neighbors of u.
    vector< vector<int> > graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);   // edges work in both directions,
        graph[y].push_back(x);   // so we store it for both vertices
    }

    // Read the sequence we must check (a[0] is the first number).
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // The sequence must start with vertex 1.
    if (a[0] != 1) {
        cout << "No" << endl;
        return 0;
    }

    // STEP 1: find the parent of every vertex with an ordinary BFS
    // from vertex 1 (any neighbor order works, because in a tree each
    // vertex has only one parent).
    // parent[v] = the vertex we came from when we first reached v.
    // The root (vertex 1) gets parent 0, which means "no parent".
    vector<int> parent(n + 1, 0);
    vector<bool> seen(n + 1, false);
    queue<int> line;

    seen[1] = true;
    line.push(1);
    while (!line.empty()) {
        int v = line.front();   // take the vertex at the front
        line.pop();
        for (int i = 0; i < (int)graph[v].size(); i++) {
            int u = graph[v][i];
            if (!seen[u]) {
                seen[u] = true;
                parent[u] = v;   // we reached u from v
                line.push(u);
            }
        }
    }

    // STEP 2: check the sequence.
    // "pos" is the position in the sequence where the NEXT block of
    // children should start. Position 0 is vertex 1, so children of
    // the first vertex start at position 1.
    int pos = 1;

    for (int i = 0; i < n; i++) {

        int v = a[i];   // the vertex at this place in the sequence

        // How many children does v have?
        // Every neighbor is a child, except the parent (if v is not the root).
        int children = (int)graph[v].size();
        if (v != 1) {
            children = children - 1;   // remove the parent from the count
        }

        // The next "children" numbers must all be children of v.
        for (int j = 0; j < children; j++) {

            // If we run out of sequence, it cannot be valid.
            if (pos >= n) {
                cout << "No" << endl;
                return 0;
            }

            // The number here must have v as its parent.
            if (parent[a[pos]] != v) {
                cout << "No" << endl;
                return 0;
            }

            pos++;   // move on to the next position in the sequence
        }
    }

    // Every check passed.
    cout << "Yes" << endl;

    return 0;         // tells the computer the program finished successfully
}
/*
This one is a step up from your earlier BFS tasks. It uses BFS for the parent array, 
plus the idea that each vertex’s children appear as one block in the sequence. 
It is labeled MEDIUM, so it is probably the hardest of the four.
*/